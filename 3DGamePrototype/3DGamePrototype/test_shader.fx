/*
 * Various shader functions & code snippets taken from Frank Luna: 3D Game Programming with DirectX 11
 */

static const int DIRECTIONAL_LIGHT = 0;
static const int POINT_LIGHT = 1;
static const int SPOT_LIGHT = 2;

struct Light {
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 position;
  float range;
  float3 direction;
  float exponent;
  float3 attenuation;
  bool enabled;
  int type;
  float3 padding;
};

static const int MAX_LIGHTS = 1;

struct Material {
  float4 ambient, diffuse, specular;
  float specularPower;
};

Texture2D diffuseTexture : register(t0);
Texture2D specularTexture : register(t1);
Texture2D normalMap : register(t2);
SamplerState samAnistropic : register(s0);
TextureCube cubeMap : register(t3);

cbuffer ConstantBuffer : register(b0) {
  matrix world;
  matrix view;
  matrix projection;
  Light lights[MAX_LIGHTS];
  Material material;
  float3 eyePosW;
  bool enableTexturing;
  bool enableSpecularMapping;
  bool enableBumpMapping;
  bool enableClipTesting;
  float fogStart;
  float fogRange;
  float2 padding;
  float4 fogColour;
}

struct VS_OUTPUT {
  float4 pos : SV_POSITION;
  float3 normalW : NORMAL;
  float3 tangentW : TANGENT;
  float3 posW : POSITION;
  float2 tex : TEXCOORD0;
};

// helper function forward declarations
float3 normalSampleToWorldSpace(float3 normalMapSample, float3 normalW, float3 tangentW);
void computeDirectionalLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular);
void computePointLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular);
void computeSpotLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular);

/*
 * General purpose vertex shader
 */
VS_OUTPUT VS(float4 pos : POSITION, float3 normalL : NORMAL, float3 tangentL : TANGENT, float2 tex : TEXCOORD0) {
  VS_OUTPUT output = (VS_OUTPUT) 0;

  output.pos = mul(pos, world);
  output.posW = output.pos.xyz;
  output.pos = mul(output.pos, view);
  output.pos = mul(output.pos, projection);

  float3 normalW = mul(float4(normalize(normalL), 0.0f), world).xyz;
  normalW = normalize(normalW);
  output.normalW = normalW;
  float3 tangentW = mul(float4(normalize(tangentL), 0.0f), world).xyz;
  tangentW = normalize(tangentW);
  output.tangentW = tangentW;
  output.tex = tex;

  return output;
}

float4 PS(VS_OUTPUT input) : SV_Target {
  float4 textureColour = enableTexturing ? diffuseTexture.Sample(samAnistropic, input.tex) : float4(1.0f, 1.0f, 1.0f, material.diffuse.a);
  float4 perPixelSpecularMat = enableSpecularMapping ? specularTexture.Sample(samAnistropic, input.tex) : material.specular;
  // read the normal from the bump map if appropriate
  float3 perPixelNormalT = enableBumpMapping ? normalMap.Sample(samAnistropic, input.tex).xyz : float3(0.0f, 0.0f, 0.0f);
  // convert the bump map normal from tangent space to world space
  float3 perPixelNormal = enableBumpMapping ? normalize(normalSampleToWorldSpace(perPixelNormalT, input.normalW, input.tangentW)) : input.normalW;

  // taken from Frank Luna 3D Game Programming with DirectX 11
  if (enableTexturing && enableClipTesting) {
    clip(textureColour.a - 0.1f);
  }

  // initialise the colour components to 0
  float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
  float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
  float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
  // vectors to use as output parameters for the various lighting helper functions
  float4 a, d, s;

  for (int i = 0; i < MAX_LIGHTS; i++) {
    if (lights[i].enabled) {
      switch (lights[i].type) {
        case DIRECTIONAL_LIGHT:
          computeDirectionalLight(lights[i], input.posW, perPixelNormal, perPixelSpecularMat, a, d, s);
          break;
        case POINT_LIGHT:
          computePointLight(lights[i], input.posW, perPixelNormal, perPixelSpecularMat, a, d, s);
          break;
        case SPOT_LIGHT:
          computeSpotLight(lights[i], input.posW, perPixelNormal, perPixelSpecularMat, a, d, s);
          break;
      }
      ambient += a;
      diffuse += d;
      specular += s;
    }
  }

  float4 returnColour = (textureColour * (ambient + diffuse)) + specular;

  // fog calculations taken from Frank Luna 3D Game Programming with DirectX 11
  float3 toEye = (eyePosW - input.posW);
  float distToEye = length(toEye);
  toEye /= distToEye;
  float fogAmount = saturate((distToEye - fogStart) / fogRange);
  returnColour = lerp(returnColour, fogColour, fogAmount);
  return returnColour;
}

/*
 * Helper functions taken from Frank Luna 3D Game Programming with DirectX 11
 */
float3 normalSampleToWorldSpace(float3 normalMapSample, float3 normalW, float3 tangentW) {
  float3 normalT = (2.0f * normalMapSample) - 1.0f;

  float3 N = normalW;
  float3 T = normalize(tangentW - dot(tangentW, N) * N);
  float3 B = cross(N, T);

  float3x3 TBN = float3x3(T, B, N);
  float3 bumpedNormalW = mul(normalT, TBN);
  return bumpedNormalW;
}

void computeDirectionalLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular) {
  // initalise the output colour components to 0
  ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
  diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
  specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

  // find the vector from the eye to the surface position & normalise
  float3 toEye = (eyePosW - positionW);
  toEye = normalize(toEye);
  float3 lightVec = -light.direction;
  lightVec = normalize(lightVec);

  float diffuseAmount = max(dot(lightVec, normalW), 0.0f);
  diffuse = diffuseAmount * (material.diffuse * light.diffuse);
  ambient = (material.ambient * light.ambient);

  float3 r = reflect(-lightVec, normalW);
  r = normalize(r);
  float specularAmount = pow(max(dot(r, toEye), 0.0f), material.specularPower);
  specular = specularAmount * (pSpecularMat * light.specular);
}

void computePointLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular) {
  // initalise the output colour components to 0
  ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
  diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
  specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

  // find the vector from the eye to the surface position & normalise
  float3 toEye = (eyePosW - positionW);
  toEye = normalize(toEye);
  float3 lightVec = light.position - positionW;
  // store the magnitude of the light vector for range checks
  float d = length(lightVec);
  lightVec /= d;

  if (d > light.range) {
    return;
  }

  float diffuseAmount = max(dot(lightVec, normalW), 0.0f);
  diffuse = diffuseAmount * (material.diffuse * light.diffuse);
  ambient = (material.ambient * light.ambient);

  float3 r = reflect(-lightVec, normalW);
  r = normalize(r);
  float specularAmount = pow(max(dot(r, toEye), 0.0f), material.specularPower);
  specular = specularAmount * (pSpecularMat * light.specular);

  float attenuation = 1.0f / dot(light.attenuation, float3(1.0f, d, d * d));
  diffuse *= attenuation;
  specular *= attenuation;
}

void computeSpotLight(Light light, float3 positionW, float3 normalW, float4 pSpecularMat, out float4 ambient, out float4 diffuse, out float4 specular) {
  // initalise the output colour components to 0
  ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
  diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
  specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

  // find the vector from the eye to the surface position & normalise
  float3 toEye = (eyePosW - positionW);
  toEye = normalize(toEye);
  float3 lightVec = light.position - positionW;
  // store the magnitude of the light vector for range checks
  float d = length(lightVec);
  lightVec /= d;

  if (d > light.range) {
    return;
  }

  float diffuseAmount = max(dot(lightVec, normalW), 0.0f);
  diffuse = diffuseAmount * (material.diffuse * light.diffuse);
  ambient = (material.ambient * light.ambient);

  float3 r = reflect(-lightVec, normalW);
  r = normalize(r);
  float specularAmount = pow(max(dot(r, toEye), 0.0f), material.specularPower);
  specular = specularAmount * (pSpecularMat * light.specular);

  float spot = pow(max(dot(-lightVec, normalize(light.direction)), 0.0f), light.exponent);
  float attenuation = spot / dot(light.attenuation, float3(1.0f, d, d * d));
  ambient *= spot;
  diffuse *= attenuation;
  specular *= attenuation;
}
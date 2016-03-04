#include "DirectX11Graphics.h"

unique_ptr<DirectX11Graphics> DirectX11Graphics::instance;

DirectX11Graphics::DirectX11Graphics() {
  if (!initialised) {
    HRESULT hr = initialise();
    if (FAILED(hr)) {
      throw exception("error initialising graphics");
    }
    initialised = true;
  }
}

DirectX11Graphics& DirectX11Graphics::getGraphics() {
  if (!instance) {
    try {
      instance.reset(new DirectX11Graphics());
    }
    catch (exception& e) {
      throw;
    }
  }
  return *instance;
}

void DirectX11Graphics::receiveMessage(IMessage& message) {
  if (message.getType() == BEGIN_FRAME_MESSAGE) {
    camPos = *((Vector3<float>*) message.getData());
    beginFrame();
  }
  else if (message.getType() == SWAP_BUFFER_MESSAGE) {
    swap();
  }
  else if (message.getType() == DRAW_MESSAGE) {
    draw(0);
  }
}

void DirectX11Graphics::cleanup() {
  for (auto kvp : vertexBuffers) {
    kvp.second->Release();
  }

  for (auto kvp : indexBuffers) {
    kvp.second->Release();
  }

  if (immediateContext) immediateContext->ClearState();
  if (anistropicSampler) anistropicSampler->Release();
  if (constantBuffer) constantBuffer->Release();
  if (vertexLayout) vertexLayout->Release();
  if (vertexShader) vertexShader->Release();
  if (pixelShader) pixelShader->Release();
  if (renderTargetView) renderTargetView->Release();
  if (swapChain) swapChain->Release();
  if (immediateContext) immediateContext->Release();
  if (d3dDevice) d3dDevice->Release();
  if (depthStencilView) depthStencilView->Release();
  if (depthStencilBuffer) depthStencilBuffer->Release();
  if (solidState) solidState->Release();

  initialised = false;
}

HRESULT DirectX11Graphics::loadTexture(const string& textureFile, ITexture*& texuture) const {
  return S_OK;
}

HRESULT DirectX11Graphics::loadMesh(const Mesh& mesh) {
  return S_OK;
}

HRESULT DirectX11Graphics::initialise() {
  HRESULT hr = initDevice();

  if (FAILED(hr)) {
    return hr;
  }

  SimpleVertex vertices[] =
  {
    // front face vertices [0-3]
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    // back face vertices [4-7]
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    // left face vertices [8-11]
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
    // right face vertices [12-15]
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    // top face vertices [16-19]
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    // bottom face vertices [20-23]
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) }
  };

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(SimpleVertex) * 24;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = vertices;

  ID3D11Buffer* vertexBuffer;
  hr = d3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

  if (FAILED(hr))
    return hr;

  WORD indices[] =
  {
    // front face
    0, 1, 2,
    2, 1, 3,
    // back face
    4, 5, 6,
    6, 5, 7,
    // top face
    16, 17, 18,
    18, 17, 19,
    // bottom face
    20, 21, 22,
    22, 21, 23,
    // left face
    8, 9, 10,
    10, 9, 11,
    // right face
    12, 13, 14,
    14, 13, 15
  };

  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(WORD) * 36;
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;

  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = indices;
  ID3D11Buffer* indexBuffer;
  hr = d3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

  if (FAILED(hr))
    return hr;

  CreateDDSTextureFromFile(d3dDevice, L"Crate_COLOR.dds", nullptr, &diffuse);
  CreateDDSTextureFromFile(d3dDevice, L"Crate_SPEC.dds", nullptr, &specular);
  CreateDDSTextureFromFile(d3dDevice, L"Crate_NRM.dds", nullptr, &normal);

  vertexBuffers.insert(pair<int, ID3D11Buffer* const>(0, vertexBuffer));
  indexBuffers.insert(pair<int, ID3D11Buffer* const>(0, indexBuffer));
  indexCounts.insert(pair<int, UINT>(0, 36));

  buffer = new char[sizeof(ConstantBuffer)];

  objectWorld = XMMatrixIdentity();

  return S_OK;
}

void DirectX11Graphics::beginFrame() {
  float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
  immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
  immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  XMMATRIX world = XMMatrixIdentity();
  XMMATRIX view = XMMatrixLookToLH(XMLoadFloat4(&XMFLOAT4(camPos.getX(), camPos.getY(), camPos.getZ(), 0.0f)), XMLoadFloat4(&XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f)), XMLoadFloat4(&XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f)));
  XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.01f, 100.0f);

  cb.mWorld = XMMatrixTranspose(world);
  cb.mView = XMMatrixTranspose(view);
  cb.mProjection = XMMatrixTranspose(projection);

  LightStruct light;
  light.type = POINT_LIGHT;

  //light.ambient = XMFLOAT4(0.2f, 0.0f, 0.0f, 1.0f);
  //light.diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
  //light.specular = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
  //light.attenuation = XMFLOAT3(0.0f, 0.1f, 0.0f);
  //light.range = 1000.0f;
  //light.exponent = 96.0f;
  //light.position = XMFLOAT3(0.0f, 0.0f, -13.0f);
  //light.direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

  light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
  light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
  light.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
  light.attenuation = XMFLOAT3(0.0f, 0.1f, 0.0f);
  light.range = 1000.0f;
  light.position = XMFLOAT3(0.0f, 5.0f, -10.0f);

  //light.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
  //light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
  //light.specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
  //light.exponent = 20.0f;
  //light.direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

  light.enabled = true;
  cb.lights[0] = light;

  Material material;
  material.diffuse = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
  material.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
  material.specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
  material.specularPower = 10.0f;
  cb.material = material;

  XMMATRIX* matrix = (XMMATRIX*) buffer;
  XMMATRIX& a = *matrix;
  a = XMMatrixTranspose(world);
  XMMATRIX& b = *(XMMATRIX*) (buffer + sizeof(XMMATRIX));
  b = XMMatrixTranspose(view);
  XMMATRIX& c = *(XMMATRIX*) (buffer + (sizeof(XMMATRIX) * 2));
  c = XMMatrixTranspose(projection);
  LightStruct* lightP = (LightStruct*) (buffer + sizeof(XMMATRIX) * 3);
  LightStruct& l = *lightP;
  l = light;
  Material* mat = (Material*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct));
  Material& m = *mat;
  m = material;
  XMFLOAT3* eyePosw = (XMFLOAT3*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material));
  XMFLOAT3& e = *eyePosw;
  e = XMFLOAT3(0.0f, 2.0f, -10.0f);
  int z = 1;
  int* enableTex = (int*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3));
  int& eT = *enableTex;
  eT = z;
  int* enableSpec = (int*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3) + sizeof(int));
  int& eS = *enableSpec;
  eS = z;
  int* enableBump = (int*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3) + (sizeof(int) * 2));
  int& eB = *enableBump;
  eB = z;
  float* fogStart = (float*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3) + (sizeof(int) * 4));
  float x = 40.0f;
  float y = 50.0f;
  float& fS = *fogStart;
  fS = x;
  float* fogRange = (float*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3) + (sizeof(int) * 4) + sizeof(float));
  float& fR = *fogRange;
  fR = y;
  XMFLOAT4* fogColour = (XMFLOAT4*) (buffer + (sizeof(XMMATRIX) * 3) + sizeof(LightStruct) + sizeof(Material) + sizeof(XMFLOAT3) + (sizeof(int) * 4) + (sizeof(float) * 2) + sizeof(XMFLOAT2));
  XMFLOAT4& fC = *fogColour;
  fC = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

  //XMMATRIX mWorld;
  //XMMATRIX mView;
  //XMMATRIX mProjection;
  //LightStruct lights[MAX_LIGHTS];
  //Material material;
  //XMFLOAT3 eyePositionW;
  //int enableTexturing;
  //int enableSpecularMapping;
  //int enableBumpMapping;
  //int enableClipTesting;
  //float fogStart;
  //float fogRange;
  //XMFLOAT2 padding;
  //XMFLOAT4 fogColour;


  //cb1.data = &XMMatrixTranspose(world);
  //void* a = ((char*) cb1.data) + sizeof(XMMATRIX);
  //a = &XMMatrixTranspose(view);
  //a = ((char*) cb1.data) + (sizeof(XMMATRIX) * 2);
  //a = &XMMatrixTranspose(projection);

  cb.eyePositionW = XMFLOAT3(0.0f, 2.0f, -10.0f);
  cb.fogStart = 100.0f - 60.0f;
  cb.fogRange = 50.0f;
  XMStoreFloat4(&cb.fogColour, XMLoadFloat4(&XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f)));

  immediateContext->VSSetShader(vertexShader, nullptr, 0);
  immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
  immediateContext->PSSetShader(pixelShader, nullptr, 0);
  immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);
  immediateContext->PSSetShaderResources(0, 1, &diffuse);
  immediateContext->PSSetShaderResources(1, 1, &specular);
  immediateContext->PSSetShaderResources(2, 1, &normal);
}

void DirectX11Graphics::draw(int meshId) {
  UINT stride = sizeof(SimpleVertex);
  UINT offset = 0;

  //objectWorld *= XMMatrixRotationY(convertDegreesToRadians(1));
  //cb.mWorld = XMMatrixTranspose(objectWorld);

  cb.enableBumpMapping = 1;
  cb.enableSpecularMapping = 1;
  cb.enableTexturing = 1;
  immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, buffer, 0, 0);
  immediateContext->IASetVertexBuffers(0, 1, &vertexBuffers.at(meshId), &stride, &offset);
  immediateContext->IASetIndexBuffer(indexBuffers.at(meshId), DXGI_FORMAT_R16_UINT, 0);
  immediateContext->DrawIndexed(indexCounts.at(meshId), 0, 0);
}

void DirectX11Graphics::swap() const {
  swapChain->Present(0, 0);
}

HRESULT DirectX11Graphics::initDevice() {
  HRESULT hr = S_OK;

  UINT createDeviceFlags = 0;

#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driverTypes[] = {
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,
  };

  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };

  UINT numFeatureLevels = ARRAYSIZE(featureLevels);

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Width = 1920;
  sd.BufferDesc.Height = 1080;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = Window::getWindowHandle();
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
    driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &sd, &swapChain, &d3dDevice, &featureLevel, &immediateContext);
    if (SUCCEEDED(hr)) {
      break;
    }
  }

  if (FAILED(hr)) {
    return hr;
  }

  D3D11_TEXTURE2D_DESC depthStencilTexDesc;
  depthStencilTexDesc.Width = 1920;
  depthStencilTexDesc.Height = 1080;
  depthStencilTexDesc.MipLevels = 1;
  depthStencilTexDesc.ArraySize = 1;
  depthStencilTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilTexDesc.SampleDesc.Count = 1;
  depthStencilTexDesc.SampleDesc.Quality = 0;
  depthStencilTexDesc.Usage = D3D11_USAGE_DEFAULT;
  depthStencilTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthStencilTexDesc.CPUAccessFlags = 0;
  depthStencilTexDesc.MiscFlags = 0;

  hr = d3dDevice->CreateTexture2D(&depthStencilTexDesc, nullptr, &depthStencilBuffer);

  if (FAILED(hr)) {
    return hr;
  }

  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
  depthStencilDesc.DepthEnable = TRUE;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
  depthStencilDesc.StencilEnable = FALSE;
  depthStencilDesc.StencilReadMask = 0xFF;
  depthStencilDesc.StencilWriteMask = 0xFF;

  ID3D11DepthStencilState* depthStencilState;

  hr = d3dDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
  if (FAILED(hr)) {
    return hr;
  }

  hr = d3dDevice->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthStencilView);
  if (FAILED(hr)) {
    return hr;
  }

  immediateContext->OMSetDepthStencilState(depthStencilState, 0);

  // Create a render target view
  ID3D11Texture2D* backBuffer = nullptr;
  hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

  if (FAILED(hr)) {
    return hr;
  }

  hr = d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
  backBuffer->Release();

  if (FAILED(hr)) {
    return hr;
  }

  immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

  D3D11_RASTERIZER_DESC solidDesc;
  ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
  solidDesc.FillMode = D3D11_FILL_SOLID;
  solidDesc.CullMode = D3D11_CULL_BACK;
  solidDesc.FrontCounterClockwise = false;

  hr = d3dDevice->CreateRasterizerState(&solidDesc, &solidState);

  if (FAILED(hr)) {
    return hr;
  }

  immediateContext->RSSetState(solidState);

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT) 1920;
  vp.Height = (FLOAT) 1080;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  immediateContext->RSSetViewports(1, &vp);

  hr = initShadersAndInputLayout();

  if (FAILED(hr)) {
    return hr;
  }

  // Set primitive topology
  immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Create the constant buffer
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(ConstantBuffer);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  hr = d3dDevice->CreateBuffer(&bd, nullptr, &constantBuffer);

  if (FAILED(hr)) {
    return hr;
  }

  // Create the sample state
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
  sampDesc.MaxAnisotropy = 16;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

  hr = d3dDevice->CreateSamplerState(&sampDesc, &anistropicSampler);
  if (FAILED(hr)) {
    return hr;
  }
  immediateContext->PSSetSamplers(0, 1, &anistropicSampler);

  return S_OK;
}

HRESULT DirectX11Graphics::initShadersAndInputLayout() {
  HRESULT hr;

  ID3DBlob* vsBlob = nullptr;
  hr = compileShaderFromFile(L"test_shader.fx", "VS", "vs_4_0", &vsBlob);

  if (FAILED(hr)) {
    MessageBox(nullptr,
      L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
    return hr;
  }

  hr = d3dDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);

  if (FAILED(hr)) {
    vsBlob->Release();
    return hr;
  }

  ID3DBlob* psBlob = nullptr;
  hr = compileShaderFromFile(L"test_shader.fx", "PS", "ps_4_0", &psBlob);

  if (FAILED(hr)) {
    MessageBox(nullptr,
      L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
    return hr;
  }

  hr = d3dDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
  psBlob->Release();

  if (FAILED(hr)) {
    return hr;
  }

  // Define the input layout
  D3D11_INPUT_ELEMENT_DESC layout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
  };

  UINT numElements = ARRAYSIZE(layout);

  // Create the input layout
  hr = d3dDevice->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &vertexLayout);
  vsBlob->Release();

  if (FAILED(hr)) {
    return hr;
  }

  // Set the input layout
  immediateContext->IASetInputLayout(vertexLayout);

  return S_OK;
}

HRESULT DirectX11Graphics::compileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
  HRESULT hr = S_OK;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3DBlob* errorBlob;

  hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &errorBlob);

  if (FAILED(hr)) {
    if (errorBlob != nullptr) {
      OutputDebugStringA((char*) errorBlob->GetBufferPointer());
    }
    if (errorBlob) errorBlob->Release();

    return hr;
  }

  if (errorBlob) errorBlob->Release();

  return S_OK;
}
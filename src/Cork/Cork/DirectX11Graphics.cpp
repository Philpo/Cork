#include "DirectX11Graphics.h"
#include <iostream>

unique_ptr<DirectX11Graphics> DirectX11Graphics::instance;
int DirectX11Graphics::textureId = 0;
int DirectX11Graphics::shaderId = 0;

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
    catch (exception&) {
      throw;
    }
  }
  return *instance;
}

void DirectX11Graphics::receiveMessage(IMessage& message) {
  try {
    if (message.getType() == BEGIN_FRAME_MESSAGE) {
      beginFrame();
    }
    else if (message.getType() == SWAP_BUFFER_MESSAGE) {
      swap();
    }
    else if (message.getType() == DRAW_MESSAGE) {
      DrawInfo data = *(DrawInfo*) message.getData();
      draw(data);
    }
    else if (message.getType() == SET_CONSTANT_BUFFER) {
      BinaryData* cb = (BinaryData*) message.getData();
      setConstantBuffer(cb);
    }
    else if (message.getType() == SET_CAMERA) {
      Camera camera = *(Camera*) message.getData();
      setCamera(camera);
    }
    else if (message.getType() == SET_LIGHT) {
      Light light = *(Light*) message.getData();
      setLight(light);
    }
    else if (message.getType() == SET_INPUT_LAYOUT) {
      ID3D11InputLayout* const layout = (ID3D11InputLayout* const) message.getData();
      bindInputLayout(layout);
    }
    else if (message.getType() == SET_SHADER) {
      int shaderId = *(int*) message.getData();
      setShader(shaderId);
    }
    else if (message.getType() == LOAD_TEXTURE) {
      TextureInfo& info = *(TextureInfo*) message.getData();
      loadTexture(info);
    }
    else if (message.getType() == LOAD_MESH) {
      Mesh& mesh = *(Mesh*) message.getData();
      loadMesh(mesh);
    }
    else if (message.getType() == LOAD_SHADER) {
      ShaderInfo& info = *(ShaderInfo*) message.getData();
      loadShader(info);
    }
    else if (message.getType() == LOAD_INPUT_LAYOUT) {
      InputLayoutInfo& info = *(InputLayoutInfo*) message.getData();
      loadInputLayout(info);
    }
    else if (message.getType() == CREATE_CONSTANT_BUFFER) {
      size_t size = *(size_t*) message.getData();
      createConstantBuffer(size);
    }
  }
  catch (exception&) {
    throw;
  }
}

void DirectX11Graphics::cleanup() {
  for (auto kvp : vertexBuffers) {
    kvp.second->Release();
  }

  for (auto kvp : indexBuffers) {
    kvp.second->Release();
  }

  for (auto kvp : vertexShaderBlobs) {
    kvp.second->Release();
  }

  if (immediateContext) immediateContext->ClearState();
  if (anistropicSampler) anistropicSampler->Release();
  if (constantBuffer) constantBuffer->Release();
  if (renderTargetView) renderTargetView->Release();
  if (swapChain) swapChain->Release();
  if (depthStencilView) depthStencilView->Release();
  if (depthStencilBuffer) depthStencilBuffer->Release();
  if (depthStencilState) depthStencilState->Release();
  if (solidState) solidState->Release();
  if (immediateContext) immediateContext->Release();

  d3dDevice->QueryInterface(&debug);
  debug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);

  if (d3dDevice) d3dDevice->Release();
  if (debug) debug->Release();

  vertexBuffers.clear();
  indexBuffers.clear();
  vertexShaderBlobs.clear();

  initialised = false;
}

void DirectX11Graphics::loadTexture(TextureInfo& info) const {
  ID3D11ShaderResourceView* tex;
  wstring file(info.filePath.begin(), info.filePath.end());
  HRESULT hr = CreateDDSTextureFromFile(d3dDevice, file.c_str(), nullptr, &tex);

  if (FAILED(hr)) {
    throw exception(("error reading texture from " + info.filePath).c_str());
  }

  info.texture = new DirectX11Texture(textureId++, *tex);
}

void DirectX11Graphics::loadMesh(const Mesh& mesh) {
  vector<BinaryData* const> vertices = mesh.getVertices();
  vector<int> indices = mesh.getIndices();

  int bufferSize = vertices.size() * vertices[0]->getSizeInBytes();
  char* vertexData = new char[bufferSize];

  for (unsigned i = 0; i < vertices.size(); i++) {
    BinaryData* const vertex = vertices[i];
    copy(vertex->getData(), vertex->getData() + vertex->getSizeInBytes(), stdext::make_checked_array_iterator(vertexData + (i * vertex->getSizeInBytes()), bufferSize));
  }

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = bufferSize;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = vertexData;

  ID3D11Buffer* vertexBuffer;
  HRESULT hr = d3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

  delete[] vertexData;

  if (FAILED(hr)) {
    throw exception("error loading mesh");
  }

  int* indexData = new int[indices.size()];

  for (unsigned i = 0; i < indices.size(); i++) {
    indexData[i] = indices[i];
  }

  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(int) * indices.size();
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;

  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = indexData;
  ID3D11Buffer* indexBuffer;
  hr = d3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

  delete[] indexData;

  if (FAILED(hr)) {
    throw exception("error loading mesh");
  }

  vertexBuffers.insert(pair<int, ID3D11Buffer* const>(mesh.getId(), vertexBuffer));
  indexBuffers.insert(pair<int, ID3D11Buffer* const>(mesh.getId(), indexBuffer));
}

void DirectX11Graphics::loadShader(ShaderInfo& info) {
  HRESULT hr;
  ID3D11DeviceChild* genericShader = nullptr;
  string type;

  ID3DBlob* blob = nullptr;
  wstring file(info.shaderFile.begin(), info.shaderFile.end());
  hr = compileShaderFromFile(file.c_str(), info.name.c_str(), info.shaderModel.c_str(), &blob);

  if (FAILED(hr)) {
    throw exception(("error loading shader " + info.shaderFile).c_str());
  }

  if (info.shaderModel.find("vs") != string::npos) {
    type = "VS";
    ID3D11VertexShader* vertexShader;
    hr = d3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);

    if (FAILED(hr)) {
      blob->Release();
      throw exception(("error loading shader " + info.shaderFile).c_str());
    }
    genericShader = vertexShader;
    vertexShaderBlobs.insert(pair<int, ID3DBlob* const>(shaderId, blob));
  }
  else if (info.shaderModel.find("ps") != string::npos) {
    type = "PS";
    ID3D11PixelShader* pixelShader;
    hr = d3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);

    if (FAILED(hr)) {
      blob->Release();
      throw exception(("error loading shader " + info.shaderFile).c_str());
    }
    genericShader = pixelShader;
    blob->Release();
  }

  IShader* temp = new DirectX11Shader;
  temp->setShader(genericShader);
  temp->setType(type);
  info.shader = temp;
  info.shaderId = shaderId++;
}

void DirectX11Graphics::loadInputLayout(InputLayoutInfo& info) {
  if (vertexShaderBlobs.find(info.vertexShader) != vertexShaderBlobs.end()) {
    ID3D11InputLayout* temp = nullptr;
    ID3DBlob* const blob = vertexShaderBlobs[info.vertexShader];
    HRESULT hr = d3dDevice->CreateInputLayout(info.layout, info.numElements, blob->GetBufferPointer(), blob->GetBufferSize(), &temp);

    if (FAILED(hr)) {
      throw exception("error loading input layout");
    }

    blob->Release();
    vertexShaderBlobs.erase(info.vertexShader);

    info.inputLayout = temp;
  }
}

void DirectX11Graphics::createConstantBuffer(size_t sizeInBytes) {
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeInBytes;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  HRESULT hr = d3dDevice->CreateBuffer(&bd, nullptr, &constantBuffer);

  if (FAILED(hr)) {
    throw exception("error creating constant buffer");
  }
}

HRESULT DirectX11Graphics::initialise() {
  HRESULT hr = initDevice();

  if (FAILED(hr)) {
    return hr;
  }

  return S_OK;
}

void DirectX11Graphics::setLight(Light light) {
  LightStruct toSet;

  toSet.ambient = XMFLOAT4(light.ambient.getX(), light.ambient.getY(), light.ambient.getZ(), 1.0f);
  toSet.diffuse = XMFLOAT4(light.diffuse.getX(), light.diffuse.getY(), light.diffuse.getZ(), 1.0f);
  toSet.specular = XMFLOAT4(light.specular.getX(), light.specular.getY(), light.specular.getZ(), 1.0f);
  toSet.position = XMFLOAT3(light.position.getX(), light.position.getY(), light.position.getZ());
  toSet.range = light.range;
  toSet.direction = XMFLOAT3(light.direction.getX(), light.direction.getY(), light.direction.getZ());
  toSet.exponent = light.exponent;
  toSet.attenuation = XMFLOAT3(light.attenuation.getX(), light.attenuation.getY(), light.attenuation.getZ());
  toSet.enabled = light.enabled;
  toSet.type = light.type;

  cb->updateData(light.cbVariableName, toSet);
}

void DirectX11Graphics::setCamera(Camera camera) {
  XMVECTOR eye = XMLoadFloat4(&XMFLOAT4(camera.position.getX(), camera.position.getY(), camera.position.getZ(), 0.0f));
  XMVECTOR at = XMLoadFloat4(&XMFLOAT4(camera.look.getX(), camera.look.getY(), camera.look.getZ(), 0.0f));
  XMVECTOR worldUp = XMLoadFloat4(&XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f));
  cb->updateData("view", XMMatrixTranspose(XMMatrixLookToLH(eye, at, worldUp)));
  cb->updateData("eyePosW", XMFLOAT3(camera.position.getX(), camera.position.getY(), camera.position.getZ()));
}

void DirectX11Graphics::bindInputLayout(ID3D11InputLayout* const layout) {
  immediateContext->IASetInputLayout(layout);
}

void DirectX11Graphics::setShader(int shaderId) {
  IShader* const shader = ResourceManager::getShader(shaderId);

  if (shader) {
    if (shader->getType() == "VS") {
      immediateContext->VSSetShader((ID3D11VertexShader*) shader->getShader(), nullptr, 0);
    }
    else if (shader->getType() == "PS") {
      immediateContext->PSSetShader((ID3D11PixelShader*) shader->getShader(), nullptr, 0);
    }
  }
}

void DirectX11Graphics::beginFrame() {
  float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
  immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
  immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
  immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);
}

void DirectX11Graphics::draw(DrawInfo data) {
  XMMATRIX world = XMMatrixIdentity();
  XMMATRIX translation = XMMatrixTranslation(data.transform.position.getX(), data.transform.position.getY(), data.transform.position.getZ());
  XMMATRIX scale = XMMatrixScaling(data.transform.scale.getX(), data.transform.scale.getY(), data.transform.scale.getZ());
  XMMATRIX xRotation = XMMatrixRotationX(XMConvertToRadians(data.transform.localRotation.getX()));
  XMMATRIX yRotation = XMMatrixRotationY(XMConvertToRadians(data.transform.localRotation.getY()));
  XMMATRIX zRotation = XMMatrixRotationZ(XMConvertToRadians(data.transform.localRotation.getZ()));
  XMMATRIX worldXRotation = XMMatrixRotationX(XMConvertToRadians(data.transform.worldRotation.getX()));
  XMMATRIX worldYRotation = XMMatrixRotationY(XMConvertToRadians(data.transform.worldRotation.getY()));
  XMMATRIX worldZRotation = XMMatrixRotationZ(XMConvertToRadians(data.transform.worldRotation.getZ()));
  world = world * scale * xRotation * yRotation * zRotation * translation * worldXRotation * worldYRotation * worldZRotation;

  Transform* parent = data.transform.parent;
  while (parent) {
    XMMATRIX parentTranslation = XMMatrixTranslation(parent->position.getX(), parent->position.getY(), parent->position.getZ());
    XMMATRIX parentXRotation = XMMatrixRotationX(XMConvertToRadians(parent->worldRotation.getX()));
    XMMATRIX parentYRotation = XMMatrixRotationY(XMConvertToRadians(parent->worldRotation.getY()));
    XMMATRIX parentZRotation = XMMatrixRotationZ(XMConvertToRadians(parent->worldRotation.getZ()));
    world *= parentTranslation * parentXRotation * parentYRotation * parentZRotation;
    parent = parent->parent;
  }

  cb->updateData("world", XMMatrixTranspose(world));

  Mesh* mesh = ResourceManager::getMesh(data.meshId);
  MeshMaterial meshMaterial = mesh->getMaterial();

  Material material;
  material.ambient = XMFLOAT4(meshMaterial.ambient.getX(), meshMaterial.ambient.getY(), meshMaterial.ambient.getZ(), meshMaterial.alpha);
  material.diffuse = XMFLOAT4(meshMaterial.diffuse.getX(), meshMaterial.diffuse.getY(), meshMaterial.diffuse.getZ(), meshMaterial.alpha);
  material.specular = XMFLOAT4(meshMaterial.specular.getX(), meshMaterial.specular.getY(), meshMaterial.specular.getZ(), meshMaterial.alpha);
  material.specularPower = meshMaterial.specularPower;

  cb->updateData("material", material);
  
  for (unsigned i = 0; i < mesh->getTextures().size(); i++) {
    ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*) ResourceManager::getTexture(mesh->getTextures()[i])->getTexture();
    immediateContext->PSSetShaderResources(i, 1, &texture);
  }

  UINT stride = mesh->getVertices()[0]->getSizeInBytes();
  UINT offset = 0;

  immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, cb->getData(), 0, 0);
  immediateContext->IASetVertexBuffers(0, 1, &vertexBuffers.at(data.meshId), &stride, &offset);
  immediateContext->IASetIndexBuffer(indexBuffers.at(data.meshId), DXGI_FORMAT_R32_UINT, 0);
  immediateContext->DrawIndexed(mesh->getIndices().size(), 0, 0);
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

  // Set primitive topology
  immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

HRESULT DirectX11Graphics::compileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) const {
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
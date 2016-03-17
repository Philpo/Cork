#include "DirectX11Graphics.h"
#include <iostream>

unique_ptr<DirectX11Graphics> DirectX11Graphics::instance;
int DirectX11Graphics::textureId = 0;

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
  if (depthStencilView) depthStencilView->Release();
  if (depthStencilBuffer) depthStencilBuffer->Release();
  if (depthStencilState) depthStencilState->Release();
  if (solidState) solidState->Release();
  if (immediateContext) immediateContext->Release();

  d3dDevice->QueryInterface(&debug);
  debug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);

  if (d3dDevice) d3dDevice->Release();
  if (debug) debug->Release();

  initialised = false;
}

HRESULT DirectX11Graphics::loadTexture(const string& textureFile, ITexture*& texture) const {
  ID3D11ShaderResourceView* tex;
  wstring file(textureFile.begin(), textureFile.end());
  HRESULT hr = CreateDDSTextureFromFile(d3dDevice, file.c_str(), nullptr, &tex);

  if (FAILED(hr)) {
    return hr;
  }

  texture = new DirectX11Texture(textureId++, *tex);

  return S_OK;
}

HRESULT DirectX11Graphics::loadMesh(const Mesh& mesh) {
  vector<BinaryData* const> vertices = mesh.getVertices();
  vector<int> indices = mesh.getIndices();

  int bufferSize = vertices.size() * vertices[0]->getSizeInBytes();
  char* vertexData = new char[bufferSize];

  for (int i = 0; i < vertices.size(); i++) {
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
    return hr;
  }

  int* indexData = new int[indices.size()];

  for (int i = 0; i < indices.size(); i++) {
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
    return hr;
  }

  vertexBuffers.insert(pair<int, ID3D11Buffer* const>(mesh.getId(), vertexBuffer));
  indexBuffers.insert(pair<int, ID3D11Buffer* const>(mesh.getId(), indexBuffer));
  indexCounts.insert(pair<int, int>(mesh.getId(), indices.size()));

  return S_OK;
}

HRESULT DirectX11Graphics::initialise() {
  HRESULT hr = initDevice();

  if (FAILED(hr)) {
    return hr;
  }

  //cb = new DirectX11ConstantBuffer(sizeof(ConstantBuffer));

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

void DirectX11Graphics::beginFrame() {
  float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
  immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
  immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

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

  Material material;
  material.diffuse = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
  material.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
  material.specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
  material.specularPower = 10.0f;

  //cb->clearBuffer();
  //cb->addMatrix("world", &XMMatrixTranspose(world));
  //cb->addMatrix("view", &XMMatrixTranspose(view));
  //cb->addMatrix("projection", &XMMatrixTranspose(projection));
  //cb->addLight("light1", &light);
  //cb->addMaterial("material", &material);
  //cb->addFloat3("eyePosW", &XMFLOAT3(0.0f, 2.0f, -10.0f));
  //cb->addInt("enableTexturing", 1);
  //cb->addInt("enableSpecularMapping", 1);
  //cb->addInt("enableBumpMapping", 1);
  //cb->addInt("enableClipTestig", 1);
  //cb->addFloat("fogStart", 40.0f);
  //cb->addFloat("fogRange", 50.0f);
  //cb->addFloat2("padding", &XMFLOAT2(0.0f, 0.0f));
  //cb->addFloat4("fogColour", &XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

  immediateContext->VSSetShader(vertexShader, nullptr, 0);
  immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
  immediateContext->PSSetShader(pixelShader, nullptr, 0);
  immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);
}

void DirectX11Graphics::draw(DrawInfo data) {
  UINT stride = sizeof(SimpleVertex);
  UINT offset = 0;

  XMMATRIX world = XMMatrixIdentity();
  XMMATRIX translation = XMMatrixTranslation(data.transform.position.getX(), data.transform.position.getY(), data.transform.position.getZ());
  XMMATRIX scale = XMMatrixScaling(data.transform.scale.getX(), data.transform.scale.getY(), data.transform.scale.getZ());
  XMMATRIX xRotation = XMMatrixRotationX(convertDegreesToRadians(data.transform.localRotation.getX()));
  XMMATRIX yRotation = XMMatrixRotationY(convertDegreesToRadians(data.transform.localRotation.getY()));
  XMMATRIX zRotation = XMMatrixRotationZ(convertDegreesToRadians(data.transform.localRotation.getZ()));
  XMMATRIX worldXRotation = XMMatrixRotationX(convertDegreesToRadians(data.transform.worldRotation.getX()));
  XMMATRIX worldYRotation = XMMatrixRotationY(convertDegreesToRadians(data.transform.worldRotation.getY()));
  XMMATRIX worldZRotation = XMMatrixRotationZ(convertDegreesToRadians(data.transform.worldRotation.getZ()));
  world = world * scale * xRotation * yRotation * zRotation * translation * worldXRotation * worldYRotation * worldZRotation;

  Transform* parent = data.transform.parent;
  while (parent) {
    XMMATRIX parentTranslation = XMMatrixTranslation(parent->position.getX(), parent->position.getY(), parent->position.getZ());
    XMMATRIX parentXRotation = XMMatrixRotationX(convertDegreesToRadians(parent->worldRotation.getX()));
    XMMATRIX parentYRotation = XMMatrixRotationY(convertDegreesToRadians(parent->worldRotation.getY()));
    XMMATRIX parentZRotation = XMMatrixRotationZ(convertDegreesToRadians(parent->worldRotation.getZ()));
    world *= parentTranslation * parentXRotation * parentYRotation * parentZRotation;
    parent = parent->parent;
  }

  //XMStoreFloat4x4(&objectWorld, temp);
  cb->updateData("world", XMMatrixTranspose(world));
  //*worldMatrix = XMMatrixTranspose(world);
  //cb.mWorld = XMMatrixTranspose(objectWorld);

  Mesh* mesh = ResourceManager::getMesh(data.meshId);
  MeshMaterial meshMaterial = mesh->getMaterial();

  Material material;
  material.ambient = XMFLOAT4(meshMaterial.ambient.getX(), meshMaterial.ambient.getY(), meshMaterial.ambient.getZ(), meshMaterial.alpha);
  material.diffuse = XMFLOAT4(meshMaterial.diffuse.getX(), meshMaterial.diffuse.getY(), meshMaterial.diffuse.getZ(), meshMaterial.alpha);
  material.specular = XMFLOAT4(meshMaterial.specular.getX(), meshMaterial.specular.getY(), meshMaterial.specular.getZ(), meshMaterial.alpha);
  material.specularPower = meshMaterial.specularPower;

  cb->updateData("material", material);
  
  for (int i = 0; i < mesh->getTextures().size(); i++) {
    ID3D11ShaderResourceView* texture = (ID3D11ShaderResourceView*) ResourceManager::getTexture(mesh->getTextures()[i])->getTexture();
    immediateContext->PSSetShaderResources(i, 1, &texture);
  }

  immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, cb->getData(), 0, 0);
  immediateContext->IASetVertexBuffers(0, 1, &vertexBuffers.at(data.meshId), &stride, &offset);
  immediateContext->IASetIndexBuffer(indexBuffers.at(data.meshId), DXGI_FORMAT_R32_UINT, 0);
  immediateContext->DrawIndexed(indexCounts.at(data.meshId), 0, 0);
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
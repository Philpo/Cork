#include "DirectX11Graphics.h"
#include <iostream>

unique_ptr<DirectX11Graphics> DirectX11Graphics::instance;
int DirectX11Graphics::textureId = 0;
int DirectX11Graphics::shaderId = 0;
const vector<size_t> DirectX11Graphics::SUPPORTED_MESSAGES = { 
  BEGIN_FRAME_MESSAGE
, BEGIN_PASS_MESSAGE
, SWAP_BUFFER_MESSAGE
, DRAW_MESSAGE
, SET_CONSTANT_BUFFER_MESSAGE
, REGISTER_TEXTURE_REGISTERS_MESSAGE
, SET_INPUT_LAYOUT_MESSAGE
, SET_SHADER_MESSAGE
, LOAD_TEXTURE_MESSAGE
, LOAD_MESH_MESSAGE
, LOAD_SHADER_MESSAGE
, LOAD_PASS_MESSAGE
, CREATE_RENDER_TARGET_MESSAGE
, CREATE_DEPTH_BUFFER_MESSAGE
, CREATE_VIEWPORT_MESSAGE
, LOAD_INPUT_LAYOUT_MESSAGE
, CREATE_CONSTANT_BUFFER_MESSAGE 
};

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
    else if (message.getType() == BEGIN_PASS_MESSAGE) {
      IPass* pass = (IPass*) message.getData();
      beginPass(*pass);
    }
    else if (message.getType() == SWAP_BUFFER_MESSAGE) {
      swap();
    }
    else if (message.getType() == DRAW_MESSAGE) {
      DrawInfo data = *(DrawInfo*) message.getData();
      draw(data);
    }
    else if (message.getType() == SET_CONSTANT_BUFFER_MESSAGE) {
      BinaryData* cb = (BinaryData*) message.getData();
      setConstantBuffer(cb);
    }
    else if (message.getType() == REGISTER_TEXTURE_REGISTERS_MESSAGE) {
      ShaderTexRegisterInfo info = *(ShaderTexRegisterInfo*) message.getData();
      registerTextureRegisters(info);
    }
    else if (message.getType() == SET_INPUT_LAYOUT_MESSAGE) {
      ID3D11InputLayout* const layout = (ID3D11InputLayout* const) message.getData();
      bindInputLayout(layout);
    }
    else if (message.getType() == SET_SHADER_MESSAGE) {
      int shaderId = *(int*) message.getData();
      setShader(shaderId);
    }
    else if (message.getType() == LOAD_TEXTURE_MESSAGE) {
      TextureInfo& info = *(TextureInfo*) message.getData();
      loadTexture(info);
    }
    else if (message.getType() == LOAD_MESH_MESSAGE) {
      Mesh& mesh = *(Mesh*) message.getData();
      loadMesh(mesh);
    }
    else if (message.getType() == LOAD_SHADER_MESSAGE) {
      ShaderInfo& info = *(ShaderInfo*) message.getData();
      loadShader(info);
    }
    else if (message.getType() == LOAD_PASS_MESSAGE) {
      PassInfo& info = *(PassInfo*) message.getData();
      loadPass(info);
    }
    else if (message.getType() == CREATE_RENDER_TARGET_MESSAGE) {
      CreateInfo& info = *(CreateInfo*) message.getData();
      createRenderTarget(info);
    }
    else if (message.getType() == CREATE_DEPTH_BUFFER_MESSAGE) {
      CreateInfo& info = *(CreateInfo*) message.getData();
      createDepthBuffer(info);
    }
    else if (message.getType() == CREATE_VIEWPORT_MESSAGE) {
      CreateInfo& info = *(CreateInfo*) message.getData();
      createViewport(info);
    }
    else if (message.getType() == LOAD_INPUT_LAYOUT_MESSAGE) {
      InputLayoutInfo& info = *(InputLayoutInfo*) message.getData();
      loadInputLayout(info);
    }
    else if (message.getType() == CREATE_CONSTANT_BUFFER_MESSAGE) {
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

  for (auto kvp : renderTargetViews) {
    if (kvp.second) kvp.second->Release();
  }
  for (auto kvp : renderTargetResourceViews) {
    if (kvp.second) kvp.second->Release();
  }

  if (swapChain) swapChain->Release();

  for (auto kvp : depthBufferViews) {
    if (kvp.second) kvp.second->Release();
  }
  for (auto kvp : depthBufferResourceViews) {
    if (kvp.second) kvp.second->Release();
  }

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
  DirectX11Graphics* temp = instance.release();
  delete temp;
  textureId = 0;
  shaderId = 0;
}

void DirectX11Graphics::loadTexture(TextureInfo& info) const {
  ID3D11ShaderResourceView* tex;
  wstring file(info.filePath.begin(), info.filePath.end());
  HRESULT hr = CreateDDSTextureFromFile(d3dDevice, file.c_str(), nullptr, &tex);

  if (FAILED(hr)) {
    throw exception(("error reading texture from " + info.filePath).c_str());
  }

  info.texture = new DirectX11Texture(textureId++, info.type, *tex);
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

void DirectX11Graphics::loadPass(PassInfo& info) {
  try {
    info.pass = new DirectX11Pass(info.passNode);
  }
  catch (exception&) {
    throw;
  }
}

void DirectX11Graphics::createRenderTarget(CreateInfo& info) {
  D3D11_TEXTURE2D_DESC textureDesc;
  D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
  ID3D11Texture2D* texture;
  ID3D11RenderTargetView* renderTarget;
  ID3D11ShaderResourceView* resourceView = nullptr;
  HRESULT hr;

  if (info.renderToBackBuffer && !UNIT_TESTS) {
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &texture);

    if (FAILED(hr)) {
      throw exception("error getting texture from swap chain");
    }
  }
  else {
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width = info.width;
    textureDesc.Height = info.height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = (DXGI_FORMAT) info.format;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    hr = d3dDevice->CreateTexture2D(&textureDesc, NULL, &texture);
    if (FAILED(hr)) {
      throw exception("error creating texture");
    }
  }

  // Create the render target views.
  hr = d3dDevice->CreateRenderTargetView(texture, nullptr, &renderTarget);
  if (FAILED(hr)) {
    texture->Release();
    throw exception("error creating render target view");
  }

  if (info.createTextureView && !info.renderToBackBuffer) {
    // Setup the description of the shader resource view.
    shaderResourceViewDesc.Format = (DXGI_FORMAT) info.textureViewFormat;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    // Create the shader resource views.
    hr = d3dDevice->CreateShaderResourceView(texture, &shaderResourceViewDesc, &resourceView);
    if (FAILED(hr)) {
      texture->Release();
      renderTarget->Release();
      throw exception("error creating shader resource view");
    }
    renderTargetResourceViews.insert(pair<string, ID3D11ShaderResourceView*>(info.id, resourceView));
  }

  renderTargetViews.insert(pair<string, ID3D11RenderTargetView*>(info.id, renderTarget));

  texture->Release();
}

void DirectX11Graphics::createDepthBuffer(CreateInfo& info) {
  D3D11_TEXTURE2D_DESC depthStencilDesc;
  ID3D11Texture2D* texture;
  ID3D11DepthStencilView* depthStencilView;
  ID3D11ShaderResourceView* resourceView = nullptr;

  depthStencilDesc.Width = info.width;
  depthStencilDesc.Height = info.height;
  depthStencilDesc.MipLevels = 1;
  depthStencilDesc.ArraySize = 1;
  depthStencilDesc.Format = (DXGI_FORMAT) info.format;
  depthStencilDesc.SampleDesc.Count = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
  depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  depthStencilDesc.CPUAccessFlags = 0;
  depthStencilDesc.MiscFlags = 0;

  HRESULT hr = d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &texture);
  if (FAILED(hr)) {
    throw exception("error creating texture");
  }

  D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc;
  viewDesc.Flags = 0;
  viewDesc.Format = (DXGI_FORMAT) info.depthBufferFormat;
  viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  viewDesc.Texture2D.MipSlice = 0;
  hr = d3dDevice->CreateDepthStencilView(texture, &viewDesc, &depthStencilView);
  if (FAILED(hr)) {
    texture->Release();
    throw exception("error creating depth stencil view");
  }

  if (info.createTextureView) {
    D3D11_SHADER_RESOURCE_VIEW_DESC rViewDesc;
    rViewDesc.Format = (DXGI_FORMAT) info.textureViewFormat;
    rViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    rViewDesc.Texture2D.MipLevels = depthStencilDesc.MipLevels;
    rViewDesc.Texture2D.MostDetailedMip = 0;

    hr = d3dDevice->CreateShaderResourceView(texture, &rViewDesc, &resourceView);

    if (FAILED(hr)) {
      texture->Release();
      depthStencilView->Release();
      throw exception("error creating shader resource view");
    }
    depthBufferResourceViews.insert(pair<string, ID3D11ShaderResourceView*>(info.id, resourceView));
  }

  depthBufferViews.insert(pair<string, ID3D11DepthStencilView*>(info.id, depthStencilView));

  texture->Release();
}

void DirectX11Graphics::createViewport(CreateInfo& info) {
  if (viewPorts.find(info.id) == viewPorts.end()) {
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT) info.width;
    vp.Height = (FLOAT) info.height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    viewPorts.insert(pair<string, D3D11_VIEWPORT>(info.id, vp));
  }
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

void DirectX11Graphics::registerTextureRegisters(const ShaderTexRegisterInfo& info) {
  if (shaderTextureRegisters.find(info.shaderId) == shaderTextureRegisters.end()) {
    shaderTextureRegisters.insert(pair<int, map<string, int>>(info.shaderId, info.textureRegisters));
  }
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
    else if (shader->getType() == "HS") {
      immediateContext->HSSetShader((ID3D11HullShader*) shader->getShader(), nullptr, 0);
    }
    else if (shader->getType() == "DS") {
      immediateContext->DSSetShader((ID3D11DomainShader*) shader->getShader(), nullptr, 0);
    }
  }
}

void DirectX11Graphics::beginFrame() {
  //float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
  //immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
  //immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  //immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
  //immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);
}

void DirectX11Graphics::beginPass(const IPass& pass) {
  int renderTargetCount = pass.getNumRenderTargets();
  vector<string> renderTargetIds = pass.getRenderTargets();
  ID3D11RenderTargetView** renderTargets = new ID3D11RenderTargetView*[renderTargetCount];

  for (int i = 0; i < renderTargetCount; i++) {
    renderTargets[i] = renderTargetViews[renderTargetIds[i]];
  }

  immediateContext->OMSetRenderTargets(renderTargetCount, renderTargets, depthBufferViews[pass.getDepthBuffer()]);
  immediateContext->RSSetViewports(1, &viewPorts[pass.getViewPort()]);

  float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha

  for (auto id : renderTargetIds) {
    if (renderTargetViews[id]) {
      immediateContext->ClearRenderTargetView(renderTargetViews[id], ClearColor);
    }
  }

  if (depthBufferViews[pass.getDepthBuffer()]) {
    immediateContext->ClearDepthStencilView(depthBufferViews[pass.getDepthBuffer()], D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  }

  map<int, string> bindTargets = *(map<int, string>*) pass.getRenderTargetBindTargets();

  for (auto kvp : bindTargets) {
    immediateContext->PSSetShaderResources(kvp.first, 1, &renderTargetResourceViews[kvp.second]);
  }

  bindTargets = *(map<int, string>*) pass.getDepthBufferBindTargets();

  for (auto kvp : bindTargets) {
    immediateContext->PSSetShaderResources(kvp.first, 1, &depthBufferResourceViews[kvp.second]);
  }

  immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
  immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);

  delete[] renderTargets;
}

void DirectX11Graphics::draw(DrawInfo data) {
  Mesh* mesh = ResourceManager::getMesh(data.meshId);
  
  if (shaderTextureRegisters.find(data.shaderId) != shaderTextureRegisters.end()) {
    for (auto id : mesh->getTextures()) {
      ITexture* texture = ResourceManager::getTexture(id);
      ID3D11ShaderResourceView* view = (ID3D11ShaderResourceView*) texture->getTexture();
      if (shaderTextureRegisters[data.shaderId].find(texture->getType()) != shaderTextureRegisters[data.shaderId].end()) {
        immediateContext->PSSetShaderResources(shaderTextureRegisters[data.shaderId][texture->getType()], 1, &view);
      }
    }
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
    if (UNIT_TESTS) {
      hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
        D3D11_SDK_VERSION, &d3dDevice, &featureLevel, &immediateContext);
    }
    else {
      hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
        D3D11_SDK_VERSION, &sd, &swapChain, &d3dDevice, &featureLevel, &immediateContext);
    }
    if (SUCCEEDED(hr)) {
      break;
    }
  }

  if (FAILED(hr)) {
    return hr;
  }

  ID3D11Texture2D* depthStencilBuffer;
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

  renderTargetViews.insert(pair<string, ID3D11RenderTargetView*>("null", nullptr));
  renderTargetResourceViews.insert(pair<string, ID3D11ShaderResourceView*>("null", nullptr));
  depthBufferViews.insert(pair<string, ID3D11DepthStencilView*>("null", nullptr));
  depthBufferResourceViews.insert(pair<string, ID3D11ShaderResourceView*>("null", nullptr));

  //depthBufferViews.push_back(nullptr);
  //hr = d3dDevice->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthBufferViews[1]);
  //if (FAILED(hr)) {
  //  return hr;
  //}

  immediateContext->OMSetDepthStencilState(depthStencilState, 0);
  depthStencilBuffer->Release();

  // Create a render target view
  //ID3D11Texture2D* backBuffer = nullptr;
  //hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

  //if (FAILED(hr)) {
  //  return hr;
  //}

  //renderTargetViews.push_back(nullptr);
  //hr = d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetViews[1]);
  //backBuffer->Release();

  //if (FAILED(hr)) {
  //  return hr;
  //}

//  immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

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
  //viewPorts.push_back(vp);
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

  ID3DBlob* errorBlob = nullptr;

  hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &errorBlob);

  if (FAILED(hr)) {
    if (errorBlob != nullptr && !UNIT_TESTS) {
      OutputDebugStringA((char*) errorBlob->GetBufferPointer());
    }
    if (errorBlob) errorBlob->Release();

    return hr;
  }

  if (errorBlob) errorBlob->Release();

  return S_OK;
}
#pragma once
#include "IGraphics.h"
#include "GraphicsTypeDefs.h"
#include "DirectX11TypeDefs.h"
#include "DDSTextureLoader.h"
#include "Vector3.h"
#include "BinaryData.h"
#include "DirectX11Texture.h"
#include "DirectX11Shader.h"
#include "ResourceManager.h"
#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <exception>
#include "Window.h"

using namespace std;
using namespace DirectX;

class DirectX11Graphics : public IGraphics {
public:
  ~DirectX11Graphics() {}

  static DirectX11Graphics& getGraphics();

  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void cleanup() override;
private:
  DirectX11Graphics();
  void receiveMessage(IMessage& message) override;
  HRESULT initialise() override;
  HRESULT initDevice();
  HRESULT compileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) const;
  void beginFrame() override;
  void setConstantBuffer(BinaryData* const cb) { this->cb = cb; }
  void setShader(int shaderId) override;
  void registerTextureRegisters(const ShaderTexRegisterInfo& info);
  void bindInputLayout(ID3D11InputLayout* const layout);
  void draw(DrawInfo data) override;
  void swap() const override;
  void loadTexture(TextureInfo& info) const override;
  void loadMesh(const Mesh& mesh) override;
  void loadShader(ShaderInfo& info) override;
  void loadInputLayout(InputLayoutInfo& info);
  void createConstantBuffer(size_t sizeInBytes);

  static unique_ptr<DirectX11Graphics> instance;
  static int textureId, shaderId;
  bool initialised = false;
  map<int, ID3D11Buffer* const> vertexBuffers;
  map<int, ID3D11Buffer* const> indexBuffers;
  map<int, ID3DBlob* const> vertexShaderBlobs;
  map<int, map<string, int>> shaderTextureRegisters;
  static const vector<string> SUPPORTED_MESSAGES;

  HWND window;
  D3D_DRIVER_TYPE driverType;
  D3D_FEATURE_LEVEL featureLevel;
  ID3D11Device* d3dDevice;
  ID3D11DeviceContext* immediateContext;
  IDXGISwapChain* swapChain;
  ID3D11RenderTargetView* renderTargetView;
  ID3D11Buffer* constantBuffer;
  ID3D11SamplerState* anistropicSampler;
  ID3D11DepthStencilView* depthStencilView;
  ID3D11Texture2D* depthStencilBuffer;
  ID3D11DepthStencilState* depthStencilState;
  ID3D11RasterizerState* solidState;
  ID3D11Debug* debug;
  BinaryData* cb;
};
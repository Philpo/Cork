#pragma once
#include "IGraphics.h"
#include "DirectX11TypeDefs.h"
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

  void cleanup() override;
  HRESULT loadTexture(const string& textureFile, ITexture*& texture) const override;
  HRESULT loadMesh(const Mesh& mesh) override;
private:
  DirectX11Graphics();
  void receiveMessage(IMessage& message) override;
  HRESULT initialise() override;
  HRESULT initDevice();
  HRESULT compileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
  HRESULT initShadersAndInputLayout();
  void draw(int meshId) const override;
  void swap() const override;

  static unique_ptr<DirectX11Graphics> instance;
  bool initialised = false;
  map<int, ID3D11Buffer* const> vertexBuffers;
  map<int, ID3D11Buffer* const> indexBuffers;

  HWND window;
  D3D_DRIVER_TYPE driverType;
  D3D_FEATURE_LEVEL featureLevel;
  ID3D11Device* d3dDevice;
  ID3D11DeviceContext* immediateContext;
  IDXGISwapChain* swapChain;
  ID3D11RenderTargetView* renderTargetView;
  ID3D11VertexShader* vertexShader;
  ID3D11PixelShader* pixelShader;
  ID3D11InputLayout* vertexLayout;
  ID3D11Buffer* constantBuffer;
  ID3D11SamplerState* anistropicSampler;
  ID3D11DepthStencilView* depthStencilView;
  ID3D11Texture2D* depthStencilBuffer;
  ID3D11RasterizerState* solidState;
};
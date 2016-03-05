#pragma once
#include "IGraphics.h"
#include "DirectX11TypeDefs.h"
#include "DDSTextureLoader.h"
#include "Vector3.h"
#include "DirectX11ConstantBuffer.h"
#include "DirectX11Texture.h"
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
  void beginFrame() override;
  void draw(int meshId) override;
  void swap() const override;

  static unique_ptr<DirectX11Graphics> instance;
  static int textureId;
  bool initialised = false;
  map<int, ID3D11Buffer* const> vertexBuffers;
  map<int, ID3D11Buffer* const> indexBuffers;
  map<int, UINT> indexCounts;

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
  ID3D11DepthStencilState* depthStencilState;
  ID3D11RasterizerState* solidState;
  ID3D11Debug* debug;
  IConstantBuffer* cb;
  XMMATRIX* worldMatrix;
  XMFLOAT4X4 objectWorld;
  int t = 0;
  Vector3<float> camPos;
};
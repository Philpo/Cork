#include "stdafx.h"
#include "catch.hpp"
#include "MessageHandler.h"
#include "Message.h"
#include "DirectX11Graphics.h"
#include "Mesh.h"
#include "ServiceLocator.h"
#include "Factory.h"
#include "DirectX11XMLMeshLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace directx11graphics {
    Factory factory;

    TEST_CASE("test directxgraphics getGraphics") {
      REQUIRE_NOTHROW(DirectX11Graphics::getGraphics());
    }

    TEST_CASE("test directxgraphics loadTexture") {
      ITexture* tex = nullptr;
      string type = "test";
      string file = "..\\CorkUnitTests\\Crate_COLOR.dds";
      TextureInfo info(type, file, tex);

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(LOAD_TEXTURE_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      REQUIRE((tex != nullptr));
      REQUIRE(tex->getType() == type);
      REQUIRE((tex->getTexture() != nullptr));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics loadMesh") {
      ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));
      Mesh::addMeshFileLoader(".xml", loadXMLMesh);

      string file = "..\\CorkUnitTests\\cube_mesh.xml";
      Mesh* mesh = new Mesh(0, file);

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(LOAD_MESH_MESSAGE, mesh, &DirectX11Graphics::getGraphics())));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics loadShader") {
      string file = "..\\CorkUnitTests\\test_shader.fx";
      string name = "VS";
      string model = "vs_4_0";
      IShader* shader;
      ShaderInfo info(file, name, model, shader);

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(LOAD_SHADER_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      REQUIRE((shader != nullptr));
      REQUIRE(shader->getType() == "VS");
      REQUIRE((shader->getShader() != nullptr));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics loadPass") {
      file<> file("..\\CorkUnitTests\\passes.xml");
      xml_document<> doc;
      doc.parse<0>(file.data());
      xml_node<>* rootNode = doc.first_node();
      xml_node<>* passNode = rootNode->first_node();
      IPass* pass;
      PassInfo info(passNode, pass);

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(LOAD_PASS_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      REQUIRE((pass != nullptr));
      REQUIRE(pass->getDepthBuffer() == "DepthBuffer");
      REQUIRE(pass->getNumRenderTargets() == 1);
      REQUIRE(pass->getRenderTargets().size() == 1);
      REQUIRE(pass->getRenderTargets()[0] == "BackBuffer");
      REQUIRE(pass->getViewPort() == "FullHD");
      map<int, string> bindTargets = *(map<int, string>*) pass->getRenderTargetBindTargets();
      REQUIRE(bindTargets.size() == 1);
      REQUIRE(bindTargets.begin()->first == 0);
      REQUIRE(bindTargets.begin()->second == "BackBuffer");
      bindTargets = *(map<int, string>*) pass->getDepthBufferBindTargets();
      REQUIRE(bindTargets.size() == 1);
      REQUIRE(bindTargets.begin()->first == 1);
      REQUIRE(bindTargets.begin()->second == "DepthBuffer");

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics createRenderTarget") {
      CreateInfo info;
      info.height = 1080;
      info.width = 1920;
      info.createTextureView = true;
      info.renderToBackBuffer = false;
      info.id = "test";
      info.format = DXGI_FORMAT_R8G8B8A8_SNORM;
      info.textureViewFormat = DXGI_FORMAT_R8G8B8A8_SNORM;

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(CREATE_RENDER_TARGET_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics createDepthBuffer") {
      CreateInfo info;
      info.height = 1080;
      info.width = 1920;
      info.createTextureView = true;
      info.renderToBackBuffer = false;
      info.id = "test";
      info.format = 44;
      info.depthBufferFormat = 45;
      info.textureViewFormat = 46;

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(CREATE_DEPTH_BUFFER_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics loadInputLayout") {
      string file = "..\\CorkUnitTests\\test_shader.fx";
      string name = "VS";
      string model = "vs_4_0";
      IShader* shader;
      ShaderInfo shaderInfo(file, name, model, shader);

      MessageHandler::forwardMessage(Message(LOAD_SHADER_MESSAGE, &shaderInfo, &DirectX11Graphics::getGraphics()));

      D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
      };
      ID3D11InputLayout* inputLayout = nullptr;
      InputLayoutInfo info(0, layout, ARRAYSIZE(layout), inputLayout);

      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(LOAD_INPUT_LAYOUT_MESSAGE, &info, &DirectX11Graphics::getGraphics())));

      REQUIRE((inputLayout != nullptr));

      DirectX11Graphics::getGraphics().cleanup();
    }

    TEST_CASE("test directxgraphics createConstantBuffer") {
      size_t cbSize = 416;
      REQUIRE_NOTHROW(MessageHandler::forwardMessage(Message(CREATE_CONSTANT_BUFFER_MESSAGE, &cbSize, &DirectX11Graphics::getGraphics())));

      DirectX11Graphics::getGraphics().cleanup();
    }
  }
}
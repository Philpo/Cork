#include "stdafx.h"
#include "catch.hpp"
#include "ResourceManager.h"
#include "Factory.h"
#include "DirectX11XMLMeshLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace resourcemanager {
    Factory factory;

    TEST_CASE("test loadTexture") {
      SECTION("test non-existent file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int texId;
        string type = "test";
        string file = "..\\CorkUnitTests\\Crate_COLOR1.dds";
        REQUIRE_THROWS(ResourceManager::loadTexture(type, file, texId));
      }

      SECTION("test with correct file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int texId;
        string type = "test";
        string file = "..\\CorkUnitTests\\Crate_COLOR.dds";
        ResourceManager::loadTexture(type, file, texId);
        ITexture* tex = ResourceManager::getTexture(texId);
        REQUIRE((tex != nullptr));
        REQUIRE(tex->getId() == texId);
        REQUIRE(texId == 0);
        REQUIRE(tex->getType() == type);
        REQUIRE((tex->getTexture() != nullptr));

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test getTexture") {
      SECTION("test unloaded texture") {
        ITexture* tex = ResourceManager::getTexture(0);
        REQUIRE((tex == nullptr));
      }

      SECTION("test loaded texture") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int texId;
        string type = "test";
        string file = "..\\CorkUnitTests\\Crate_COLOR.dds";
        ResourceManager::loadTexture(type, file, texId);
        ITexture* tex = ResourceManager::getTexture(texId);
        REQUIRE((tex != nullptr));
        REQUIRE(tex->getId() == texId);
        REQUIRE(texId == 0);
        REQUIRE(tex->getType() == type);
        REQUIRE((tex->getTexture() != nullptr));

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test loadMesh") {
      SECTION("test non-existent file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));
        Mesh::addMeshFileLoader(".xml", loadXMLMesh);

        int meshId;
        string file = "..\\CorkUnitTests\\cube_mesh1.xml";
        REQUIRE_THROWS(ResourceManager::loadMesh(file, meshId));
      }

      SECTION("test with correct file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));
        Mesh::addMeshFileLoader(".xml", loadXMLMesh);

        int meshId;
        string file = "..\\CorkUnitTests\\cube_mesh.xml";
        ResourceManager::loadMesh(file, meshId);
        Mesh* mesh = ResourceManager::getMesh(meshId);
        REQUIRE((mesh != nullptr));
        REQUIRE(mesh->getId() == meshId);
        REQUIRE(meshId == 0);
        REQUIRE(mesh->getIndices().size() == 36);
        REQUIRE(mesh->getTextures().size() == 3);
        REQUIRE(mesh->getVertices().size() == 24);

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test getMesh") {
      SECTION("test unloaded mesh") {
        Mesh* mesh = ResourceManager::getMesh(0);
        REQUIRE((mesh == nullptr));
      }

      SECTION("test loaded mesh") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));
        Mesh::addMeshFileLoader(".xml", loadXMLMesh);

        int meshId;
        string file = "..\\CorkUnitTests\\cube_mesh.xml";
        ResourceManager::loadMesh(file, meshId);
        Mesh* mesh = ResourceManager::getMesh(meshId);
        REQUIRE((mesh != nullptr));
        REQUIRE(mesh->getId() == meshId);
        REQUIRE(meshId == 0);
        REQUIRE(mesh->getIndices().size() == 36);
        REQUIRE(mesh->getTextures().size() == 3);
        REQUIRE(mesh->getVertices().size() == 24);

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test loadShader") {
      SECTION("test non-existent file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int shaderId;
        string name = "VS";
        string model = "vs_4_0";
        string file = "..\\CorkUnitTests\\test_shader1.fx";
        REQUIRE_THROWS(ResourceManager::loadShader(file, name, model, shaderId));
      }

      SECTION("test with correct file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int shaderId;
        string name = "VS";
        string model = "vs_4_0";
        string file = "..\\CorkUnitTests\\test_shader.fx";
        ResourceManager::loadShader(file, name, model, shaderId);
        IShader* shader = ResourceManager::getShader(shaderId);
        REQUIRE((shader != nullptr));
        REQUIRE(shader->getType() == "VS");
        REQUIRE(shaderId == 0);
        REQUIRE((shader->getShader() != nullptr));

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test getShader") {
      SECTION("test unloaded shader") {
        IShader* shader = ResourceManager::getShader(0);
        REQUIRE((shader == nullptr));
      }

      SECTION("test loaded shader") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        int shaderId;
        string name = "VS";
        string model = "vs_4_0";
        string file = "..\\CorkUnitTests\\test_shader.fx";
        ResourceManager::loadShader(file, name, model, shaderId);
        IShader* shader = ResourceManager::getShader(shaderId);
        REQUIRE((shader != nullptr));
        REQUIRE(shader->getType() == "VS");
        REQUIRE(shaderId == 0);
        REQUIRE((shader->getShader() != nullptr));

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test loadPass") {
      SECTION("test non-existent file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        vector<IPass* const> passes;
        string file = "..\\CorkUnitTests\\passes1.xml";
        REQUIRE_THROWS(ResourceManager::loadPasses(file, passes));
      }

      SECTION("test with correct file") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        vector<IPass* const> passes;
        string file = "..\\CorkUnitTests\\passes.xml";
        ResourceManager::loadPasses(file, passes);

        REQUIRE(passes.size() == 1);
        IPass* pass = passes[0];
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

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }

    TEST_CASE("test getPass") {
      SECTION("test unloaded pass") {
        IPass* pass = ResourceManager::getPass(0);
        REQUIRE((pass == nullptr));
      }

      SECTION("test loaded pass") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        vector<IPass* const> passes;
        string file = "..\\CorkUnitTests\\passes.xml";
        ResourceManager::loadPasses(file, passes);
        IPass* pass = ResourceManager::getPass(0);

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

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
        ResourceManager::cleanup();
      }
    }
  }
}
#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "ServiceLocator.h"
#include "DirectX11Pass.h"
#include "RapidXML\rapidxml.hpp"
#include "RapidXML\rapidxml_utils.hpp"

using namespace rapidxml;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace directx11pass {
    Factory factory;

    TEST_CASE("test directx11pass constructor") {
      SECTION("test with null node") {
        DirectX11Pass pass(nullptr);

        REQUIRE(pass.getDepthBuffer() == "");
        REQUIRE(pass.getNumRenderTargets() == 0);
        REQUIRE(pass.getRenderTargets().size() == 0);
        REQUIRE(pass.getViewPort() == "");
        map<int, string> bindTargets = *(map<int, string>*) pass.getRenderTargetBindTargets();
        REQUIRE(bindTargets.size() == 0);
        bindTargets = *(map<int, string>*) pass.getDepthBufferBindTargets();
        REQUIRE(bindTargets.size() == 0);
      }

      SECTION("test with correct node") {
        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));

        file<> file("..\\CorkUnitTests\\passes.xml");
        xml_document<> doc;
        doc.parse<0>(file.data());
        xml_node<>* rootNode = doc.first_node();
        xml_node<>* passNode = rootNode->first_node();

        DirectX11Pass pass(passNode); 
        REQUIRE(pass.getDepthBuffer() == "DepthBuffer");
        REQUIRE(pass.getNumRenderTargets() == 1);
        REQUIRE(pass.getRenderTargets().size() == 1);
        REQUIRE(pass.getRenderTargets()[0] == "BackBuffer");
        REQUIRE(pass.getViewPort() == "FullHD");
        map<int, string> bindTargets = *(map<int, string>*) pass.getRenderTargetBindTargets();
        REQUIRE(bindTargets.size() == 1);
        REQUIRE(bindTargets.begin()->first == 0);
        REQUIRE(bindTargets.begin()->second == "BackBuffer");
        bindTargets = *(map<int, string>*) pass.getDepthBufferBindTargets();
        REQUIRE(bindTargets.size() == 1);
        REQUIRE(bindTargets.begin()->first == 1);
        REQUIRE(bindTargets.begin()->second == "DepthBuffer");

        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
      }
    }

    TEST_CASE("test directx11pass setters") {
      DirectX11Pass pass(nullptr);

      string depthBuffer = "DepthBuffer";
      string viewport = "FullHD";
      map<int, string> binds1 = { { 0, "BackBuffer" } };
      map<int, string> binds2 = { { 1, "DepthBuffer" } };
      vector<string> targets = { "BackBuffer" };

      pass.setDepthBuffer(depthBuffer);
      pass.setViewport(viewport);
      pass.setRenderTargets(targets);
      pass.setRenderTargetBindTargets(&binds1);
      pass.setDepthBufferBindTargets(&binds2);

      REQUIRE(pass.getDepthBuffer() == "DepthBuffer");
      REQUIRE(pass.getNumRenderTargets() == 1);
      REQUIRE(pass.getRenderTargets().size() == 1);
      REQUIRE(pass.getRenderTargets()[0] == "BackBuffer");
      REQUIRE(pass.getViewPort() == "FullHD");
      map<int, string> bindTargets = *(map<int, string>*) pass.getRenderTargetBindTargets();
      REQUIRE(bindTargets.size() == 1);
      REQUIRE(bindTargets.begin()->first == 0);
      REQUIRE(bindTargets.begin()->second == "BackBuffer");
      bindTargets = *(map<int, string>*) pass.getDepthBufferBindTargets();
      REQUIRE(bindTargets.size() == 1);
      REQUIRE(bindTargets.begin()->first == 1);
      REQUIRE(bindTargets.begin()->second == "DepthBuffer");
    }
  }
}
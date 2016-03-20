#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace factory {
    Factory factory;

    TEST_CASE("test IComponent functions") {
      IComponent* component = factory.getBasicGraphicsComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(ConsoleGraphicsComponent));
      delete component;

      component = factory.getBasicInputComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(TestInputComponent));
      delete component;

      component = factory.getBasicMovementComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(BasicMovementComponent));
      delete component;
    }

    TEST_CASE("test IDataComponent functions") {
      file<> file("..\\CorkUnitTests\\data_components_test.xml");
      xml_document<> doc;
      doc.parse<0>(file.data());
      xml_node<>* rootNode = doc.first_node();
      xml_node<>* component_node = rootNode->first_node();
      
      IDataComponent* component = factory.getTransformComponent(component_node);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(TransformComponent));
      Transform data = *(Transform*) component->getData();
      REQUIRE(data.position.getX() == approx(0.0f));
      REQUIRE(data.position.getY() == approx(0.0f));
      REQUIRE(data.position.getZ() == approx(0.0f));
      REQUIRE(data.localRotation.getX() == approx(0.0f));
      REQUIRE(data.localRotation.getY() == approx(0.0f));
      REQUIRE(data.localRotation.getZ() == approx(0.0f));
      REQUIRE(data.scale.getX() == approx(2.0f));
      REQUIRE(data.scale.getY() == approx(2.0f));
      REQUIRE(data.scale.getZ() == approx(2.0f));
      REQUIRE(data.worldRotation.getX() == approx(0.0f));
      REQUIRE(data.worldRotation.getY() == approx(0.0f));
      REQUIRE(data.worldRotation.getZ() == approx(0.0f));
      REQUIRE((data.parent == nullptr));
      delete component;

      component_node = component_node->next_sibling();
      component = factory.getCameraComponent(component_node);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(CameraComponent));
      Camera cameraData = *(Camera*) component->getData();
      REQUIRE(cameraData.look.getX() == approx(0.0f));
      REQUIRE(cameraData.look.getY() == approx(0.0f));
      REQUIRE(cameraData.look.getZ() == approx(1.0f));
      REQUIRE(cameraData.right.getX() == approx(1.0f));
      REQUIRE(cameraData.right.getY() == approx(0.0f));
      REQUIRE(cameraData.right.getZ() == approx(0.0f));
      REQUIRE(cameraData.up.getX() == approx(0.0f));
      REQUIRE(cameraData.up.getY() == approx(1.0f));
      REQUIRE(cameraData.up.getZ() == approx(0.0f));
      delete component;

      component_node = component_node->next_sibling();
      component = factory.getLightComponent(component_node);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(LightComponent));
      Light lightData = *(Light*) component->getData();
      REQUIRE(lightData.range == approx(1000.0f));
      REQUIRE(lightData.type == POINT_LIGHT);
      REQUIRE(lightData.ambient.getX() == approx(0.2f));
      REQUIRE(lightData.ambient.getY() == approx(0.2f));
      REQUIRE(lightData.ambient.getZ() == approx(0.2f));
      REQUIRE(lightData.diffuse.getX() == approx(1.0f));
      REQUIRE(lightData.diffuse.getY() == approx(1.0f));
      REQUIRE(lightData.diffuse.getZ() == approx(1.0f));
      REQUIRE(lightData.specular.getX() == approx(0.5f));
      REQUIRE(lightData.specular.getY() == approx(0.5f));
      REQUIRE(lightData.specular.getZ() == approx(0.5f));
      REQUIRE(lightData.attenuation.getX() == approx(0.0f));
      REQUIRE(lightData.attenuation.getY() == approx(0.1f));
      REQUIRE(lightData.attenuation.getZ() == approx(0.0f));
      delete component;
    }
  }
}
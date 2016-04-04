#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace factory {
    Factory factory;

    TEST_CASE("test IComponent functions") {
      SECTION("test IComponent with nullptr") {
        IComponent* component = factory.getBasicInputComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(TestInputComponent));
        delete component;

        component = factory.getBasicMovementComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(BasicMovementComponent));
        delete component;

        component = factory.getUpdatePositionComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(UpdatePositionComponent));
        delete component;

        component = factory.getApplyForceComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ApplyForceComponent));
        delete component;

        component = factory.getJumpComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(JumpComponent));
        delete component;
      }

      SECTION("test IComponent with object") {
        GameObject* go = new GameObject;

        IComponent* component = factory.getBasicInputComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(TestInputComponent));
        delete component;

        component = factory.getBasicMovementComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(BasicMovementComponent));
        delete component;

        component = factory.getUpdatePositionComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(UpdatePositionComponent));
        delete component;

        component = factory.getApplyForceComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ApplyForceComponent));
        delete component;

        component = factory.getJumpComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(JumpComponent));
        delete component;

        delete go;
      }
    }

    TEST_CASE("test IDataComponent functions") {
      SECTION("test IDataComponent with nullptr") {
        IDataComponent* component = factory.getTransformComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(TransformComponent));
        Transform data = *(Transform*) component->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(0.0f));
        REQUIRE(data.position.getZ() == approx(0.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(0.0f));
        REQUIRE(data.previousPosition.getZ() == approx(0.0f));
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
        REQUIRE(data.scale.getX() == approx(0.0f));
        REQUIRE(data.scale.getY() == approx(0.0f));
        REQUIRE(data.scale.getZ() == approx(0.0f));
        REQUIRE(data.worldRotation.getX() == approx(0.0f));
        REQUIRE(data.worldRotation.getY() == approx(0.0f));
        REQUIRE(data.worldRotation.getZ() == approx(0.0f));
        REQUIRE((data.parent == nullptr));
        delete component;

        component = factory.getCameraComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(CameraComponent));
        Camera cameraData = *(Camera*) component->getData();
        REQUIRE(cameraData.look.getX() == approx(0.0f));
        REQUIRE(cameraData.look.getY() == approx(0.0f));
        REQUIRE(cameraData.look.getZ() == approx(0.0f));
        REQUIRE(cameraData.right.getX() == approx(0.0f));
        REQUIRE(cameraData.right.getY() == approx(0.0f));
        REQUIRE(cameraData.right.getZ() == approx(0.0f));
        REQUIRE(cameraData.up.getX() == approx(0.0f));
        REQUIRE(cameraData.up.getY() == approx(0.0f));
        REQUIRE(cameraData.up.getZ() == approx(0.0f));
        delete component;

        component = factory.getLightComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(LightComponent));
        Light lightData = *(Light*) component->getData();
        REQUIRE(lightData.range == approx(0.0f));
        REQUIRE(lightData.ambient.getX() == approx(0.0f));
        REQUIRE(lightData.ambient.getY() == approx(0.0f));
        REQUIRE(lightData.ambient.getZ() == approx(0.00));
        REQUIRE(lightData.diffuse.getX() == approx(0.0f));
        REQUIRE(lightData.diffuse.getY() == approx(0.0f));
        REQUIRE(lightData.diffuse.getZ() == approx(0.0f));
        REQUIRE(lightData.specular.getX() == approx(0.0f));
        REQUIRE(lightData.specular.getY() == approx(0.0f));
        REQUIRE(lightData.specular.getZ() == approx(0.0f));
        REQUIRE(lightData.attenuation.getX() == approx(0.0f));
        REQUIRE(lightData.attenuation.getY() == approx(0.0f));
        REQUIRE(lightData.attenuation.getZ() == approx(0.0f));
        delete component;

        component = factory.getBoundingBoxComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(BoundingBoxComponent));
        BoundingBox boxData = *(BoundingBox*) component->getData();
        REQUIRE(boxData.height == approx(0.0f));
        REQUIRE(boxData.width == approx(0.0f));
        REQUIRE(boxData.depth == approx(0.0f));
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(0.0f));
        REQUIRE(boxData.centre.getZ() == approx(0.0f));
        delete component;

        component = factory.getParticleComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ParticleComponent));
        Particle particleData = *(Particle*) component->getData();
        REQUIRE(particleData.mass == approx(0.0f));
        REQUIRE(particleData.maxSpeed == approx(0.0f));
        REQUIRE(particleData.gravityEnabled);
        REQUIRE(particleData.totalForce.getX() == approx(0.0f));
        REQUIRE(particleData.totalForce.getY() == approx(0.0f));
        REQUIRE(particleData.totalForce.getZ() == approx(0.0f));
        REQUIRE(particleData.acceleration.getX() == approx(0.0f));
        REQUIRE(particleData.acceleration.getY() == approx(0.0f));
        REQUIRE(particleData.acceleration.getZ() == approx(0.0f));
        REQUIRE(particleData.velocity.getX() == approx(0.0f));
        REQUIRE(particleData.velocity.getY() == approx(0.0f));
        REQUIRE(particleData.velocity.getZ() == approx(0.0f));
        REQUIRE(particleData.displacement.getX() == approx(0.0f));
        REQUIRE(particleData.displacement.getY() == approx(0.0f));
        REQUIRE(particleData.displacement.getZ() == approx(0.0f));
        delete component;

        component = factory.getJumpDataComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(JumpDataComponent));
        JumpData jumpData = *(JumpData*) component->getData();
        REQUIRE(jumpData.maxJumpTime == approx(0.0f));
        REQUIRE(jumpData.jumpForce == approx(0.0f));
        REQUIRE(jumpData.jumpControlPower == approx(0.0f));
        REQUIRE(jumpData.jumpTime == approx(0.0f));
        REQUIRE(!jumpData.jumping);
        REQUIRE(!jumpData.falling);
        delete component;
      }

      SECTION("test IDataComponent with data") {
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
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(0.0f));
        REQUIRE(data.previousPosition.getZ() == approx(0.0f));
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

        component_node = component_node->next_sibling();
        component = factory.getBoundingBoxComponent(component_node);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(BoundingBoxComponent));
        BoundingBox boxData = *(BoundingBox*) component->getData();
        REQUIRE(boxData.height == approx(1.0f));
        REQUIRE(boxData.width == approx(1.0f));
        REQUIRE(boxData.depth == approx(1.0f));
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(5.0f));
        REQUIRE(boxData.centre.getZ() == approx(0.0f));
        delete component;

        component_node = component_node->next_sibling();
        component = factory.getParticleComponent(component_node);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ParticleComponent));
        Particle particleData = *(Particle*) component->getData();
        REQUIRE(particleData.mass == approx(1.0f));
        REQUIRE(particleData.maxSpeed == approx(100.0f));
        REQUIRE(particleData.gravityEnabled);
        REQUIRE(particleData.totalForce.getX() == approx(0.0f));
        REQUIRE(particleData.totalForce.getY() == approx(0.0f));
        REQUIRE(particleData.totalForce.getZ() == approx(0.0f));
        REQUIRE(particleData.acceleration.getX() == approx(0.0f));
        REQUIRE(particleData.acceleration.getY() == approx(0.0f));
        REQUIRE(particleData.acceleration.getZ() == approx(0.0f));
        REQUIRE(particleData.velocity.getX() == approx(0.0f));
        REQUIRE(particleData.velocity.getY() == approx(0.0f));
        REQUIRE(particleData.velocity.getZ() == approx(0.0f));
        REQUIRE(particleData.displacement.getX() == approx(0.0f));
        REQUIRE(particleData.displacement.getY() == approx(0.0f));
        REQUIRE(particleData.displacement.getZ() == approx(0.0f));
        delete component;

        component_node = component_node->next_sibling();
        component = factory.getJumpDataComponent(component_node);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(JumpDataComponent));
        JumpData jumpData = *(JumpData*) component->getData();
        REQUIRE(jumpData.maxJumpTime == approx(3.0f));
        REQUIRE(jumpData.jumpForce == approx(1.0f));
        REQUIRE(jumpData.jumpControlPower == approx(2.0f));
        REQUIRE(jumpData.jumpTime == approx(0.0f));
        REQUIRE(!jumpData.jumping);
        REQUIRE(!jumpData.falling);
        delete component;
      }
    }
  }
}
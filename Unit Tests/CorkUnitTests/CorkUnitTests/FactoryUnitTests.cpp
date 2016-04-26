#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "TypeDefs.h"
#include "DirectX11XMLMeshLoader.h"

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

        component = factory.getDirectX11Graphics(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(DirectX11Graphics));
        ((IGraphics*) component)->cleanup();

        component = factory.getApplyForceComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ApplyForceComponent));
        delete component;
      }

      SECTION("test IComponent with object") {
        GameObject* go = new GameObject;

        IComponent* component = factory.getBasicInputComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(TestInputComponent));
        delete component;

        component = factory.getApplyForceComponent(go);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(ApplyForceComponent));
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

        component = factory.getMeshComponent(nullptr);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(MeshComponent));
        int meshData = *(int*) component->getData();
        REQUIRE(meshData == -1);
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

        ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, &factory, std::placeholders::_1));
        Mesh::addMeshFileLoader(".xml", loadXMLMesh);
        component_node = component_node->next_sibling();
        component = factory.getMeshComponent(component_node);
        REQUIRE((component != nullptr));
        REQUIRE(typeid(*component) == typeid(MeshComponent));
        int meshData = *(int*) component->getData();
        REQUIRE(meshData == 0);
        ResourceManager::cleanup();
        ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
      }
    }
  }
}
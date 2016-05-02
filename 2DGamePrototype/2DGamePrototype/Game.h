#pragma once
#include "MessageHandler.h"
#include "Scheduler.h"
#include "Window.h"
#include "Message.h"
#include "ServiceLocator.h"
#include "GameFactory.h"
#include "Mesh.h"
#include "DirectX11XMLMeshLoader.h"
#include "ResourceManager.h"
#include "EntityLoader.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"
#include "ObjectPool.h"
#include "DirectX11Pass.h"
#include "GameComponents.h"

struct LightStruct {
  LightStruct() : range(0.0f), exponent(0.0f), enabled(1) {
    ambient = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
    diffuse = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
    specular = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
    position = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
    direction = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
    attenuation = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
  }

  XMFLOAT4 ambient;
  XMFLOAT4 diffuse;
  XMFLOAT4 specular;
  XMFLOAT3 position;
  float range;
  XMFLOAT3 direction;
  float exponent;
  XMFLOAT3 attenuation;
  int enabled;
  int type;
  XMFLOAT3 padding;
};

struct Material {
  Material() : specularPower(0.0f) {
    ambient = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
    diffuse = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
    specular = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
  }

  XMFLOAT4 ambient, diffuse, specular;
  float specularPower;
};

class Game {
public:
  Game();
  ~Game();

  HRESULT initGame(HINSTANCE instance, int cmdShow);
  WPARAM startGame();

  void loopFunction(double timeSinceLastFrame);
private:
  Scheduler* scheduler;
  GameObject *camera, *player;
  vector<GameObject* const> lights, boxes;
  const GameFactory* factory;
  int meshId, vertexShader, pixelShader;
  float fogStart = 40.0f;
  float fogRange = 50.0f;
  ID3D11InputLayout* inputLayout;
  BinaryData* cb;
  vector<IPass* const> passes;

  void update(double timeSinceLastFrame);
  void draw();

  // performs collision detection on 2 axis-aligned bounding boxes
  bool axisAlignedBoundingBoxCollisionDetection(IDataComponent& lhs, IDataComponent& rhs);
  // resolves collisions by adjusting the position of the first object to touch the second object
  void basicCollisionResolution(const GameObject& lhs, const GameObject& rhs);
  void resolveSceneGraph(GameObject* const entity);
  void resolveViewMatrix(GameObject* const camera);
  void setMaterial(GameObject* const entity);
  void setLight(GameObject* const light);
};
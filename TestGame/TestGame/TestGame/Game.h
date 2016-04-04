#pragma once
#include "MessageHandler.h"
#include "Scheduler.h"
#include "Window.h"
#include "Message.h"
#include "ServiceLocator.h"
#include "Factory.h"
#include "Mesh.h"
#include "DirectX11XMLMeshLoader.h"
#include "ResourceManager.h"
#include "EntityLoader.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"
#include "ObjectPool.h"

class Game {
public:
  Game();
  ~Game();

  HRESULT initGame(HINSTANCE instance, int cmdShow);
  WPARAM startGame();

  void loopFunction(double timeSinceLastFrame);
private:
  Scheduler* scheduler;
  GameObject* camera;
  GameObject* floorPlane;
  vector<GameObject* const> lights, boxes, bullets;
  const Factory* factory;
  int meshId, vertexShader, pixelShader;
  float fogStart = 40.0f;
  float fogRange = 50.0f;
  ID3D11InputLayout* inputLayout;
  BinaryData* cb;
  ObjectPool boxPool;

  void update(double timeSinceLastFrame);
  void draw() const;

  // performs collision detection on 2 axis-aligned bounding boxes
  bool axisAlignedBoundingBoxCollisionDetection(IDataComponent& lhs, IDataComponent& rhs);
  // resolves collisions by adjusting the position of the first object to touch the second object
  void basicCollisionResolution(const GameObject& lhs, const GameObject& rhs);
};
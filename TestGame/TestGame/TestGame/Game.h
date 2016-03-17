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
  vector<GameObject* const> lights, boxes;
  const Factory* factory;
  int meshId;
  BinaryData* cb;
};
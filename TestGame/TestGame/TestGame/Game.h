#pragma once
#include "MessageHandler.h"
#include "Scheduler.h"
#include "Window.h"
#include "Message.h"
#include "TestInputComponent.h"
#include "BasicMovementComponent.h"
#include "ConsoleGraphicsComponent.h"

class Game {
public:
  Game();
  ~Game();

  HRESULT initGame(HINSTANCE instance, int cmdShow);
  WPARAM startGame();

  void loopFunction(double timeSinceLastFrame);
private:
  Window window;
  Scheduler* scheduler;
  GameObject* entity;
};
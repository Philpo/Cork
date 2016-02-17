#include "Game.h"

Game::Game() : scheduler(nullptr) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (player) {
    delete player;
  }
}

HRESULT Game::initGame(HINSTANCE instance, int cmdShow) {
  HRESULT hr = window.initWindow(instance, cmdShow);
  if (FAILED(hr)) {
    return hr;
  }

  scheduler = new Scheduler(window, 60.0, L"Test Game");
  scheduler->setGameLoopFunction(std::bind(&Game::loopFunction, this, std::placeholders::_1));

  player = new Player(Vector3<float>());
  scheduler->registerPollComponent(new TestInputComponent(*player));
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  if (player) {
    player->draw();
  }
}
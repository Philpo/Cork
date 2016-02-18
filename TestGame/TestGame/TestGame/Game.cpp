#include "Game.h"

Game::Game() : scheduler(nullptr) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (player) {
    delete player;
  }
  if (entity) {
    delete entity;
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
  entity = new GameObject(Vector3<float>());
  entity->addFunctionalComponent(INPUT_RECEIVED_MESSAGE, new BasicMovementComponent(*entity));
  entity->addFunctionalComponent(DRAW_MESSAGE, new ConsoleGraphicsComponent());
  scheduler->registerPollComponent(new TestInputComponent(*entity));
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  if (entity) {
    DrawMessage m;
    m.setData(&entity->getPositon());
    entity->receiveMessage(m);
  }
  //if (player) {
  //  player->draw();
  //}
}
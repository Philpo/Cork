#include "Game.h"

Game::Game() : scheduler(nullptr), factory(&Factory::getFactory()) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (entity) {
    delete entity;
  }
  Factory::deleteFactory();
  ServiceLocator::cleanup();
}

HRESULT Game::initGame(HINSTANCE instance, int cmdShow) {
  HRESULT hr = window.initWindow(instance, cmdShow);
  if (FAILED(hr)) {
    return hr;
  }

  scheduler = new Scheduler(window, 60.0, L"Test Game");
  scheduler->setGameLoopFunction(std::bind(&Game::loopFunction, this, std::placeholders::_1));

  ServiceLocator::addFactoryFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, factory));
  ServiceLocator::addFactoryFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getBasicGraphicsComponent, factory));
  ServiceLocator::addFactoryFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory));

  entity = new GameObject(Vector3<float>());

  BasicMovementComponent* m = (BasicMovementComponent*) ServiceLocator::getComponent(BASIC_MOVE_COMPONENT);
  m->setTarget(entity);
  entity->addFunctionalComponent(INPUT_RECEIVED_MESSAGE, m);

  entity->addFunctionalComponent(DRAW_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));

  TestInputComponent* t = (TestInputComponent*) ServiceLocator::getComponent(INPUT_COMPONENT);
  t->setPlayer(entity);
  scheduler->registerPollComponent(POLL_INPUT_MESSAGE, t);

  return 1;
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  if (entity) {
    MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &entity->getPositon(), entity->getMessageHandler(DRAW_MESSAGE)));
  }
  //if (player) {
  //  player->draw();
  //}
}
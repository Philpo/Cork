#include "Game.h"

Game::Game() : scheduler(nullptr), factory(&Factory::getFactory()) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (entity) {
    delete entity;
  }

  ServiceLocator::cleanup();
}

HRESULT Game::initGame(HINSTANCE instance, int cmdShow) {
  HRESULT hr = Window::initWindow(instance, cmdShow);
  if (FAILED(hr)) {
    return hr;
  }

  scheduler = new Scheduler(60.0, L"Test Game");
  scheduler->setGameLoopFunction(std::bind(&Game::loopFunction, this, std::placeholders::_1));

  ServiceLocator::addFactoryFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, factory));
  //ServiceLocator::addFactoryFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getBasicGraphicsComponent, factory));
  ServiceLocator::addFactoryFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, factory));
  ServiceLocator::addFactoryFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory));

  entity = new GameObject(Vector3<float>());

  BasicMovementComponent* m = (BasicMovementComponent*) ServiceLocator::getComponent(BASIC_MOVE_COMPONENT);
  m->setTarget(entity);
  entity->addComponent(INPUT_RECEIVED_MESSAGE, m);

  TestInputComponent* t = (TestInputComponent*) ServiceLocator::getComponent(INPUT_COMPONENT);
  t->setPlayer(entity);
  scheduler->registerPollComponent(POLL_INPUT_MESSAGE, t);

  try {
    entity->addComponent(DRAW_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
  }
  catch (exception& e) {
    cout << e.what() << endl;
    return -1;
  }

  return S_OK;
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
#include "Game.h"

Game::Game() : scheduler(nullptr), factory(&Factory::getFactory()) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (entity) {
    delete entity;
  }
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

  entity = new GameObject(Vector3<float>(0.0f, 2.0f, -10.0f));
  box = new GameObject;

  BasicMovementComponent* m = (BasicMovementComponent*) ServiceLocator::getComponent(BASIC_MOVE_COMPONENT);
  m->setTarget(entity);
  entity->addComponent(INPUT_RECEIVED_MESSAGE, m);

  TestInputComponent* t = (TestInputComponent*) ServiceLocator::getComponent(INPUT_COMPONENT);
  t->setPlayer(entity);
  scheduler->registerPollComponent(POLL_INPUT_MESSAGE, t);

  TransformComponent* transform = new TransformComponent;
  Transform data;
  data.position = Vector3<float>(0.0f, 2.0f, -10.0f);
  transform->setData(&data);
  entity->addDataComponent(TRANSFORM_COMPONENT, transform);

  transform = new TransformComponent;
  data.position = Vector3<float>();
  data.scale = Vector3<float>(2.0f, 2.0f, 2.0f);
  transform->setData(&data);
  box->addDataComponent(TRANSFORM_COMPONENT, transform);

  try {
    entity->addComponent(DRAW_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
    entity->addComponent(BEGIN_FRAME_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
    entity->addComponent(SWAP_BUFFER_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));

    box->addComponent(DRAW_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
    box->addComponent(BEGIN_FRAME_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
    box->addComponent(SWAP_BUFFER_MESSAGE, ServiceLocator::getComponent(GRAPHICS_COMPONENT));
  }
  catch (exception& e) {
    cout << e.what() << endl;
    return -1;
  }

  Mesh::addMeshFileLoader(".xml", loadXMLMesh);
  string meshFile = "cube_mesh.xml";
  hr = ResourceManager::loadMesh(meshFile, meshId);

  //mesh = new Mesh(1, "cube_mesh.xml");
  //IGraphics* graphics = (IGraphics*) ServiceLocator::getComponent(GRAPHICS_COMPONENT);
  //graphics->loadMesh(*mesh);

  return S_OK;
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  if (entity) {
    MessageHandler::forwardMessage(Message(BEGIN_FRAME_MESSAGE, &entity->getPositon(), entity->getMessageHandler(BEGIN_FRAME_MESSAGE)));
    DrawInfo drawData;
    drawData.meshId = meshId;
    drawData.transform = *(Transform*) box->getDataComponent(TRANSFORM_COMPONENT)->getData();
    MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, box->getMessageHandler(DRAW_MESSAGE)));
    MessageHandler::forwardMessage(Message(SWAP_BUFFER_MESSAGE, &entity->getPositon(), entity->getMessageHandler(SWAP_BUFFER_MESSAGE)));
  }
  //if (player) {
  //  player->draw();
  //}
}
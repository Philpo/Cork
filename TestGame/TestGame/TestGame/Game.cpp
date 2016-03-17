#include "Game.h"
#include "BinaryData.h"

Game::Game() : scheduler(nullptr), factory(nullptr) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (factory) {
    delete factory;
  }
}

HRESULT Game::initGame(HINSTANCE instance, int cmdShow) {
  HRESULT hr = Window::initWindow(instance, cmdShow);
  if (FAILED(hr)) {
    return hr;
  }

  scheduler = new Scheduler(60.0, L"Test Game");
  scheduler->setGameLoopFunction(std::bind(&Game::loopFunction, this, std::placeholders::_1));

  factory = new Factory();

  ServiceLocator::addMessageHandlerFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, factory, std::placeholders::_1));
  //ServiceLocator::addFactoryFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getBasicGraphicsComponent, factory));
  ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getDirectX11Graphics, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(MESH_COMPONENT, std::bind(&Factory::getMeshComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(LIGHT_COMPONENT, std::bind(&Factory::getLightComponent, factory, std::placeholders::_1));
  Mesh::addMeshFileLoader(".xml", loadXMLMesh);

  //cb = new DirectX11ConstantBuffer(416);
  //cb->addMatrix("world", &XMMatrixIdentity());
  //cb->addMatrix("view", &XMMatrixIdentity());
  //cb->addMatrix("projection", &XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.01f, 100.0f)));
  //cb->addLight("light1", &LightStruct());
  //cb->addMaterial("material", &Material());
  //cb->addFloat3("eyePosW", &XMFLOAT3(0.0f, 2.0f, -10.0f));
  //cb->addInt("enableTexturing", 1);
  //cb->addInt("enableSpecularMapping", 1);
  //cb->addInt("enableBumpMapping", 1);
  //cb->addInt("enableClipTestig", 1);
  //cb->addFloat("fogStart", 40.0f);
  //cb->addFloat("fogRange", 50.0f);
  //cb->addFloat2("padding", &XMFLOAT2(0.0f, 0.0f));
  //cb->addFloat4("fogColour", &XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

  //BinaryData bd(416);
  cb = new BinaryData(416);
  cb->addVariable("world", sizeof(XMMATRIX));
  cb->addVariable("view", sizeof(XMMATRIX));
  cb->addData("projection", XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.01f, 100.0f)));
  cb->addVariable("light1", sizeof(LightStruct));
  cb->addVariable ("material", sizeof(Material));
  cb->addVariable("eyePosW", sizeof(XMFLOAT3));
  int a = 1;
  cb->addData("enableTexturing", a);
  cb->addData("enableSpecularMapping", a);
  cb->addData("enableBumpMapping", a);
  cb->addData("enableClipTesting", a);
  float b = 40.0f;
  float c = 50.0f;
  cb->addData("fogStart", b);
  cb->addData("fogRange", c);
  cb->addVariable("padding", sizeof(XMFLOAT2));
  cb->addData("fogColour", XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

  //XMMATRIX temp = *bd.getVariable<XMMATRIX>("world");

  camera = EntityLoader::loadEntity("camera.xml");
  EntityLoader::loadEntities("lights.xml", lights);
  EntityLoader::loadEntities("game_objects.xml", boxes);

  scheduler->registerPollComponent(POLL_INPUT_MESSAGE, ServiceLocator::getMessageHandler(INPUT_COMPONENT, camera));

  for (auto light : lights) {
    Light& lightData = *(Light*) lights[0]->getDataComponent(LIGHT_COMPONENT)->getData();
    lightData.cbVariableName = "light1";
  }

  return S_OK;
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  MessageHandler::forwardMessage(Message(BEGIN_FRAME_MESSAGE, nullptr, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_CONSTANT_BUFFER, cb, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_CAMERA, camera->getDataComponent(CAMERA_COMPONENT)->getData(), ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  for (auto light : lights) {
    MessageHandler::forwardMessage(Message(SET_LIGHT, light->getDataComponent(LIGHT_COMPONENT)->getData(), ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  }

  DrawInfo drawData;
  Transform& transform = *(Transform*) boxes[0]->getDataComponent(TRANSFORM_COMPONENT)->getData();
  transform.localRotation.setY(transform.localRotation.getY() + 1);

  for (auto box : boxes) {
    drawData.meshId = *(int*) box->getDataComponent(MESH_COMPONENT)->getData();
    drawData.transform = *(Transform*) box->getDataComponent(TRANSFORM_COMPONENT)->getData();
    MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, box->getMessageHandler(DRAW_MESSAGE)));
  }

  MessageHandler::forwardMessage(Message(SWAP_BUFFER_MESSAGE, nullptr, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
}
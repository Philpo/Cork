#include "Game.h"
#include "BinaryData.h"

Game::Game() : scheduler(nullptr), factory(nullptr), inputLayout(nullptr) {}

Game::~Game() {
  if (scheduler) {
    delete scheduler;
  }
  if (factory) {
    delete factory;
  }
  if (inputLayout) {
    inputLayout->Release();
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
  ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, factory, std::placeholders::_1));
  Mesh::addMeshFileLoader(".xml", loadXMLMesh);

  cb = new BinaryData(416);
  cb->addVariable("world", sizeof(XMMATRIX));
  cb->addVariable("view", sizeof(XMMATRIX));
  cb->addData("projection", XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.01f, 100.0f)));
  cb->addVariable("light1", sizeof(LightStruct));
  cb->addVariable ("material", sizeof(Material));
  cb->addVariable("eyePosW", sizeof(XMFLOAT3));
  cb->addVariable("enableTexturing", sizeof(int));
  cb->addVariable("enableSpecularMapping", sizeof(int));
  cb->addVariable("enableBumpMapping", sizeof(int));
  cb->addVariable("enableClipTesting", sizeof(int));
  cb->addData("fogStart", fogStart);
  cb->addData("fogRange", fogRange);
  cb->addVariable("padding", sizeof(XMFLOAT2));
  cb->addData("fogColour", XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

  size_t cbSize = cb->getSizeInBytes();
  MessageHandler::forwardMessage(Message(CREATE_CONSTANT_BUFFER, &cbSize, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  camera = EntityLoader::loadEntity("camera.xml");
  EntityLoader::loadEntities("lights.xml", lights);
  EntityLoader::loadEntities("game_objects.xml", boxes);

  scheduler->registerPollComponent(POLL_INPUT_MESSAGE, ServiceLocator::getMessageHandler(INPUT_COMPONENT, camera));

  stringstream lightName;
  for (unsigned i = 0; i < lights.size(); i++) {
    lightName.clear();
    Light& lightData = *(Light*) lights[i]->getDataComponent(LIGHT_COMPONENT)->getData();
    lightName << "light" << (i + 1);
    lightData.cbVariableName = lightName.str();
  }

  ResourceManager::loadShader("test_shader.fx", "VS", "vs_4_0", vertexShader);
  ResourceManager::loadShader("test_shader.fx", "PS", "ps_4_0", pixelShader);

  map<string, int> textureRegisters;
  textureRegisters.insert(pair<string, int>("diffuse", 0));
  textureRegisters.insert(pair<string, int>("specular", 1));
  textureRegisters.insert(pair<string, int>("normal", 2));

  ShaderTexRegisterInfo registersInfo(pixelShader, textureRegisters);

  MessageHandler::forwardMessage(Message(REGISTER_TEXTURE_REGISTERS, &registersInfo, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  D3D11_INPUT_ELEMENT_DESC layout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
  };
  InputLayoutInfo info(vertexShader, layout, ARRAYSIZE(layout), inputLayout);

  MessageHandler::forwardMessage(Message(LOAD_INPUT_LAYOUT, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  inputLayout = (ID3D11InputLayout*) info.inputLayout;

  MessageHandler::forwardMessage(Message(SET_SHADER, &vertexShader, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_SHADER, &pixelShader, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_INPUT_LAYOUT, inputLayout, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  return S_OK;
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  for (auto box : boxes) {
    if (CollisionDetector::collisionDetection(*camera->getDataComponent(BOUNDING_BOX_COMPONENT), *box->getDataComponent(BOUNDING_BOX_COMPONENT))) {
      CollisionResolver::resolveCollision(*camera, *box);
      Transform& transform = *(Transform*) camera->getDataComponent(TRANSFORM_COMPONENT)->getData();
      BoundingBox box = *(BoundingBox*) camera->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
      //transform.previousPosition = transform.position;
      transform.position = box.centre;
      camera->getDataComponent(TRANSFORM_COMPONENT)->setData(&transform);
    }
  }

  MessageHandler::forwardMessage(Message(BEGIN_FRAME_MESSAGE, nullptr, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_CONSTANT_BUFFER, cb, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_CAMERA, camera, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  for (auto light : lights) {
    MessageHandler::forwardMessage(Message(SET_LIGHT, light, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  }

  DrawInfo drawData;
  //Transform& transform = *(Transform*) boxes[0]->getDataComponent(TRANSFORM_COMPONENT)->getData();
  //transform.localRotation.setY(transform.localRotation.getY() + 1);
  drawData.shaderId = pixelShader;

  for (auto box : boxes) {
    int enableDiffuse, enableSpecular, enableBump;
    enableDiffuse = enableSpecular = enableBump = 0;

    drawData.meshId = *(int*) box->getDataComponent(MESH_COMPONENT)->getData();
    Mesh* mesh = ResourceManager::getMesh(drawData.meshId);

    for (auto id : mesh->getTextures()) {
      ITexture* texture = ResourceManager::getTexture(id);

      if (texture->getType() == "diffuse") {
        enableDiffuse = 1;
      }
      else if (texture->getType() == "specular") {
        enableSpecular = 1;
      }
      else if (texture->getType() == "normal") {
        enableBump = 1;
      }
    }

    cb->updateData("enableTexturing", enableDiffuse);
    cb->updateData("enableSpecularMapping", enableSpecular);
    cb->updateData("enableBumpMapping", enableBump);
    cb->updateData("enableClipTesting", enableDiffuse);

    drawData.transform = *(Transform*) box->getDataComponent(TRANSFORM_COMPONENT)->getData();
    MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, box->getMessageHandler(DRAW_MESSAGE)));
  }

  MessageHandler::forwardMessage(Message(SWAP_BUFFER_MESSAGE, nullptr, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
}
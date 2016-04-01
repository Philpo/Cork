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
  ServiceLocator::addMessageHandlerFunction(UPDATE_POSITION_COMPONENT, std::bind(&Factory::getUpdatePositionComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(APPLY_FORCE_COMPONENT, std::bind(&Factory::getApplyForceComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(MESH_COMPONENT, std::bind(&Factory::getMeshComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(LIGHT_COMPONENT, std::bind(&Factory::getLightComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(PARTICLE_COMPONENT, std::bind(&Factory::getParticleComponent, factory, std::placeholders::_1));
  Mesh::addMeshFileLoader(".xml", loadXMLMesh);

  CollisionDetector::setDetectionFunction(std::bind(&Game::axisAlignedBoundingBoxCollisionDetection, this, std::placeholders::_1, std::placeholders::_2));
  CollisionResolver::setResolvingFunction(std::bind(&Game::basicCollisionResolution, this, std::placeholders::_1, std::placeholders::_2));

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
    }
  }

  ApplyForceComponentData fcd;
  fcd.particle = (Particle*) boxes[1]->getDataComponent(PARTICLE_COMPONENT)->getData();
  fcd.timeInMilliseconds = timeSinceLastFrame;
  MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &fcd, boxes[1]->getMessageHandler(APPLY_FORCE_MESSAGE)));

  Transform& t = *(Transform*) boxes[1]->getDataComponent(TRANSFORM_COMPONENT)->getData();
  BoundingBox& b = *(BoundingBox*) boxes[1]->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();

  t.position += fcd.particle->displacement;
  b.centre += fcd.particle->displacement;

  for (auto box1 : boxes) {
    for (auto box2 : boxes) {
      if (box1 != box2 && CollisionDetector::collisionDetection(*box1->getDataComponent(BOUNDING_BOX_COMPONENT), *box2->getDataComponent(BOUNDING_BOX_COMPONENT))) {
        CollisionResolver::resolveCollision(*box1, *box2);
      }
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

bool Game::axisAlignedBoundingBoxCollisionDetection(IDataComponent& lhs, IDataComponent& rhs) {
  const BoundingBox lhsBox = *(BoundingBox*) lhs.getData();
  const BoundingBox rhsBox = *(BoundingBox*) rhs.getData();

  float lhsBottomFace = lhsBox.centre.getY() - (lhsBox.height / 2.0f);
  float lhsTopFace = lhsBox.centre.getY() + (lhsBox.height / 2.0f);
  float lhsLeftFace = lhsBox.centre.getX() - (lhsBox.width / 2.0f);
  float lhsRightFace = lhsBox.centre.getX() + (lhsBox.width / 2.0f);
  float lhsNearFace = lhsBox.centre.getZ() - (lhsBox.depth / 2.0f);
  float lhsFarFace = lhsBox.centre.getZ() + (lhsBox.depth / 2.0f);

  float rhsBottomFace = rhsBox.centre.getY() - (rhsBox.height / 2.0f);
  float rhsTopFace = rhsBox.centre.getY() + (rhsBox.height / 2.0f);
  float rhsLeftFace = rhsBox.centre.getX() - (rhsBox.width / 2.0f);
  float rhsRightFace = rhsBox.centre.getX() + (rhsBox.width / 2.0f);
  float rhsNearFace = rhsBox.centre.getZ() - (rhsBox.depth / 2.0f);
  float rhsFarFace = rhsBox.centre.getZ() + (rhsBox.depth / 2.0f);

  // bottom edge of the first is above the top edge of the second, therefore no collision
  if (lhsBottomFace > rhsTopFace) {
    return false;
  }
  // top edge of the first is below the bottom edge of the second, therefore no collision
  if (lhsTopFace < rhsBottomFace) {
    return false;
  }
  // right edge of the first is to the left of the second's left edge, therefore no collision
  if (lhsRightFace < rhsLeftFace) {
    return false;
  }
  // left edge of the first is to the right of the second's right edge, therefore no collision
  if (lhsLeftFace > rhsRightFace) {
    return false;
  }
  // near edge of the first is behind the far edge of the second, therefore no collision
  if (lhsNearFace > rhsFarFace) {
    return false;
  }
  // far edge of the first is in front of the near edge of the second, therefore no collision
  if (lhsFarFace < rhsNearFace) {
    return false;
  }

  return true;
}

void Game::basicCollisionResolution(const GameObject& lhs, const GameObject& rhs) {
  // find where we've collided
  // then update our position so we tesselate with the object's bounding box

  float xCorrection = 0.0f;
  float yCorrection = 0.0f;
  float zCorrection = 0.0f;

  BoundingBox& lhsBox = *(BoundingBox*) lhs.getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
  BoundingBox rhsBox = *(BoundingBox*) rhs.getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
  Transform lhsTransform = *(Transform*) lhs.getDataComponent(TRANSFORM_COMPONENT)->getData();

  float top = lhsBox.centre.getY() + (lhsBox.height / 2.0f);
  float bottom = lhsBox.centre.getY() - (lhsBox.height / 2.0f);
  float left = lhsBox.centre.getX() - (lhsBox.width / 2.0f);
  float right = lhsBox.centre.getX() + (lhsBox.width / 2.0f);
  float front = lhsBox.centre.getZ() - (lhsBox.depth / 2.0f);
  float back = lhsBox.centre.getZ() + (lhsBox.depth / 2.0f);

  float previousTop = lhsTransform.previousPosition.getY() + (lhsBox.height / 2.0f);
  float previousBottom = lhsTransform.previousPosition.getY() - (lhsBox.height / 2.0f);
  float previousLeft = lhsTransform.previousPosition.getX() - (lhsBox.width / 2.0f);
  float previousRight = lhsTransform.previousPosition.getX() + (lhsBox.width / 2.0f);
  float previousNear = lhsTransform.previousPosition.getZ() - (lhsBox.depth / 2.0f);
  float previousFar = lhsTransform.previousPosition.getZ() + (lhsBox.depth / 2.0f);

  float collidedTop = rhsBox.centre.getY() + (rhsBox.height / 2.0f);
  float collidedBottom = rhsBox.centre.getY() - (rhsBox.height / 2.0f);
  float collidedLeft = rhsBox.centre.getX() - (rhsBox.width / 2.0f);
  float collidedRight = rhsBox.centre.getX() + (rhsBox.width / 2.0f);
  float collidedNear = rhsBox.centre.getZ() - (rhsBox.depth / 2.0f);
  float collidedFar = rhsBox.centre.getZ() + (rhsBox.depth / 2.0f);

  if (previousBottom >= collidedTop && (bottom <= collidedTop && bottom >= collidedBottom)) {
    yCorrection = collidedTop - bottom;
    Particle* particle = (Particle*) lhs.getDataComponent(PARTICLE_COMPONENT)->getData();
    particle->gravityEnabled = false;
    particle->displacement.setY(0.0f);
    particle->velocity.setY(0.0f);
    particle->acceleration.setY(0.0f);
  }
  else if (previousTop <= collidedBottom && (top >= collidedBottom && top <= collidedTop)) {
    yCorrection = collidedBottom - top;
  }
  else if (previousRight <= collidedLeft && (right >= collidedLeft && right <= collidedRight)) {
    xCorrection = collidedLeft - right;
  }
  else if (previousLeft >= collidedRight && (left <= collidedRight && left >= collidedLeft)) {
    xCorrection = collidedRight - left;
  }
  else if (previousFar <= collidedNear && (back >= collidedNear && back <= collidedFar)) {
    zCorrection = collidedNear - back;
  }
  else if (previousNear >= collidedFar && (front <= collidedFar && front >= collidedNear)) {
    zCorrection = collidedFar - front;
  }

  lhsBox.centre += Vector3(xCorrection, yCorrection, zCorrection);
  MessageHandler::forwardMessage(Message(UPDATE_AFTER_COLLISION_MESSAGE, &lhsBox.centre, lhs.getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)));
}
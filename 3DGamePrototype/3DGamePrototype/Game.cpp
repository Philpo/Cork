#include "Game.h"
#include "BinaryData.h"

const bool UNIT_TESTS = false;

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
  HRESULT hr = Window::initWindow(instance, cmdShow, 480, 640);
  if (FAILED(hr)) {
    return hr;
  }

  scheduler = new Scheduler(60.0, L"Test Game");
  scheduler->setGameLoopFunction(std::bind(&Game::loopFunction, this, std::placeholders::_1));

  factory = new GameFactory();

  ServiceLocator::addMessageHandlerFunction(BASIC_MOVE_COMPONENT, std::bind(&GameFactory::getBasicMovementComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(CAMERA_MOVE_COMPONENT, std::bind(&GameFactory::getCameraMoveComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(GRAPHICS_COMPONENT, std::bind(&GameFactory::getDirectX11Graphics, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
  //ServiceLocator::addMessageHandlerFunction(INPUT_COMPONENT, std::bind(&Factory::getInputMessenger, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(UPDATE_POSITION_COMPONENT, std::bind(&GameFactory::getUpdatePositionComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(APPLY_FORCE_COMPONENT, std::bind(&Factory::getApplyForceComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(JUMP_COMPONENT, std::bind(&GameFactory::getJumpComponent, factory, std::placeholders::_1));
  ServiceLocator::addMessageHandlerFunction(BULLET_COMPONENT, std::bind(&GameFactory::getBulletComponent, factory, std::placeholders::_1));

  ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(MESH_COMPONENT, std::bind(&Factory::getMeshComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(LIGHT_COMPONENT, std::bind(&GameFactory::getLightComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(PARTICLE_COMPONENT, std::bind(&Factory::getParticleComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(JUMP_DATA_COMPONENT, std::bind(&GameFactory::getJumpDataComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(BULLET_DATA_COMPONENT, std::bind(&GameFactory::getBulletDataComponent, factory, std::placeholders::_1));
  ServiceLocator::addDataComponentFunction(OBJECT_POOL_DATA_COMPONENT, std::bind(&GameFactory::getObjectPoolDataComponent, factory, std::placeholders::_1));

  Mesh::addMeshFileLoader(".xml", loadXMLMesh);

  CollisionDetector::setDetectionFunction(std::bind(&Game::axisAlignedBoundingBoxCollisionDetection, this, std::placeholders::_1, std::placeholders::_2));
  CollisionResolver::setResolvingFunction(std::bind(&Game::basicCollisionResolution, this, std::placeholders::_1, std::placeholders::_2));

  cb = new BinaryData(416);
  cb->addVariable("world", sizeof(XMMATRIX));
  cb->addVariable("view", sizeof(XMMATRIX));
  cb->addData("projection", XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.01f, 100.0f)));
  cb->addVariable("light1", sizeof(LightStruct));
  cb->addVariable("material", sizeof(Material));
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
  MessageHandler::forwardMessage(Message(CREATE_CONSTANT_BUFFER_MESSAGE, &cbSize, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  camera = EntityLoader::loadEntity("camera.xml");
  floorPlane = EntityLoader::loadEntity("floor.xml");
  EntityLoader::loadEntities("lights.xml", lights);
  EntityLoader::loadEntities("game_objects.xml", boxes);
  EntityLoader::loadEntity("bullet.xml");

  boxPool = ((PoolData*) camera->getDataComponent(OBJECT_POOL_DATA_COMPONENT)->getData())->pool;

  scheduler->scheduleComponent(POLL_INPUT_MESSAGE, ServiceLocator::getMessageHandler(INPUT_COMPONENT, camera));

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

  MessageHandler::forwardMessage(Message(REGISTER_TEXTURE_REGISTERS_MESSAGE, &registersInfo, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  D3D11_INPUT_ELEMENT_DESC layout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
  };
  InputLayoutInfo info(vertexShader, layout, ARRAYSIZE(layout), inputLayout);

  MessageHandler::forwardMessage(Message(LOAD_INPUT_LAYOUT_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  MessageHandler::forwardMessage(Message(SET_SHADER_MESSAGE, &vertexShader, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_SHADER_MESSAGE, &pixelShader, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  MessageHandler::forwardMessage(Message(SET_INPUT_LAYOUT_MESSAGE, inputLayout, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

  ResourceManager::loadPasses("passes.xml", passes);

  return S_OK;
}

WPARAM Game::startGame() {
  return scheduler->gameLoop();
}

void Game::loopFunction(double timeSinceLastFrame) {
  update(timeSinceLastFrame);
  draw();
}

void Game::update(double timeSinceLastFrame) {
  CollisionResolver::setResolvingFunction(std::bind(&Game::basicCollisionResolution, this, std::placeholders::_1, std::placeholders::_2));

  Transform& t = *(Transform*) camera->getDataComponent(TRANSFORM_COMPONENT)->getData();
  BoundingBox& b = *(BoundingBox*) camera->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
  Particle& p = *(Particle*) camera->getDataComponent(PARTICLE_COMPONENT)->getData();
  JumpData& jd = *(JumpData*) camera->getDataComponent(JUMP_DATA_COMPONENT)->getData();

  b.centre = t.position;

  if (jd.jumping) {
    scheduler->scheduleComponent(JUMP_MESSAGE, camera->getMessageHandler(JUMP_MESSAGE));
  }

  MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &timeSinceLastFrame, camera->getMessageHandler(APPLY_FORCE_MESSAGE)));

  t.position += p.displacement;
  b.centre += p.displacement;

  for (auto box : boxes) {
    MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &timeSinceLastFrame, box->getMessageHandler(APPLY_FORCE_MESSAGE)));

    Transform& t = *(Transform*) box->getDataComponent(TRANSFORM_COMPONENT)->getData();
    BoundingBox& b = *(BoundingBox*) box->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
    Particle p = *(Particle*) box->getDataComponent(PARTICLE_COMPONENT)->getData();

    t.position += p.displacement;
    b.centre += p.displacement;
  }

  for (auto bullet : boxPool->getObjects()) {
    BulletData bd = *(BulletData*) bullet->getDataComponent(BULLET_DATA_COMPONENT)->getData();
    Transform& t = *(Transform*) bullet->getDataComponent(TRANSFORM_COMPONENT)->getData();
    BoundingBox& b = *(BoundingBox*) bullet->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
    Particle p = *(Particle*) bullet->getDataComponent(PARTICLE_COMPONENT)->getData();
    Vector3 moveAmount = bd.direction * bd.speed;

    t.position += moveAmount;
    b.centre += moveAmount;

    MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &timeSinceLastFrame, bullet->getMessageHandler(APPLY_FORCE_MESSAGE)));

    t.position += p.displacement;
    b.centre += p.displacement;
  }

  for (auto box1 : boxes) {
    bool noCollision = true;

    if (CollisionDetector::collisionDetection(*camera->getDataComponent(BOUNDING_BOX_COMPONENT), *box1->getDataComponent(BOUNDING_BOX_COMPONENT))) {
      CollisionResolver::resolveCollision(*camera, *box1);
      noCollision = false;
    }
    if (CollisionDetector::collisionDetection(*box1->getDataComponent(BOUNDING_BOX_COMPONENT), *floorPlane->getDataComponent(BOUNDING_BOX_COMPONENT))) {
      CollisionResolver::resolveCollision(*box1, *floorPlane);
      noCollision = false;
    }

    for (auto box2 : boxes) {
      if (box1 != box2 && CollisionDetector::collisionDetection(*box1->getDataComponent(BOUNDING_BOX_COMPONENT), *box2->getDataComponent(BOUNDING_BOX_COMPONENT))) {
        CollisionResolver::resolveCollision(*box1, *box2);
        noCollision = false;
      }
    }

    if (noCollision) {
      Particle& p = *(Particle*) box1->getDataComponent(PARTICLE_COMPONENT)->getData();
      p.gravityEnabled = true;
    }
  }

  if (CollisionDetector::collisionDetection(*camera->getDataComponent(BOUNDING_BOX_COMPONENT), *floorPlane->getDataComponent(BOUNDING_BOX_COMPONENT))) {
    CollisionResolver::resolveCollision(*camera, *floorPlane);
  }

  CollisionResolver::setResolvingFunction(std::bind(&Game::bulletCollisionResolution, this, std::placeholders::_1, std::placeholders::_2));
  vector<GameObject*> bulletsToRemove, boxesToRemove;
  for (auto bullet : boxPool->getObjects()) {
    if (CollisionDetector::collisionDetection(*bullet->getDataComponent(BOUNDING_BOX_COMPONENT), *floorPlane->getDataComponent(BOUNDING_BOX_COMPONENT))) {
      bulletsToRemove.push_back(bullet);
      continue;
    }

    for (auto box : boxes) {
      if (CollisionDetector::collisionDetection(*bullet->getDataComponent(BOUNDING_BOX_COMPONENT), *box->getDataComponent(BOUNDING_BOX_COMPONENT))) {
        bulletsToRemove.push_back(bullet);
        boxesToRemove.push_back(box);
        continue;
      }
    }
  }
  for (auto bullet : bulletsToRemove) {
    remove<GameObject*>(boxPool->getObjects(), bullet);
  }
  for (auto box : boxesToRemove) {
    remove<GameObject* const>(boxes, box);
  }
}

void Game::draw() {
  for (auto pass : passes) {
    MessageHandler::forwardMessage(Message(BEGIN_PASS_MESSAGE, pass, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    MessageHandler::forwardMessage(Message(SET_CONSTANT_BUFFER_MESSAGE, cb, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    resolveViewMatrix(camera);

    for (auto light : lights) {
      setLight(light);
    }

    DrawInfo drawData;
    drawData.shaderId = pixelShader;

    int enableDiffuse, enableSpecular, enableBump;
    enableDiffuse = enableSpecular = enableBump = 0;
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

      resolveSceneGraph(box);
      setMaterial(box);

      MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, box->getMessageHandler(DRAW_MESSAGE)));
    }

    for (auto bullet : boxPool->getObjects()) {
      enableDiffuse = enableSpecular = enableBump = 1;

      drawData.meshId = *(int*) bullet->getDataComponent(MESH_COMPONENT)->getData();

      cb->updateData("enableTexturing", enableDiffuse);
      cb->updateData("enableSpecularMapping", enableSpecular);
      cb->updateData("enableBumpMapping", enableBump);
      cb->updateData("enableClipTesting", enableDiffuse);

      resolveSceneGraph(bullet);
      MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, bullet->getMessageHandler(DRAW_MESSAGE)));
    }

    drawData.meshId = *(int*) floorPlane->getDataComponent(MESH_COMPONENT)->getData();
    enableDiffuse = enableSpecular = enableBump = 0;
    cb->updateData("enableTexturing", enableDiffuse);
    cb->updateData("enableSpecularMapping", enableSpecular);
    cb->updateData("enableBumpMapping", enableBump);
    cb->updateData("enableClipTesting", enableDiffuse);
    resolveSceneGraph(floorPlane);
    setMaterial(floorPlane);
    MessageHandler::forwardMessage(Message(DRAW_MESSAGE, &drawData, floorPlane->getMessageHandler(DRAW_MESSAGE)));
  }

  MessageHandler::forwardMessage(Message(SWAP_BUFFER_MESSAGE, nullptr, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
}

void Game::resolveSceneGraph(GameObject* const entity) {
  Transform transform = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();

  XMMATRIX world = XMMatrixIdentity();
  XMMATRIX translation = XMMatrixTranslation(transform.position.getX(), transform.position.getY(), transform.position.getZ());
  XMMATRIX scale = XMMatrixScaling(transform.scale.getX(), transform.scale.getY(), transform.scale.getZ());
  XMMATRIX xRotation = XMMatrixRotationX(XMConvertToRadians(transform.localRotation.getX()));
  XMMATRIX yRotation = XMMatrixRotationY(XMConvertToRadians(transform.localRotation.getY()));
  XMMATRIX zRotation = XMMatrixRotationZ(XMConvertToRadians(transform.localRotation.getZ()));
  XMMATRIX worldXRotation = XMMatrixRotationX(XMConvertToRadians(transform.worldRotation.getX()));
  XMMATRIX worldYRotation = XMMatrixRotationY(XMConvertToRadians(transform.worldRotation.getY()));
  XMMATRIX worldZRotation = XMMatrixRotationZ(XMConvertToRadians(transform.worldRotation.getZ()));
  world = world * scale * xRotation * yRotation * zRotation * translation * worldXRotation * worldYRotation * worldZRotation;

  Transform* parent = transform.parent;
  while (parent) {
    XMMATRIX parentTranslation = XMMatrixTranslation(parent->position.getX(), parent->position.getY(), parent->position.getZ());
    XMMATRIX parentXRotation = XMMatrixRotationX(XMConvertToRadians(parent->worldRotation.getX()));
    XMMATRIX parentYRotation = XMMatrixRotationY(XMConvertToRadians(parent->worldRotation.getY()));
    XMMATRIX parentZRotation = XMMatrixRotationZ(XMConvertToRadians(parent->worldRotation.getZ()));
    world *= parentTranslation * parentXRotation * parentYRotation * parentZRotation;
    parent = parent->parent;
  }

  cb->updateData("world", XMMatrixTranspose(world));
}

void Game::resolveViewMatrix(GameObject* const camera) {
  Camera cameraData = *(Camera*) camera->getDataComponent(CAMERA_COMPONENT)->getData();
  Transform transformData = *(Transform*) camera->getDataComponent(TRANSFORM_COMPONENT)->getData();

  XMMATRIX temp = XMMatrixIdentity();

  Transform* parent = transformData.parent;
  while (parent) {
    XMMATRIX parentTranslation = XMMatrixTranslation(parent->position.getX(), parent->position.getY(), parent->position.getZ());
    temp *= parentTranslation;
    parent = parent->parent;
  }

  XMVECTOR eye = XMVectorSet(transformData.position.getX(), transformData.position.getY(), transformData.position.getZ(), 0.0f);
  eye = XMVector4Transform(eye, temp);
  XMFLOAT3 eyePosW;
  XMStoreFloat3(&eyePosW, eye);

  XMVECTOR right = XMVectorSet(cameraData.right.getX(), cameraData.right.getY(), cameraData.right.getZ(), 0.0f);
  XMVECTOR up = XMVectorSet(cameraData.up.getX(), cameraData.up.getY(), cameraData.up.getZ(), 0.0f);
  XMVECTOR at = XMVectorSet(cameraData.look.getX(), cameraData.look.getY(), cameraData.look.getZ(), 0.0f);
  XMVECTOR worldUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

  XMMATRIX yRotation = XMMatrixRotationY(XMConvertToRadians(transformData.localRotation.getY()));

  // first do yaw rotation
  at = XMVector4Normalize(XMVector4Transform(at, yRotation));
  //up = XMVector4Normalize(XMVector4Transform(up, yRotation));
  //right = XMVector4Normalize(XMVector4Transform(right, yRotation));
  right = XMVector4Normalize(XMVector3Cross(worldUp, at));


  XMMATRIX xRotation = XMMatrixRotationAxis(right, XMConvertToRadians(transformData.localRotation.getX()));
  // then do pitch rotation
  at = XMVector4Normalize(XMVector4Transform(at, xRotation));

  cb->updateData("view", XMMatrixTranspose(XMMatrixLookToLH(eye, at, worldUp)));
  cb->updateData("eyePosW", eyePosW);
}

void Game::setMaterial(GameObject* const entity) {
  Mesh* mesh = ResourceManager::getMesh(*(int*) entity->getDataComponent(MESH_COMPONENT)->getData());
  MeshMaterial meshMaterial = mesh->getMaterial();

  Material material;
  material.ambient = XMFLOAT4(meshMaterial.ambient.getX(), meshMaterial.ambient.getY(), meshMaterial.ambient.getZ(), meshMaterial.alpha);
  material.diffuse = XMFLOAT4(meshMaterial.diffuse.getX(), meshMaterial.diffuse.getY(), meshMaterial.diffuse.getZ(), meshMaterial.alpha);
  material.specular = XMFLOAT4(meshMaterial.specular.getX(), meshMaterial.specular.getY(), meshMaterial.specular.getZ(), meshMaterial.alpha);
  material.specularPower = meshMaterial.specularPower;

  cb->updateData("material", material);
}

void Game::setLight(GameObject* const light) {
  LightStruct toSet;

  Light lightData = *(Light*) light->getDataComponent(LIGHT_COMPONENT)->getData();
  Transform transformData = *(Transform*) light->getDataComponent(TRANSFORM_COMPONENT)->getData();

  XMMATRIX temp = XMMatrixIdentity();
  XMMATRIX rotationTemp = XMMatrixIdentity();

  Transform* parent = transformData.parent;
  while (parent) {
    XMMATRIX parentTranslation = XMMatrixTranslation(parent->position.getX(), parent->position.getY(), parent->position.getZ());
    XMMATRIX parentXRotation = XMMatrixRotationX(XMConvertToRadians(parent->worldRotation.getX()));
    XMMATRIX parentYRotation = XMMatrixRotationY(XMConvertToRadians(parent->worldRotation.getY()));
    XMMATRIX parentZRotation = XMMatrixRotationZ(XMConvertToRadians(parent->worldRotation.getZ()));
    temp *= parentTranslation;
    rotationTemp *= parentXRotation * parentYRotation * parentZRotation;
    parent = parent->parent;
  }

  XMVECTOR position = XMVectorSet(transformData.position.getX(), transformData.position.getY(), transformData.position.getZ(), 1.0f);
  position = XMVector3Transform(position, temp);
  XMStoreFloat3(&toSet.position, position);

  if (lightData.type == DIRECTIONAL_LIGHT) {
    toSet.direction = XMFLOAT3(lightData.direction.getX(), lightData.direction.getY(), lightData.direction.getZ());
  }
  else {
    XMVECTOR direction = XMVectorSet(lightData.direction.getX(), lightData.direction.getY(), lightData.direction.getZ(), 0.0f);
    direction = XMVector3Transform(direction, rotationTemp);
    XMStoreFloat3(&toSet.direction, direction);
  }

  toSet.ambient = XMFLOAT4(lightData.ambient.getX(), lightData.ambient.getY(), lightData.ambient.getZ(), 1.0f);
  toSet.diffuse = XMFLOAT4(lightData.diffuse.getX(), lightData.diffuse.getY(), lightData.diffuse.getZ(), 1.0f);
  toSet.specular = XMFLOAT4(lightData.specular.getX(), lightData.specular.getY(), lightData.specular.getZ(), 1.0f);
  toSet.range = lightData.range;
  toSet.exponent = lightData.exponent;
  toSet.attenuation = XMFLOAT3(lightData.attenuation.getX(), lightData.attenuation.getY(), lightData.attenuation.getZ());
  toSet.enabled = lightData.enabled;
  toSet.type = lightData.type;

  cb->updateData(lightData.cbVariableName, toSet);
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

    if (lhs.getDataComponent(JUMP_DATA_COMPONENT)) {
      JumpData* jump = (JumpData*) lhs.getDataComponent(JUMP_DATA_COMPONENT)->getData();
      jump->falling = false;
      scheduler->unscheduleComponent(JUMP_MESSAGE);
    }
  }
  else if (previousTop <= collidedBottom && (top >= collidedBottom && top <= collidedTop)) {
    yCorrection = collidedBottom - top;

    if (lhs.getDataComponent(JUMP_DATA_COMPONENT)) {
      JumpData* jump = (JumpData*) lhs.getDataComponent(JUMP_DATA_COMPONENT)->getData();
      jump->jumping = false;
      jump->jumpTime = jump->maxJumpTime;
    }
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

void Game::bulletCollisionResolution(const GameObject& lhs, const GameObject& rhs) {
  MessageHandler::forwardMessage(Message(REMOVE_BULLET_MESSAGE, (void*) &lhs, camera->getMessageHandler(REMOVE_BULLET_MESSAGE)));
}
#include "BulletComponent.h"

const vector<string> BulletComponent::SUPPORTED_MESSAGES = { ADD_BULLET_MESSAGE, REMOVE_BULLET_MESSAGE };

void BulletComponent::receiveMessage(IMessage& message) {
  Transform t = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
  Camera c = *(Camera*) entity->getDataComponent(CAMERA_COMPONENT)->getData();
  PoolData pd = *(PoolData*) entity->getDataComponent(OBJECT_POOL_DATA_COMPONENT)->getData();

  if (message.getType() == ADD_BULLET_MESSAGE) {
    GameObject* bullet = pd.pool->createObject(pd.masterUUId);
    BulletData& bd = *(BulletData*) bullet->getDataComponent(BULLET_DATA_COMPONENT)->getData();
    Transform& bt = *(Transform*) bullet->getDataComponent(TRANSFORM_COMPONENT)->getData();
    BoundingBox& bb = *(BoundingBox*) bullet->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
    bt.position = t.position;
    bb.centre = t.position;
    Vector3 rotatedLook = c.look.rotateY(-t.localRotation.getY());
    rotatedLook = rotatedLook.rotateX(-t.localRotation.getX());
    bd.direction = rotatedLook;
    bt.localRotation = t.localRotation;
  }
  else if (message.getType() == REMOVE_BULLET_MESSAGE) {
    pd.pool->removeObject((GameObject*) message.getData());
  }
}
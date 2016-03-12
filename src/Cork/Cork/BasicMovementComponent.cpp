#include "BasicMovementComponent.h"

void BasicMovementComponent::receiveMessage(IMessage& message) {
  if (message.getType() == INPUT_RECEIVED_MESSAGE && target) {
    string* event = (string*) message.getData(); 
    Vector3 newPosition;
    IDataComponent* component = nullptr;

    if (target->getDataComponent(TRANSFORM_COMPONENT)) {
      component = target->getDataComponent(TRANSFORM_COMPONENT);
      newPosition = ((Transform*) component->getData())->position;
    }
    else if (target->getDataComponent(CAMERA_COMPONENT)) {
      component = target->getDataComponent(CAMERA_COMPONENT);
      newPosition = ((Camera*) component->getData())->position;
    }

    if (event) {
      if (*event == MOVE_UP) {
        newPosition.setZ(newPosition.getZ() + 1.0f);
      }
      else if (*event == MOVE_DOWN) {
        newPosition.setZ(newPosition.getZ() - 1.0f);
      }
      else if (*event == MOVE_LEFT) {
        newPosition.setX(newPosition.getX() - 1.0f);
      }
      else if (*event == MOVE_RIGHT) {
        newPosition.setX(newPosition.getX() + 1.0f);
      }
    }

    if (target->getDataComponent(TRANSFORM_COMPONENT)) {
      Transform* t = (Transform*) component->getData();
      t->position = newPosition;
      component->setData(t);
    }
    else if (target->getDataComponent(CAMERA_COMPONENT)) {
      Camera* t = (Camera*) component->getData();
      t->position = newPosition;
      component->setData(t);
    }
  }
}
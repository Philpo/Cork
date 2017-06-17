#include "BasicMovementComponent.h"

const vector<size_t> BasicMovementComponent::SUPPORTED_MESSAGES = { INPUT_RECEIVED_MESSAGE };

void BasicMovementComponent::receiveMessage(IMessage& message) {
  if (target) {
    size_t* event = (size_t*) message.getData(); 
    Vector3 newPosition, newRotation;
    IDataComponent* component = nullptr;

    component = target->getDataComponent(TRANSFORM_COMPONENT);
    newPosition = ((Transform*) component->getData())->position;
    newRotation = ((Transform*) component->getData())->localRotation;

    if (event) {
      if (*event == MOVE_LEFT) {
        newPosition.setX(newPosition.getX() - 0.1f);
      }
      else if (*event == MOVE_RIGHT) {
        newPosition.setX(newPosition.getX() + 0.1f);
      }
    }

    Transform* t = (Transform*) component->getData();
    t->previousPosition = t->position;
    t->position = newPosition;
    t->localRotation = newRotation;
    component->setData(t);
  }
}
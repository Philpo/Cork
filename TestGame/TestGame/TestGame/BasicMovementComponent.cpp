#include "BasicMovementComponent.h"

const vector<string> BasicMovementComponent::SUPPORTED_MESSAGES = { INPUT_RECEIVED_MESSAGE };

void BasicMovementComponent::receiveMessage(IMessage& message) {
  if (target) {
    string* event = (string*) message.getData(); 
    Vector3 newPosition, newRotation;
    IDataComponent* component = nullptr;

    component = target->getDataComponent(TRANSFORM_COMPONENT);
    newPosition = ((Transform*) component->getData())->position;
    newRotation = ((Transform*) component->getData())->localRotation;

    if (event) {
      if (*event == MOVE_FORWARD) {
        newPosition.setZ(newPosition.getZ() + 1.0f);
      }
      else if (*event == MOVE_BACK) {
        newPosition.setZ(newPosition.getZ() - 1.0f);
      }
      else if (*event == MOVE_LEFT) {
        newPosition.setX(newPosition.getX() - 1.0f);
      }
      else if (*event == MOVE_RIGHT) {
        newPosition.setX(newPosition.getX() + 1.0f);
      }
      else if (*event == ROTATE_PITCH_UP) {
        newRotation.setX(newRotation.getX() - 1.0f);
      }
      else if (*event == ROTATE_PITCH_DOWN) {
        newRotation.setX(newRotation.getX() + 1.0f);
      }
      else if (*event == ROTATE_YAW_ANTICLOCKWISE) {
        newRotation.setY(newRotation.getY() - 1.0f);
      }
      else if (*event == ROTATE_YAW_CLOCKWISE) {
        newRotation.setY(newRotation.getY() + 1.0f);
      }
    }

    Transform* t = (Transform*) component->getData();
    t->previousPosition = t->position;
    t->position = newPosition;
    t->localRotation = newRotation;
    component->setData(t);
  }
}
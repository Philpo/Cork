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
      if (*event == MOVE_LEFT) {
        newPosition.setX(newPosition.getX() - 0.1f);
      }
      else if (*event == MOVE_RIGHT) {
        newPosition.setX(newPosition.getX() + 0.1f);
      }
      else if (*event == JUMP) {
        double time = 0.01;
        MessageHandler::forwardMessage(Message(JUMP_MESSAGE, &time, target->getMessageHandler(JUMP_MESSAGE)));
      }
    }

    Transform* t = (Transform*) component->getData();
    t->previousPosition = t->position;
    t->position = newPosition;
    t->localRotation = newRotation;
    component->setData(t);
  }
}
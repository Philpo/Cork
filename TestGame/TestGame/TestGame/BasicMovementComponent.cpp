#include "BasicMovementComponent.h"

void BasicMovementComponent::receiveMessage(const IMessage& message) {
  if (message.getType() == INPUT_RECEIVED_MESSAGE) {
    InputEvent* event = (InputEvent*) message.getData(); 
    Vector3<float> newPosition = target.getPositon();

    if (event) {
      switch (*event) {
        case MOVE_UP:
          newPosition.setY(newPosition.getY() - 1.0f);
          break;
        case MOVE_DOWN:
          newPosition.setY(newPosition.getY() + 1.0f);
          break;
        case MOVE_LEFT:
          newPosition.setX(newPosition.getX() - 1.0f);
          break;
        case MOVE_RIGHT:
          newPosition.setX(newPosition.getX() + 1.0f);
          break;
        case NONE:
          break;
      }
    }
    target.setPosition(newPosition);
  }
}
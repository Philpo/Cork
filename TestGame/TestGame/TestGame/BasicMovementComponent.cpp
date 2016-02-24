#include "BasicMovementComponent.h"

void BasicMovementComponent::receiveMessage(IMessage& message) {
  if (message.getType() == INPUT_RECEIVED_MESSAGE) {
    string* event = (string*) message.getData(); 
    Vector3<float> newPosition = target.getPositon();

    if (event) {
      if (*event == MOVE_UP) {
        newPosition.setY(newPosition.getY() - 1.0f);
      }
      else if (*event == MOVE_DOWN) {
        newPosition.setY(newPosition.getY() + 1.0f);
      }
      else if (*event == MOVE_LEFT) {
        newPosition.setX(newPosition.getX() - 1.0f);
      }
      else if (*event == MOVE_RIGHT) {
        newPosition.setX(newPosition.getX() + 1.0f);
      }
    }
    target.setPosition(newPosition);
  }
}
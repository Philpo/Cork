#include "CameraMovementComponent.h"
#include "Message.h"

const vector<string> CameraMovementComponent::SUPPORTED_MESSAGES = { INPUT_RECEIVED_MESSAGE };

void CameraMovementComponent::receiveMessage(IMessage& message) {
  if (target) {
    string* event = (string*) message.getData();
    Vector3 newPosition, newRotation;
    IDataComponent* component = nullptr;
    Camera& camera = *(Camera*) target->getDataComponent(CAMERA_COMPONENT)->getData();

    component = target->getDataComponent(TRANSFORM_COMPONENT);
    newPosition = ((Transform*) component->getData())->position;
    newRotation = ((Transform*) component->getData())->localRotation;

    if (event) {
      if (*event == MOVE_FORWARD) {
        Vector3 rotatedLook = camera.look.rotateY(-newRotation.getY());
        Vector3 moveAmount = rotatedLook * 1.0f;
        newPosition += moveAmount;

        //newPosition.setZ(newPosition.getZ() + 1.0f);
      }
      else if (*event == MOVE_BACK) {
        Vector3 rotatedLook = camera.look.rotateY(-newRotation.getY());
        Vector3 moveAmount = rotatedLook * -1.0f;
        newPosition += moveAmount;

        //newPosition.setZ(newPosition.getZ() - 1.0f);
      }
      else if (*event == MOVE_LEFT) {
        Vector3 rotatedRight = camera.right.rotateY(-newRotation.getY());
        Vector3 moveAmount = rotatedRight * -1.0f;
        newPosition += moveAmount;

        //newPosition.setX(newPosition.getX() - 1.0f);
      }
      else if (*event == MOVE_RIGHT) {
        Vector3 rotatedRight = camera.right.rotateY(-newRotation.getY());
        Vector3 moveAmount = rotatedRight * 1.0f;
        newPosition += moveAmount;

        //newPosition.setX(newPosition.getX() + 1.0f);
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
      else if (*event == FIRE) {
        MessageHandler::forwardMessage(Message(ADD_BULLET_MESSAGE, nullptr, target->getMessageHandler(ADD_BULLET_MESSAGE)));
      }
    }

    Transform* t = (Transform*) component->getData();
    t->previousPosition = t->position;
    t->position = newPosition;
    t->localRotation = newRotation;
    component->setData(t);
  }
}
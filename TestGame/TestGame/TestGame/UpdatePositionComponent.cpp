#include "UpdatePositionComponent.h"

const vector<size_t> UpdatePositionComponent::SUPPORTED_MESSAGES = { UPDATE_AFTER_COLLISION_MESSAGE };

void UpdatePositionComponent::receiveMessage(IMessage& message) {
  if (target) {
    Transform& transform = *(Transform*) target->getDataComponent(TRANSFORM_COMPONENT)->getData();
    Vector3 newPosition = *(Vector3*) message.getData();
    transform.position = newPosition;
  }
}
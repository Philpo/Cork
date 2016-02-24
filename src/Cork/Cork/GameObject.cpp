#include "GameObject.h"

GameObject::GameObject(const Vector3<float> position) : position(position) {}

GameObject::~GameObject() {}

void GameObject::receiveMessage(IMessage& message) {
  if (components.find(message.getType()) != components.end()) {
    message.setTarget(components[message.getType()]);
    MessageHandler::forwardMessage(message);
  }
}
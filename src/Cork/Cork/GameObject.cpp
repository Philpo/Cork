#include "GameObject.h"

GameObject::~GameObject() {}

void GameObject::receiveMessage(IMessage& message) {
  if (components.find(message.getType()) != components.end()) {
    message.setTarget(components[message.getType()]);
    MessageHandler::forwardMessage(message);
  }
}
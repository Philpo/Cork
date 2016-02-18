#include "GameObject.h"

GameObject::GameObject(const Vector3<float> position) : position(position) {}

GameObject::~GameObject() {
  for (auto component : components) {
    delete component;
  }
  for (auto kvp : functionalComponents) {
    delete kvp.second;
  }
}

void GameObject::receiveMessage(IMessage& message) {
  if (functionalComponents.find(message.getType()) != functionalComponents.end()) {
    message.setTarget(functionalComponents[message.getType()]);
    MessageHandler::forwardMessage(message);
    //functionalComponents[message.getType()]->receiveMessage(message);
  }
}
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

void GameObject::receiveMessage(const IMessage& message) {
  if (functionalComponents.find(message.getType()) != functionalComponents.end()) {
    functionalComponents[message.getType()]->receiveMessage(message);
  }
}
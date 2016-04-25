#include "GameObject.h"

GameObject::~GameObject() {}

void GameObject::addComponent(const string& type, IComponent* const component) {
  components.insert(pair<string, IComponent* const>(type, component));
  supportedMessages.push_back(type);
}

void GameObject::receiveMessage(IMessage& message) {
  if (components.find(message.getType()) != components.end()) {
    message.setTarget(components[message.getType()]);
    MessageHandler::forwardMessage(message);
  }
}

void GameObject::copy(const GameObject& toCopy) {
  for (auto kvp : toCopy.dataComponents) {
    IDataComponent* c = ServiceLocator::getDataComponent(kvp.first, nullptr);
    c->setData(kvp.second->getData());
    addDataComponent(kvp.first, c);
  }

  for (auto kvp : toCopy.components) {
    addComponent(kvp.first, ServiceLocator::getMessageHandler(kvp.second->getType(), this));
  }
}
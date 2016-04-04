#pragma once
#include "IComponent.h"
#include "IDataComponent.h"
#include "Vector3.h"
#include <vector>
#include <map>
#include "MessageHandler.h"
#include "ServiceLocator.h"

using namespace std;

class ObjectPool;

class GameObject : public IMessageable {
  friend class ObjectPool;
public:
  GameObject() {}
  virtual ~GameObject();

  const vector<string>& getSupportedMessages() const override { return supportedMessages; }

  inline void addDataComponent(const string& type, IDataComponent* const component) { dataComponents.insert(pair<string, IDataComponent* const>(type, component)); }
  inline IDataComponent* const getDataComponent(const string& type) const { return dataComponents.find(type) != dataComponents.end() ? dataComponents.at(type) : nullptr; }

  inline void addComponent(const string& type, IComponent* const component);
  inline IComponent* const getMessageHandler(const string& type) const { return components.find(type) != components.end() ? components.at(type) : nullptr; }
protected:
  map<string, IDataComponent* const> dataComponents;
  map<string, IComponent* const> components;
  vector<string> supportedMessages;
private:
  void receiveMessage(IMessage& message) override;
  void copy(const GameObject& toCopy);
};

void GameObject::addComponent(const string& type, IComponent* const component) {
  components.insert(pair<string, IComponent* const>(type, component));
  supportedMessages.push_back(type);
}
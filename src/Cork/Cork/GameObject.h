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
public:
  GameObject() {}
  virtual ~GameObject();

  void copy(const GameObject& toCopy);

  const vector<size_t>& getSupportedMessages() const override { return supportedMessages; }
  int getUUId() const { return uuid; }

  void setUUId(int uuid) { this->uuid = uuid; }

  void addDataComponent(size_t type, IDataComponent* const component) { dataComponents.insert(pair<size_t, IDataComponent* const>(type, component)); }
  void removeDataComponent(size_t type) { dataComponents.erase(type); }
  IDataComponent* const getDataComponent(size_t type) const { return dataComponents.find(type) != dataComponents.end() ? dataComponents.at(type) : nullptr; }

  void addMessageHandler(size_t type, IComponent* const component);
  void removeMessageHandler(size_t type) { components.erase(type); }
  IComponent* const getMessageHandler(size_t type) const { return components.find(type) != components.end() ? components.at(type) : nullptr; }
protected:
  int uuid;
  map<size_t, IDataComponent* const> dataComponents;
  map<size_t, IComponent* const> components;
  vector<size_t> supportedMessages;
private:
  void receiveMessage(IMessage& message) override;
};
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
  int getUUId() const { return uuid; }

  void setUUId(int uuid) { this->uuid = uuid; }

  void addDataComponent(const string& type, IDataComponent* const component) { dataComponents.insert(pair<string, IDataComponent* const>(type, component)); }
  void removeDataComponent(const string& type) { dataComponents.erase(type); }
  IDataComponent* const getDataComponent(const string& type) const { return dataComponents.find(type) != dataComponents.end() ? dataComponents.at(type) : nullptr; }

  void addComponent(const string& type, IComponent* const component);
  void removeComponent(const string& type) { components.erase(type); }
  IComponent* const getMessageHandler(const string& type) const { return components.find(type) != components.end() ? components.at(type) : nullptr; }
protected:
  int uuid;
  map<string, IDataComponent* const> dataComponents;
  map<string, IComponent* const> components;
  vector<string> supportedMessages;
private:
  void receiveMessage(IMessage& message) override;
  void copy(const GameObject& toCopy);
};
#pragma once
#include "IComponent.h"
#include "IDataComponent.h"
#include "Vector3.h"
#include <vector>
#include <map>
#include "MessageHandler.h"

using namespace std;

class GameObject : public IMessageable {
public:
  GameObject() {}
  virtual ~GameObject();

  inline void addDataComponent(const string& type, IDataComponent* const component) { dataComponents.insert(pair<string, IDataComponent* const>(type, component)); }
  inline IDataComponent* const getDataComponent(const string& type) const { return dataComponents.find(type) != dataComponents.end() ? dataComponents.at(type) : nullptr; }

  inline void addComponent(const string& type, IComponent* const component) { components.insert(pair<string, IComponent* const>(type, component)); }
  inline IComponent* const getMessageHandler(const string& type) const { return components.find(type) != components.end() ? components.at(type) : nullptr; }
protected:
  map<string, IDataComponent* const> dataComponents;
  map<string, IComponent* const> components;
private:
  void receiveMessage(IMessage& message) override;
};
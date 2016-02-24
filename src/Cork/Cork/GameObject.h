#pragma once
#include "IComponent.h"
#include "Vector3.h"
#include <vector>
#include <map>
#include "MessageHandler.h"

using namespace std;

class GameObject : public IMessageable {
public:
  GameObject() {}
  GameObject(const Vector3<float> position);
  virtual ~GameObject();

  inline Vector3<float> getPositon() const { return position; }

  inline void setPosition(const Vector3<float> position) { this->position = position; }

  inline void addFunctionalComponent(const string& type, IComponent* const component) { components.insert(pair<string, IComponent* const>(type, component)); }
  inline IComponent* const getMessageHandler(const string& type) const { return components.find(type) != components.end() ? components.at(type) : nullptr; }
protected:
  Vector3<float> position;

  map<string, IComponent* const> components;
private:
  void receiveMessage(IMessage& message) override;
};
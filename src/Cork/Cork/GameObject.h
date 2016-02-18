#pragma once
#include "IComponent.h"
#include "Vector3.h"
#include <vector>
#include <map>

using namespace std;

class GameObject : public IMessageable {
public:
  GameObject() {}
  GameObject(const Vector3<float> position);
  virtual ~GameObject();

  inline Vector3<float> getPositon() const { return position; }

  inline void setPosition(const Vector3<float> position) { this->position = position; }

  inline void addComponent(IComponent* const component) { components.push_back(component); }
  inline void addFunctionalComponent(MessageType type, IComponent* const component) { functionalComponents.insert(pair<MessageType, IComponent* const>(type, component)); }

  void receiveMessage(const IMessage& message) override;
protected:
  Vector3<float> position;

  vector<IComponent* const> components;
  map<MessageType, IComponent* const> functionalComponents;
};
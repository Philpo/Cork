#pragma once
#include "IComponent.h"
#include "Vector3.h"
#include <vector>

using namespace std;

class GameObject : public IMessageable {
public:
  GameObject() {}
  GameObject(const Vector3<float> position);
  virtual ~GameObject();

  inline Vector3<float> getPositon() const { return position; }

  inline void setPosition(const Vector3<float> position) { this->position = position; }

  inline void addComponent(IComponent* const component) { components.push_back(component); }
protected:
  Vector3<float> position;

  vector<IComponent* const> components;
};
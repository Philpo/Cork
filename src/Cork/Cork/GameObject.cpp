#include "GameObject.h"

GameObject::GameObject(const Vector3<float> position) : position(position) {}

GameObject::~GameObject() {
  for (auto component : components) {
    delete component;
  }
}
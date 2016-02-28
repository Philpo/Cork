#include "ServiceLocator.h"

map<string, factoryFunction> ServiceLocator::factoryFunctions;
map<string, vector<IComponent* const>> ServiceLocator::components;

void ServiceLocator::cleanup() {
  for (auto kvp : components) {
    for (auto component : kvp.second) {
      delete component;
    }
  }
}

void ServiceLocator::addFactoryFunction(const string& componentType, factoryFunction function) {
  if (factoryFunctions.find(componentType) == factoryFunctions.end()) {
    factoryFunctions.insert(pair<string, factoryFunction>(componentType, function));
  }
}

IComponent* const ServiceLocator::getComponent(const string& componentType) {
  IComponent* component = nullptr;

  if (factoryFunctions.find(componentType) != factoryFunctions.end()) {
     component = factoryFunctions[componentType]();

    if (components.find(componentType) != components.end()) {
      components[componentType].push_back(component);
    }
    else {
      vector<IComponent* const> v = { component };
      components.insert(pair<string, vector<IComponent* const>>(componentType, v));
    }
  }

  return component;
}

void ServiceLocator::deleteComponent(IComponent*& toDelete) {
  if (components.find(toDelete->getType()) != components.end()) {
    if (remove<IComponent* const>(components[toDelete->getType()], toDelete)) {
      delete toDelete;
      toDelete = nullptr;
    }
  }
}
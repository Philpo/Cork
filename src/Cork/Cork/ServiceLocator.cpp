#include "ServiceLocator.h"

map<string, MessageHandlerFunction> ServiceLocator::messageHandlerFunctions;
map<string, vector<IComponent* const>> ServiceLocator::messageHandlers;

map<string, DataComponentFunction> ServiceLocator::dataComponentFunctions;
map<string, vector<IDataComponent* const>> ServiceLocator::dataComponents;

void ServiceLocator::cleanup() {
  for (auto kvp : messageHandlers) {
    for (auto component : kvp.second) {
      delete component;
    }
  }
  for (auto kvp : dataComponents) {
    for (auto component : kvp.second) {
      delete component;
    }
  }
  messageHandlers.clear();
  dataComponents.clear();
}

void ServiceLocator::addMessageHandlerFunction(const string& componentType, MessageHandlerFunction function) {
  if (messageHandlerFunctions.find(componentType) == messageHandlerFunctions.end()) {
    messageHandlerFunctions.insert(pair<string, MessageHandlerFunction>(componentType, function));
  }
}

IComponent* const ServiceLocator::getMessageHandler(const string& componentType) {
  return getMessageHandler(componentType, nullptr);
}

IComponent* const ServiceLocator::getMessageHandler(const string& componentType, void* data) {
  IComponent* component = nullptr;

  if (messageHandlerFunctions.find(componentType) != messageHandlerFunctions.end()) {
    try {
      component = messageHandlerFunctions[componentType](data);

      if (componentType != GRAPHICS_COMPONENT) {
        if (messageHandlers.find(componentType) != messageHandlers.end()) {
          messageHandlers[componentType].push_back(component);
        }
        else {
          vector<IComponent* const> v = { component };
          messageHandlers.insert(pair<string, vector<IComponent* const>>(componentType, v));
        }
      }
    }
    catch (exception&) {
      throw;
    }
  }

  return component;
}

void ServiceLocator::deleteMessageHandler(IComponent*& toDelete) {
  if (messageHandlers.find(toDelete->getType()) != messageHandlers.end()) {
    if (remove<IComponent* const>(messageHandlers[toDelete->getType()], toDelete)) {
      delete toDelete;
      toDelete = nullptr;
    }
  }
}

void ServiceLocator::addDataComponentFunction(const string& componentType, DataComponentFunction function) {
  if (dataComponentFunctions.find(componentType) == dataComponentFunctions.end()) {
    dataComponentFunctions.insert(pair<string, DataComponentFunction>(componentType, function));
  }
}

IDataComponent* const ServiceLocator::getDataComponent(const string& componentType, void* data) {
  IDataComponent* component = nullptr;

  if (dataComponentFunctions.find(componentType) != dataComponentFunctions.end()) {
    component = dataComponentFunctions[componentType](data);

    if (dataComponents.find(componentType) != dataComponents.end()) {
      dataComponents[componentType].push_back(component);
    }
    else {
      vector<IDataComponent* const> v = { component };
      dataComponents.insert(pair<string, vector<IDataComponent* const>>(componentType, v));
    }
  }

  return component;
}

void ServiceLocator::deleteDataComponent(const string& componentType, IDataComponent*& toDelete) {
  if (dataComponents.find(componentType) != dataComponents.end()) {
    if (remove<IDataComponent* const>(dataComponents[componentType], toDelete)) {
      delete toDelete;
      toDelete = nullptr;
    }
  }
}
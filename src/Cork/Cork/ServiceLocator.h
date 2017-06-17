#pragma once
#include <map>
#include <vector>
#include <functional>
#include "IComponent.h"
#include "IDataComponent.h"

using namespace std;

typedef function<IComponent* const (void*)> MessageHandlerFunction;
typedef function<IDataComponent* const (void*)> DataComponentFunction;

class ServiceLocator {
public:
  ServiceLocator() = delete;
  ServiceLocator(ServiceLocator& toCopy) = delete;
  ~ServiceLocator() = delete;

  ServiceLocator& operator=(ServiceLocator& rhs) = delete;

  static void cleanup();

  static void addMessageHandlerFunction(size_t componentType, MessageHandlerFunction function);
  static void removeMessageHandlerFunction(size_t componentType) { messageHandlerFunctions.erase(componentType); }
  static IComponent* const getMessageHandler(size_t componentType);
  static IComponent* const getMessageHandler(size_t componentType, void* data);
  static void deleteMessageHandler(IComponent*& toDelete);

  static void addDataComponentFunction(size_t componentType, DataComponentFunction function);
  static void removeDataComponentFunction(size_t componentType) { dataComponentFunctions.erase(componentType); }
  static IDataComponent* const getDataComponent(size_t componentType, void* data);
  static void deleteDataComponent(size_t componentType, IDataComponent*& toDelete);
private:
  static map<size_t, MessageHandlerFunction> messageHandlerFunctions;
  static map<size_t, vector<IComponent* const>> messageHandlers;

  static map<size_t, DataComponentFunction> dataComponentFunctions;
  static map<size_t, vector<IDataComponent* const>> dataComponents;
};
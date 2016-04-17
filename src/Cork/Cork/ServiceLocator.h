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

  static void addMessageHandlerFunction(const string& componentType, MessageHandlerFunction function);
  static IComponent* const getMessageHandler(const string& componentType);
  static IComponent* const getMessageHandler(const string& componentType, void* data);
  static void deleteMessageHandler(IComponent*& toDelete);

  static void addDataComponentFunction(const string& componentType, DataComponentFunction function);
  static IDataComponent* const getDataComponent(const string& componentType, void* data);
  static void deleteDataComponent(const string& componentType, IDataComponent*& toDelete);
private:
  static map<string, MessageHandlerFunction> messageHandlerFunctions;
  static map<string, vector<IComponent* const>> messageHandlers;

  static map<string, DataComponentFunction> dataComponentFunctions;
  static map<string, vector<IDataComponent* const>> dataComponents;
};
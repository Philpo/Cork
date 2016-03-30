#pragma once
#include <map>
#include <vector>
#include <functional>
#include "IComponent.h"
#include "IDataComponent.h"

using namespace std;

typedef function<IComponent* const (void*)> messageHandlerFunction;
typedef function<IDataComponent* const (void*)> dataComponentFunction;

class ServiceLocator {
public:
  ServiceLocator() = delete;
  ServiceLocator(ServiceLocator& toCopy) = delete;
  ~ServiceLocator() = delete;

  ServiceLocator& operator=(ServiceLocator& rhs) = delete;

  static void cleanup();

  static void addMessageHandlerFunction(const string& componentType, messageHandlerFunction function);
  static IComponent* const getMessageHandler(const string& componentType);
  static IComponent* const getMessageHandler(const string& componentType, void* data);
  static void deleteMessageHandler(IComponent*& toDelete);

  static void addDataComponentFunction(const string& componentType, dataComponentFunction function);
  static IDataComponent* const getDataComponent(const string& componentType, void* data);
  static void deleteDataComponent(const string& componentType, IDataComponent*& toDelete);
private:
  static map<string, messageHandlerFunction> messageHandlerFunctions;
  static map<string, vector<IComponent* const>> messageHandlers;

  static map<string, dataComponentFunction> dataComponentFunctions;
  static map<string, vector<IDataComponent* const>> dataComponents;
};
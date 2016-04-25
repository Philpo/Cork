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
<<<<<<< HEAD
=======
  static void removeMessageHandlerFunction(const string& componentType) { messageHandlerFunctions.erase(componentType); }
>>>>>>> 52a51f58ff3e8ee3cd3e848a451a444d40f4bcfc
  static IComponent* const getMessageHandler(const string& componentType);
  static IComponent* const getMessageHandler(const string& componentType, void* data);
  static void deleteMessageHandler(IComponent*& toDelete);

  static void addDataComponentFunction(const string& componentType, DataComponentFunction function);
<<<<<<< HEAD
=======
  static void removeDataComponentFunction(const string& componentType) { dataComponentFunctions.erase(componentType); }
>>>>>>> 52a51f58ff3e8ee3cd3e848a451a444d40f4bcfc
  static IDataComponent* const getDataComponent(const string& componentType, void* data);
  static void deleteDataComponent(const string& componentType, IDataComponent*& toDelete);
private:
  static map<string, MessageHandlerFunction> messageHandlerFunctions;
  static map<string, vector<IComponent* const>> messageHandlers;

  static map<string, DataComponentFunction> dataComponentFunctions;
  static map<string, vector<IDataComponent* const>> dataComponents;
};
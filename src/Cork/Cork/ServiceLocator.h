#pragma once
#include <map>
#include <vector>
#include <functional>
#include "IComponent.h"

using namespace std;

typedef function<IComponent* const ()> factoryFunction;

class ServiceLocator {
public:
  static void cleanup();
  static void addFactoryFunction(const string& componentType, factoryFunction);
  static IComponent* const getComponent(const string& componentType);
  static void deleteComponent(IComponent* toDelete);
private:
  static map<string, factoryFunction> factoryFunctions;
  static map<string, vector<IComponent* const>> components;

  ServiceLocator() {}
  ~ServiceLocator() {}
};
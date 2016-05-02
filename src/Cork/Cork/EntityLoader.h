#pragma once
#include "GameObject.h"
#include "ServiceLocator.h"
#include "RapidXML\rapidxml.hpp"
#include "RapidXML\rapidxml_utils.hpp"
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace rapidxml;

class EntityLoader {
public:
  EntityLoader() = delete;
  EntityLoader(EntityLoader& toCopy) = delete;
  ~EntityLoader() = delete;

  EntityLoader& operator=(EntityLoader& rhs) = delete;

  static void cleanup();

  static GameObject* const getEntity(int uId) { return allEntities.find(uId) != allEntities.end() ? allEntities.at(uId) : nullptr; }

  static GameObject* const loadEntity(const std::string& entityFile);
  static void loadEntities(const std::string& entitiesFile, vector<GameObject* const>& entities);
  static GameObject* const createEntity(int masterId);
private:
  static int entityId;
  static map<int, GameObject* const> allEntities;
  static void loadEntity(xml_node<>* entityNode, GameObject*& entity);
};
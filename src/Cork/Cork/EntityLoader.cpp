#include "EntityLoader.h"

int EntityLoader::entityId = 0;
map<int, GameObject* const> EntityLoader::allEntities;

void EntityLoader::cleanup() {
  for (auto kvp : allEntities) {
    delete kvp.second;
  }
  allEntities.clear();
}

GameObject* const EntityLoader::loadEntity(const std::string& entityFile) {
  GameObject* toReturn = new GameObject;

  try {
    file<> file(entityFile.c_str());
    xml_document<> doc;
    doc.parse<0>(file.data());
    xml_node<>* rootNode = doc.first_node();

    int uId = convertStringToNumber<int>(rootNode->first_attribute("uid")->value());

    loadEntity(rootNode, toReturn);
    toReturn->setUUId(uId);
    allEntities.insert(pair<int, GameObject* const>(uId, toReturn));
    entityId = uId + 1;
  }
  catch (exception&) {
    delete toReturn;
    throw;
  }

  return toReturn;
}

void EntityLoader::loadEntities(const std::string& entitiesFile, vector<GameObject* const>& entities) {
  GameObject* toAdd = nullptr;
  vector<int> parentIndices;

  try {
    file<> file(entitiesFile.c_str());
    xml_document<> doc;
    doc.parse<0>(file.data());
    xml_node<>* rootNode = doc.first_node();

    for (xml_node<>* entityNode = rootNode->first_node(); entityNode; entityNode = entityNode->next_sibling()) {
      int uId = convertStringToNumber<int>(entityNode->first_attribute("uid")->value());
      toAdd = new GameObject;
      loadEntity(entityNode, toAdd);
      toAdd->setUUId(uId);
      entityId = uId + 1;
      entities.push_back(toAdd);
      allEntities.insert(pair<int, GameObject* const>(uId, toAdd));
    }
  }
  catch (exception&) {
    for (auto entity : entities) {
      delete entity;
    }
    if (toAdd) {
      delete toAdd;
    }
    throw;
  }
}

void EntityLoader::loadEntity(xml_node<>* entityNode, GameObject*& entity) {
  try {
    if (entityNode->first_node("data_components")) {
      for (xml_node<>* componentNode = entityNode->first_node("data_components")->first_node(); componentNode; componentNode = componentNode->next_sibling()) {
        std::string componentType = componentNode->first_attribute("type")->value();
        entity->addDataComponent(componentType, ServiceLocator::getDataComponent(componentType, componentNode));
      }
    }

    if (entityNode->first_node("message_handlers")) {
      for (xml_node<>* componentNode = entityNode->first_node("message_handlers")->first_node(); componentNode; componentNode = componentNode->next_sibling()) {
        std::string messageType = componentNode->first_attribute("message_type")->value();
        std::string componentType = componentNode->first_attribute("type")->value();
        entity->addMessageHandler(messageType, ServiceLocator::getMessageHandler(componentType, entity));
      }
    }
  }
  catch (exception&) {
    throw;
  }
}

GameObject* const EntityLoader::createEntity(int masterId) {
  if (allEntities.find(masterId) != allEntities.end()) {
    GameObject* toReturn = new GameObject;
    toReturn->copy(*allEntities[masterId]);
    toReturn->setUUId(entityId);
    allEntities.insert(pair<int, GameObject* const>(entityId++, toReturn));
    return toReturn;
  }
  return nullptr;
}
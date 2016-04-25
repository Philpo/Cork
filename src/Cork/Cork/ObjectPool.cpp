#include "ObjectPool.h"

ObjectPool::ObjectPool(int poolSize) : poolSize(poolSize), pool(new GameObject[poolSize]) {
  for (int i = poolSize - 1; i >= 0; i--) {
    available.push_back(&pool[i]);
  }
}

ObjectPool::~ObjectPool() {
  delete[] pool;
}

GameObject* const ObjectPool::createObject(int masterUUId) {
  if (available.size() > 0) {
    GameObject* master = EntityLoader::getEntity(masterUUId);
    GameObject* toReturn = available.back();
    GameObject temp = *master;
    toReturn->copy(*master);
    available.pop_back();
    used.push_back(toReturn);
    return toReturn;
  }
  return nullptr;
}

void ObjectPool::removeObject(GameObject* const object) {
  if (contains(used, object)) {
    remove(used, object);
    available.push_back(object);
  }
}
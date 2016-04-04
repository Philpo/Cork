#pragma once
#include "GameObject.h"
#include "EntityLoader.h"
#include <vector>

using namespace std;

class ObjectPool {
public:
  ObjectPool(int poolSize);
  ~ObjectPool();

  inline int getSize() const { return poolSize; }
  inline int getAvailableSpace() const { return available.size(); }
  inline int getUsedSpace() const { return used.size(); }

  GameObject* const createObject(int masterUUId);
  void removeObject(GameObject* const object);
private:
  int poolSize;
  GameObject* pool;
  vector<GameObject*> used, available;
};
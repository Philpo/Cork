#pragma once
#include "GameObject.h"
#include "EntityLoader.h"
#include <vector>

using namespace std;

class ObjectPool {
public:
  ObjectPool(int poolSize);
  ~ObjectPool();

  int getSize() const { return poolSize; }
  int getAvailableSpace() const { return available.size(); }
  int getUsedSpace() const { return used.size(); }
  vector<GameObject*>& getObjects() { return used; }

  GameObject* const createObject(int masterUUId);
  void removeObject(GameObject* const object);
private:
  int poolSize;
  GameObject* pool;
  vector<GameObject*> used, available;
};
#pragma once
#include "GameObject.h"
#include "EntityLoader.h"
#include <vector>

using namespace std;

class ObjectPool {
public:
  ObjectPool(int poolSize);
  ~ObjectPool();

  GameObject* const createObject(int masterUUId);
  void removeObject(GameObject* const object);
private:
  int poolSize;
  GameObject* pool;
  vector<GameObject*> used, available;
};
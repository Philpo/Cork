#pragma once
#include <functional>
#include "GameObject.h"
#include "Message.h"

typedef std::function<void(const GameObject&, const GameObject&)> ResolvingFunction;

/**
* static class to be handle collision resolution
* reolving function must be passed in before use
*/
class CollisionResolver {
public:
  CollisionResolver() = delete;
  CollisionResolver(CollisionResolver& toCopy) = delete;
  ~CollisionResolver() = delete;

  CollisionResolver& operator=(CollisionResolver& rhs) = delete;

  static void setResolvingFunction(ResolvingFunction func) { function = func; }
  static void resolveCollision(const GameObject& lhs, const GameObject& rhs) { if (function) function(lhs, rhs); }
private:
  static ResolvingFunction function;
};
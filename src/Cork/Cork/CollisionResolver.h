#pragma once
#include <functional>
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "TransformComponent.h"

typedef std::function<void(const GameObject&, const GameObject&)> ResolvingFunction;

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
  static void basicCollisionResolution(const GameObject& lhs, const GameObject& rhs);
};
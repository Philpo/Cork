#pragma once
#include <functional>
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "TransformComponent.h"
#include "Message.h"

typedef std::function<void(const GameObject&, const GameObject&)> ResolvingFunction;

/**
* static class to be handle collision resolution
* by default, collisions will be resolved by adjusting the position of the colliding object to touch the object it collides with
* more complex functionality can be added by passing in a function pointer to the resolving function
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
  // resolves collisions by adjusting the position of the first object to touch the second object
  // assumes a left-hand coordinate system
  static void basicCollisionResolution(const GameObject& lhs, const GameObject& rhs);
};
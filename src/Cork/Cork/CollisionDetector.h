#pragma once
#include <functional>
#include "IDataComponent.h"

typedef std::function<bool (IDataComponent&, IDataComponent&)> DetectionFunction;

/**
 * static class to be used for collision detection
 * detection function must be passed in before use
 */
class CollisionDetector {
public:
  CollisionDetector() = delete;
  CollisionDetector(CollisionDetector& toCopy) = delete;
  ~CollisionDetector() = delete;

  CollisionDetector& operator=(CollisionDetector& rhs) = delete;

  static void setDetectionFunction(DetectionFunction func) { function = func; }
  static bool collisionDetection(IDataComponent& lhs, IDataComponent& rhs) { return function ? function(lhs, rhs) : false; }
private:
  static DetectionFunction function;
};
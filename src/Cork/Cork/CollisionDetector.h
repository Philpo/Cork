#pragma once
#include <functional>
#include "IDataComponent.h"
#include "BoundingBoxComponent.h"

typedef std::function<bool (IDataComponent&, IDataComponent&)> DetectionFunction;

/**
 * static class to be used for collision detection
 * by default, collision detection will be carried out using axis-aligned bounding boxes
 * more complex functionality can be added by passing in a function pointer to the detection function
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
  static bool axisAlignedBoundingBoxCollisionDetection(IDataComponent& lhs, IDataComponent& rhs);
};
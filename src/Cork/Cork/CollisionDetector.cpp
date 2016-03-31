#include "CollisionDetector.h"

DetectionFunction CollisionDetector::function = &CollisionDetector::axisAlignedBoundingBoxCollisionDetection;

bool CollisionDetector::axisAlignedBoundingBoxCollisionDetection(IDataComponent& lhs, IDataComponent& rhs) {
  const BoundingBox lhsBox = *(BoundingBox*) lhs.getData();
  const BoundingBox rhsBox = *(BoundingBox*) rhs.getData();

  float lhsBottomFace = lhsBox.centre.getY() - (lhsBox.height / 2.0f);
  float lhsTopFace = lhsBox.centre.getY() + (lhsBox.height / 2.0f);
  float lhsLeftFace = lhsBox.centre.getX() - (lhsBox.width / 2.0f);
  float lhsRightFace = lhsBox.centre.getX() + (lhsBox.width / 2.0f);
  float lhsNearFace = lhsBox.centre.getZ() - (lhsBox.depth / 2.0f);
  float lhsFarFace = lhsBox.centre.getZ() + (lhsBox.depth / 2.0f);

  float rhsBottomFace = rhsBox.centre.getY() - (rhsBox.height / 2.0f);
  float rhsTopFace = rhsBox.centre.getY() + (rhsBox.height / 2.0f);
  float rhsLeftFace = rhsBox.centre.getX() - (rhsBox.width / 2.0f);
  float rhsRightFace = rhsBox.centre.getX() + (rhsBox.width / 2.0f);
  float rhsNearFace = rhsBox.centre.getZ() - (rhsBox.depth / 2.0f);
  float rhsFarFace = rhsBox.centre.getZ() + (rhsBox.depth / 2.0f);

  // bottom edge of the first is above the top edge of the second, therefore no collision
  if (lhsBottomFace > rhsTopFace) {
    return false;
  }
  // top edge of the first is below the bottom edge of the second, therefore no collision
  if (lhsTopFace < rhsBottomFace) {
    return false;
  }
  // right edge of the first is to the left of the second's left edge, therefore no collision
  if (lhsRightFace < rhsLeftFace) {
    return false;
  }
  // left edge of the first is to the right of the second's right edge, therefore no collision
  if (lhsLeftFace > rhsRightFace) {
    return false;
  }
  // near edge of the first is behind the far edge of the second, therefore no collision
  if (lhsNearFace > rhsFarFace) {
    return false;
  }
  // far edge of the first is in front of the near edge of the second, therefore no collision
  if (lhsFarFace < rhsNearFace) {
    return false;
  }

  return true;
}
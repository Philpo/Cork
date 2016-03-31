#include "CollisionResolver.h"

ResolvingFunction CollisionResolver::function = &CollisionResolver::basicCollisionResolution;

void CollisionResolver::basicCollisionResolution(const GameObject& lhs, const GameObject& rhs) {
  // find where we've collided
  // then update our position so we tesselate with the object's bounding box

  float xCorrection = 0.0f;
  float yCorrection = 0.0f;
  float zCorrection = 0.0f;

  BoundingBox& lhsBox = *(BoundingBox*) lhs.getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
  BoundingBox rhsBox = *(BoundingBox*) rhs.getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
  Transform lhsTransform = *(Transform*) lhs.getDataComponent(TRANSFORM_COMPONENT)->getData();

  float top = lhsBox.centre.getY() + (lhsBox.height / 2.0f);
  float bottom = lhsBox.centre.getY() - (lhsBox.height / 2.0f);
  float left = lhsBox.centre.getX() - (lhsBox.width / 2.0f);
  float right = lhsBox.centre.getX() + (lhsBox.width / 2.0f);
  float near = lhsBox.centre.getZ() - (lhsBox.depth / 2.0f);
  float far = lhsBox.centre.getZ() + (lhsBox.depth / 2.0f);

  float previousTop = lhsTransform.previousPosition.getY() + (lhsBox.height / 2.0f);
  float previousBottom = lhsTransform.previousPosition.getY() - (lhsBox.height / 2.0f);
  float previousLeft = lhsTransform.previousPosition.getX() - (lhsBox.width / 2.0f);
  float previousRight = lhsTransform.previousPosition.getX() + (lhsBox.width / 2.0f);
  float previousNear = lhsTransform.previousPosition.getZ() - (lhsBox.depth / 2.0f);
  float previousFar = lhsTransform.previousPosition.getZ() + (lhsBox.depth / 2.0f);

  float collidedTop = rhsBox.centre.getY() + (rhsBox.height / 2.0f);
  float collidedBottom = rhsBox.centre.getY() - (rhsBox.height / 2.0f);
  float collidedLeft = rhsBox.centre.getX() - (rhsBox.width / 2.0f);
  float collidedRight = rhsBox.centre.getX() + (rhsBox.width / 2.0f);
  float collidedNear = rhsBox.centre.getZ() - (rhsBox.depth / 2.0f);
  float collidedFar = rhsBox.centre.getZ() + (rhsBox.depth / 2.0f);

  if (previousBottom >= collidedTop && (bottom <= collidedTop && bottom >= collidedBottom)) {
    yCorrection = collidedTop - bottom;
  }
  else if (previousTop <= collidedBottom && (top >= collidedBottom && top <= collidedTop)) {
    yCorrection = collidedBottom - top;
  }
  else if (previousRight <= collidedLeft && (right >= collidedLeft && right <= collidedRight)) {
    xCorrection = collidedLeft - right;
  }
  else if (previousLeft >= collidedRight && (left <= collidedRight && left >= collidedLeft)) {
    xCorrection = collidedRight - left;
  }
  else if ((far >= collidedNear && far <= collidedFar)) {
    zCorrection = collidedNear - far;
  }
  else if ((near <= collidedFar && near >= collidedNear)) {
    zCorrection = collidedFar - near;
  }

  lhsBox.centre += Vector3(xCorrection, yCorrection, zCorrection);
}
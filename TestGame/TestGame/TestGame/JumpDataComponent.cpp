#include "JumpDataComponent.h"

JumpDataComponent::JumpDataComponent() {
  jumpData = new JumpData;
}

JumpDataComponent::~JumpDataComponent() {
  delete jumpData;
}

void JumpDataComponent::setData(void* data) {
  JumpData toSet = *(JumpData*) data;

  jumpData->falling = toSet.falling;
  jumpData->jumping = toSet.jumping;
  jumpData->jumpControlPower = toSet.jumpControlPower;
  jumpData->jumpForce = toSet.jumpForce;
  jumpData->jumpTime = toSet.jumpTime;
  jumpData->maxJumpTime = toSet.maxJumpTime;
}
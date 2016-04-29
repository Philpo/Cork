#pragma once
#include "IDataComponent.h"

struct JumpData {
  JumpData() : jumping(false), falling(false), jumpTime(0.0f), maxJumpTime(0.0f), jumpForce(0.0f), jumpControlPower(0.0f) {}
  bool jumping, falling;
  float jumpTime, maxJumpTime, jumpForce, jumpControlPower;
};

class JumpDataComponent : public IDataComponent {
public:
  JumpDataComponent();
  ~JumpDataComponent();

  void* getData() override { return jumpData; }
  void setData(void* data) override;
private:
  JumpData* jumpData;
};
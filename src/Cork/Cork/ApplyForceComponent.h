#pragma once
#include "IComponent.h"
#include "ParticleComponent.h"
#include <algorithm>

struct ApplyForceComponentData {
  Particle* particle;
  double timeInMilliseconds;
};

class ApplyForceComponent : public IComponent {
public:
  ApplyForceComponent() {}
  ~ApplyForceComponent() {}

  const std::string& getType() const override { return APPLY_FORCE_COMPONENT; }
private:
  void receiveMessage(IMessage& message) override;
  static const Vector3 GRAVITY;
};
#pragma once
#include "IComponent.h"
#include "ParticleComponent.h"
#include <algorithm>

using namespace std;

class ApplyForceComponent : public IComponent {
public:
  ApplyForceComponent() {}
  ~ApplyForceComponent() {}

  size_t getType() const override { return APPLY_FORCE_COMPONENT; }
  const vector<size_t>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setParticle(Particle* const particle) { this->particle = particle; }
private:
  Particle* particle;
  static const vector<size_t> SUPPORTED_MESSAGES;
  static const Vector3 GRAVITY;

  void receiveMessage(IMessage& message) override;
};
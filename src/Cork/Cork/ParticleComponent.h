#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct Particle {
  Particle() : mass(0.0f), maxSpeed(0.0f) {}
  Vector3 totalForce, displacement, velocity, acceleration;
  float mass, maxSpeed;
  bool gravityEnabled = true;
};

class ParticleComponent : public IDataComponent {
public:
  ParticleComponent();
  ~ParticleComponent();

  void* getData() override { return particle; }
  void setData(void* data) override;
private:
  Particle* particle;
};
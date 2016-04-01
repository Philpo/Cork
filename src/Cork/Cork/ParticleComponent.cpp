#include "ParticleComponent.h"

ParticleComponent::ParticleComponent() {
  particle = new Particle;
}

ParticleComponent::~ParticleComponent() {
  delete particle;
}

void ParticleComponent::setData(void* data) {
  Particle toSet = *(Particle*) data;

  particle->totalForce = toSet.totalForce;
  particle->acceleration = toSet.acceleration;
  particle->displacement = toSet.displacement;
  particle->velocity = toSet.velocity;
  particle->mass = toSet.mass;
  particle->maxSpeed = toSet.maxSpeed;
  particle->gravityEnabled = toSet.gravityEnabled;
}
#include "ApplyForceComponent.h"

const vector<string> ApplyForceComponent::SUPPORTED_MESSAGES = { APPLY_FORCE_MESSAGE };
const Vector3 ApplyForceComponent::GRAVITY = Vector3(0.0f, -0.918f, 0.0f);

void ApplyForceComponent::receiveMessage(IMessage& message) {
  double timeInMilliseconds = *(double*) message.getData();

  float timeInSeconds = timeInMilliseconds / 1000.0f;
  particle->acceleration = (particle->totalForce / particle->mass) + (particle->gravityEnabled ? GRAVITY : Vector3(0.0f, 0.0f, 0.0f));
  // s = ut + 0.5at*t
  particle->displacement = (particle->velocity * timeInSeconds) + (particle->acceleration * (timeInSeconds * timeInSeconds)) / 2.0f;
  particle->velocity += particle->acceleration * timeInSeconds;
  particle->velocity.clamp(particle->maxSpeed);
  particle->totalForce = 0.0f;
}
#include "ApplyForceComponent.h"

const Vector3 ApplyForceComponent::GRAVITY = Vector3(0.0f, -0.918f, 0.0f);

void ApplyForceComponent::receiveMessage(IMessage& message) {
  ApplyForceComponentData data = *(ApplyForceComponentData*) message.getData();

  float timeInSeconds = std::min(data.timeInMilliseconds, 16.0) / 1000.0f;
  data.particle->acceleration = (data.particle->totalForce / data.particle->mass) + (data.particle->gravityEnabled ? GRAVITY : Vector3(0.0f, 0.0f, 0.0f));
  // s = ut + 0.5at*t
  data.particle->displacement = (data.particle->velocity * timeInSeconds) + (data.particle->acceleration * (timeInSeconds * timeInSeconds)) / 2.0f;
  data.particle->velocity += data.particle->acceleration * timeInSeconds;
  data.particle->velocity.clamp(data.particle->maxSpeed);
}
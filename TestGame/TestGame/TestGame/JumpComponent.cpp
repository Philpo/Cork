#include "JumpComponent.h"

const vector<string> JumpComponent::SUPPORTED_MESSAGES = { JUMP_MESSAGE };

void JumpComponent::receiveMessage(IMessage& message) {
  if (target) {
    Particle& p = *(Particle*) target->getDataComponent(PARTICLE_COMPONENT)->getData();
    JumpData& jd = *(JumpData*) target->getDataComponent(JUMP_DATA_COMPONENT)->getData();
    double elapsedTime = *(double*) message.getData();

    if (!jd.jumping && !jd.falling) {
      jd.jumping = true;
      jd.jumpTime = 0.0f;
      p.gravityEnabled = true;
      p.acceleration = 0.0f;
      p.displacement.setY(0.0f);
      p.velocity.setY(0.0f);
    }

    if (jd.jumping) {
      jd.jumpTime += (float) elapsedTime / 1000.0f;

      // If we are in the ascent of the jump
      if (0.0f < jd.jumpTime && jd.jumpTime <= jd.maxJumpTime) {
        p.totalForce += Vector3(0.0f, jd.jumpForce * (1.0f - (float) pow(jd.jumpTime / jd.maxJumpTime, jd.jumpControlPower)), 0.0f);
      }
      else {
        jd.jumpTime = 0.0f;
        jd.jumping = false;
        jd.falling = true;
        p.displacement.setY(0.0f);
        p.velocity.setY(0.0f);
      }
    }
  }
}
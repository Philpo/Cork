#pragma once
#include "GameObject.h"
#include "IDrawable.h"
#include "MessageHandler.h"
#include "DrawMessage.h"
#include "ConsoleGraphicsComponent.h"

class Player : public GameObject, IDrawable {
public:
  Player();
  Player(const Vector3<float> position);
  ~Player();

  void receiveMessage(const IMessage& message) override;
  void draw() const override;
};
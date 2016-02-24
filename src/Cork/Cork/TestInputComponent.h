#pragma once
#include "IComponent.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"
#include <windows.h>

class TestInputComponent : public IComponent {
public:
  TestInputComponent();
  ~TestInputComponent();

  const string& getType() const override { return INPUT_COMPONENT; }

  inline void setPlayer(IMessageable* const player) { this->player = player; }
private:
  IMessageable* player;
  void receiveMessage(IMessage& message) override;
};
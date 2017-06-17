#pragma once
#include "IComponent.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"
#include <windows.h>
#include "InputSystem.h"

class TestInputComponent : public IComponent {
public:
  TestInputComponent();
  ~TestInputComponent();

  size_t getType() const override { return INPUT_COMPONENT; }
  const vector<size_t>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setPlayer(IMessageable* const player) { this->player = player; }
private:
  IMessageable* player;
  static const vector<size_t> SUPPORTED_MESSAGES;

  //SHORT inputData = 0;

  void receiveMessage(IMessage& message) override;
};
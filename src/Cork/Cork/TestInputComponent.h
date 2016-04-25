#pragma once
#include "IComponent.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"
#include <windows.h>
#include "input.h"

class TestInputComponent : public IComponent {
public:
  TestInputComponent();
  ~TestInputComponent();

  const string& getType() const override { return INPUT_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setPlayer(IMessageable* const player) { this->player = player; }
private:
  IMessageable* player;
  static const vector<string> SUPPORTED_MESSAGES;

  //SHORT inputData = 0;

  void receiveMessage(IMessage& message) override;
};
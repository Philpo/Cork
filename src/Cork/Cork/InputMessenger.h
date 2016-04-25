#pragma once
#include "IComponent.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"
#include <windows.h>

class InputMessenger : public IComponent {
public:
	InputMessenger();
	~InputMessenger();

  const string& getType() const override { return INPUT_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setPlayer(IMessageable* const player) { this->player = player; }
private:
  IMessageable* player;
  static const vector<string> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};
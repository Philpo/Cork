#pragma once
#include "IMessage.h"
#include <vector>
#include <string>

class MessageHandler;

class IMessageable {
  friend class MessageHandler;
public:
  virtual const std::vector<std::string>& getSupportedMessages() const = 0;
private:
  virtual void receiveMessage(IMessage& message) = 0;
};
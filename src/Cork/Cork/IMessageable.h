#pragma once
#include "IMessage.h"

class MessageHandler;

class IMessageable {
  friend class MessageHandler;
private:
  virtual void receiveMessage(IMessage& message) = 0;
};
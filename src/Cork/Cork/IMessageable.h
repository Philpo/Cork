#pragma once
#include "IMessage.h"

class IMessageable {
public:
  virtual void receiveMessage(const IMessage& message) = 0;
};
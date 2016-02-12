#pragma once
#include "Utils.h"
#include "IMessage.h"

class MessageHandler {
public:
  MessageHandler();
  ~MessageHandler();

  void forwardMessage(const IMessage& message) const {}
};
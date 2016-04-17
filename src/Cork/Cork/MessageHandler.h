#pragma once
#include "Utils.h"
#include "IMessageable.h"

using namespace std;

class MessageHandler {
public:
  MessageHandler() = delete;
  MessageHandler(MessageHandler& toCopy) = delete;
  ~MessageHandler() = delete;

  MessageHandler& operator=(MessageHandler& rhs) = delete;

  static void forwardMessage(IMessage& message);
};
#pragma once
#include "Utils.h"
#include "IMessageable.h"

using namespace std;

class MessageHandler {
public:
  MessageHandler() {}
  ~MessageHandler() {}

  //static inline void addForwardingMapping(MessageType type, IMessageable* const target) { forwardingMappings.insert(pair<MessageType, IMessageable* const>(type, target)); }

  static void forwardMessage(IMessage& message);
};
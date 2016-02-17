#include "MessageHandler.h"

map<MessageType, IMessageable* const> MessageHandler::forwardingMappings;

void MessageHandler::forwardMessage(const IMessage& message) {
  if (forwardingMappings.find(message.getType()) != forwardingMappings.end()) {
    forwardingMappings[message.getType()]->receiveMessage(message);
  }
}
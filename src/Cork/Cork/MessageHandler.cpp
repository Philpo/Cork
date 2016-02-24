#include "MessageHandler.h"

void MessageHandler::forwardMessage(IMessage& message) {
  message.getTarget()->receiveMessage(message);
  //if (forwardingMappings.find(message.getType()) != forwardingMappings.end()) {
  //  forwardingMappings[message.getType()]->receiveMessage(message);
  //}
}
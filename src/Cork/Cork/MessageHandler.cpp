#include "MessageHandler.h"

void MessageHandler::forwardMessage(IMessage& message) {
  try {
    message.getTarget()->receiveMessage(message);
  }
  catch (exception&) {
    throw;
  }
  //if (forwardingMappings.find(message.getType()) != forwardingMappings.end()) {
  //  forwardingMappings[message.getType()]->receiveMessage(message);
  //}
}
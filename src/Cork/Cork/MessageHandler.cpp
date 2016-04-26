#include "MessageHandler.h"

void MessageHandler::forwardMessage(IMessage& message) {
  try {
    if (message.getTarget() && contains(message.getTarget()->getSupportedMessages(), message.getType())) {
      message.getTarget()->receiveMessage(message);
    }
  }
  catch (exception&) {
    throw;
  }
}
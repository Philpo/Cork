#include "TestInputComponent.h"

TestInputComponent::TestInputComponent(IMessageable& player) {
  MessageHandler::addForwardingMapping(POLL_INPUT_MESSAGE, this);
  MessageHandler::addForwardingMapping(INPUT_RECEIVED_MESSAGE, &player);
}

TestInputComponent::~TestInputComponent() {}

void TestInputComponent::receiveMessage(const IMessage& message) {
  InputMessage returnMessage;
  InputEvent event;

  if (message.getType() == POLL_INPUT_MESSAGE) {
    if (GetAsyncKeyState('W')) {
      while (GetAsyncKeyState('W')) {}
      event = MOVE_UP;
      returnMessage.setData(&event);
    }
    else if (GetAsyncKeyState('S')) {
      while (GetAsyncKeyState('S')) {}
      event = MOVE_DOWN;
      returnMessage.setData(&event);
    }
    else if (GetAsyncKeyState('A')) {
      while (GetAsyncKeyState('A')) {}
      event = MOVE_LEFT;
      returnMessage.setData(&event);
    }
    else if (GetAsyncKeyState('D')) {
      while (GetAsyncKeyState('D')) {}
      event = MOVE_RIGHT;
      returnMessage.setData(&event);
    }
  }

  MessageHandler::forwardMessage(returnMessage);
}
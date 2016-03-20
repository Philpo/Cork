#include "TestInputComponent.h"

TestInputComponent::TestInputComponent() : player(nullptr) {
  //MessageHandler::addForwardingMapping(POLL_INPUT_MESSAGE, this);
  //MessageHandler::addForwardingMapping(INPUT_RECEIVED_MESSAGE, &player);
}

TestInputComponent::~TestInputComponent() {}

void TestInputComponent::receiveMessage(IMessage& message) {
  Message returnMessage;
  string event;
  
  if (player) {
    returnMessage.setType(INPUT_RECEIVED_MESSAGE);
    returnMessage.setTarget(player);

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
      else if (GetAsyncKeyState('I')) {
        while (GetAsyncKeyState('I')) {}
        event = ROTATE_PITCH_UP;
        returnMessage.setData(&event);
      }
      else if (GetAsyncKeyState('K')) {
        while (GetAsyncKeyState('K')) {}
        event = ROTATE_PITCH_DOWN;
        returnMessage.setData(&event);
      }
      else if (GetAsyncKeyState('J')) {
        while (GetAsyncKeyState('J')) {}
        event = ROTATE_YAW_ANTICLOCKWISE;
        returnMessage.setData(&event);
      }
      else if (GetAsyncKeyState('L')) {
        while (GetAsyncKeyState('L')) {}
        event = ROTATE_YAW_CLOCKWISE;
        returnMessage.setData(&event);
      }
    }

    MessageHandler::forwardMessage(returnMessage);
  }
}
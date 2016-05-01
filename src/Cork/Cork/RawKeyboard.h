#pragma once

#include "IComponent.h"
#include "RawDevice.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"

#include "KeyMap.h"
#include <string>
#include <Windows.h>

using namespace std;


class RawKeyboard : public RawDevice
{
public:
	RawKeyboard();
	~RawKeyboard();

	void InitialiseRawInput();
	void recieveMessage(IMessage &message);

  IMessageable* player;
private:
  void receiveMessage(IMessage& message);
};


#pragma once

#include "IComponent.h"
#include "IRawDevice.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"

#include "KeyMap.h"
#include <string>
#include <Windows.h>

using namespace std;


class RawKeyboard : public IRawDevice
{
public:
	RawKeyboard();
	~RawKeyboard();

	void InitialiseRawInput();
	void recieveMessage(IMessage &message);

private:
  void receiveMessage(IMessage& message);
};


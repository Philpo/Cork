//http://codereal.blogspot.co.uk/2009/11/raw-input-introduction-part-1-keyboard.html
//https://www.youtube.com/watch?v=IEQSB5lDD_I
#pragma once
//||TODO|| use singleton

#include <Windows.h>
#include <string>
#include "RawDevice.h"
#include "RawKeyboard.h"
#include "InputMethod.h"
#include "IComponent.h"
#include "MessageHandler.h"
#include "utils.h"

using namespace std;


class RawInput : public InputMethod, public IComponent
{
public:
	RawInput();
	RawInput(HWND currentWindow);
	~RawInput();

	bool InitializeInput(string inputType);
	RawDevice* GetKeyboard() { return _keyboard; }
	RawDevice* GetJoystick() { return _Joystick; }
	RawDevice* GetMouse()	 { return _mouse; }

  const std::string& getType() const { return INPUT_COMPONENT; }
  const std::vector<std::string>& getSupportedMessages() const {
    return temp;
  }

  void setPlayer(IMessageable* const player) { ((RawKeyboard*) _keyboard)->player = player; }
private:
  void receiveMessage(IMessage& message) {
    message.setTarget(_keyboard);
    MessageHandler::forwardMessage(message);
  }
	HWND _window = 0;
	RawDevice* _keyboard = nullptr;
	RawDevice* _Joystick = nullptr;
	RawDevice* _mouse	 = nullptr;
  vector < string >  temp;
};


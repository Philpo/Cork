//http://codereal.blogspot.co.uk/2009/11/raw-input-introduction-part-1-keyboard.html
//https://www.youtube.com/watch?v=IEQSB5lDD_I
#pragma once
//||TODO|| use singleton

#include <Windows.h>
#include <string>
#include "IRawDevice.h"
#include "RawKeyboard.h"
#include "IInputMethod.h"
#include "IComponent.h"
#include "MessageHandler.h"
#include "utils.h"

using namespace std;


class RawInput : public IInputMethod, public IComponent
{
public:
	//RawInput(HWND currentWindow);
	RawInput();
	~RawInput();

	//--------SINGLETON---------//
	//static RawInput* Instance();

	void InitializeInput(string inputType);
	IRawDevice* GetKeyboard() { return _keyboard; }
	IRawDevice* GetJoystick() { return _Joystick; }
	IRawDevice* GetMouse()	 { return _mouse; }

	//vector<IRawDevice*> GetKeyboard() { return _keyboard; }
	//vector<IRawDevice*> GetJoystick() { return _joystick; }
	//vector<IRawDevice*> GetMouse()	 { return _mouse; }

  size_t getType() const { return INPUT_COMPONENT; }
  const std::vector<size_t>& getSupportedMessages() const {
    return _temp;
  }

  void setPlayer(IMessageable* const player) { ((RawKeyboard*) _keyboard)->player = player; }

protected:
	//SINGLETON
	//RawInput();

private:
	//SINGLETON
	//static RawInput* _instance;
  void receiveMessage(IMessage& message)
  {
    message.setTarget(_keyboard);
    MessageHandler::forwardMessage(message);
  }
	HWND _window = 0;

	//		||TODO|| These need to be made into vectors to allow for multipls of X devices

	IRawDevice* _keyboard = nullptr;
	IRawDevice* _Joystick = nullptr;
	IRawDevice* _mouse	 = nullptr;

	//vector<IRawDevice*> _keyboard;
	//vector<IRawDevice*> _joystick;
	//vector<IRawDevice*> _mouse;
	//vector<IRawDevice*> _misc;

	/*
	 *		||OR||, storing all devices in one vector would suit the better open/close princliple by preventing
	 *		the need for new vectors to be manually create. This shouldn't however be needed since the _misc vector
	 *		would hold all other devices.
	 *
	 */

	//vector<IRawDevice*> _rawDeviceVect;

  vector <size_t>  _temp;
};


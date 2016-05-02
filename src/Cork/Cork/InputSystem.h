#pragma once

#include <windows.h>
#include <vector>
#include "RawInput.h"
//#include "InputTypeEnums.h"
#include "IComponent.h"

using namespace std;

//#include "DirectInput.h"

class InputSystem : public IComponent
{
public:

	InputSystem(HWND window);
	~InputSystem();

	void setCurrentWindow(HWND window) { _window = window; }
	HWND GetCurrentWindow()	{return _window;}

	const IRawDevice* GetRawInputDevice(string inputType);

	bool CheckInputMethod(string inputMethod)
	{
		return (inputMethod == "rawInput" && _rawInput != nullptr) ? (true) : (false);
	};

  const std::string& getType() const { return INPUT_COMPONENT; }
  const std::vector<std::string>& getSupportedMessages() const {
    return temp;
  }
  void setPlayer(IMessageable* const player) { _rawInput->setPlayer(player); }
private:
  void receiveMessage(IMessage& message) { 
    message.setTarget(_rawInput);
    MessageHandler::forwardMessage(message);
  }

	//|| TODO || make this into a vector so it doesn't need to be updated each time

	RawInput* _rawInput = nullptr;
	//InputMethod* _rawInput = nullptr;
	//InputMethod* _xInput = nullptr;
	//InputMethod* _directInput = nullptr;

	//vector <inputMethod*> _inputMethods;


	HWND _window;

  vector < string >  temp;
};


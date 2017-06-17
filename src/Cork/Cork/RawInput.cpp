#include "RawInput.h"
//#include "InputTypeEnums.h"


RawInput::RawInput()
{
  _temp.push_back(std::hash<std::string>{}("CheckInputMessage"));
  InitializeInput(INPUTMETHOD_KEYBOARD);
}

//RawInput::RawInput(HWND window)
//{
//	_window = window;
//	InitializeInput(INPUTMETHOD_KEYBOARD);
//}


//----------||SINGLETON||----------
//RawInput* RawInput::_instance = 0;
//
//RawInput* RawInput::Instance()
//{
//	if (_instance == 0)
//	{
//		_instance = new RawInput;
//	}
//	return _instance;
//}

void RawInput::InitializeInput(string inputType)
{

	if (inputType == INPUTMETHOD_KEYBOARD)
		{
			_keyboard = new RawKeyboard;
			//GetKeyboard().push_back(new RawKeyboard);
		}
	else if (inputType == INPUTMETHOD_JOYSTICK)
		{

			//_keyboard = new RawJoyStick;

			//rawinput[0].usUsagePage = 1;
			//rawinput[0].usUsage = 4;
			//rawinput[0].dwFlags = 0;
			//rawinput[0].hwndTarget = _window;
			//_Joystick = new RawJoystick;
		}
}


RawInput::~RawInput()
{
	delete _keyboard;
	_keyboard = nullptr;
}

#include "RawInput.h"
//#include "InputTypeEnums.h"


RawInput::RawInput()
{
  temp.push_back("CheckInputMessage");
  InitializeInput(INPUTMETHOD_KEYBOARD);
}

RawInput::RawInput(HWND window)
{
	_window = window;
	InitializeInput(INPUTMETHOD_KEYBOARD);
}

bool RawInput::InitializeInput(string inputType)
{

	if (inputType == INPUTMETHOD_KEYBOARD)
		{
			_keyboard = new RawKeyboard;
		}
	else if (inputType == INPUTMETHOD_JOYSTICK)
		{
			//rawinput[0].usUsagePage = 1;
			//rawinput[0].usUsage = 4;
			//rawinput[0].dwFlags = 0;
			//rawinput[0].hwndTarget = _window;
			//_Joystick = new RawJoystick;
		}

	//||TODO|| can currently only have 1 of each input device
	//if (RegisterRawInputDevices(rawinput, 1 /*device quantity*/, sizeof(rawinput[0])) == false)
	//{
	//	return false;
	//}

	return true;
}


RawInput::~RawInput()
{
}

#include "RawInput.h"
#include "InputTypeEnums.h"


RawInput::RawInput()
{
	InitializeInput(KEYBOARD);
}

RawInput::RawInput(HWND window)
{
	_window = window;
	InitializeInput(KEYBOARD);
}

bool RawInput::InitializeInput(int inputType)
{
	RAWINPUTDEVICE rawinput[1];

	switch (inputType)
	{
		case KEYBOARD:
		{
			rawinput[0].usUsagePage = 1;		//Generic desktop control
			rawinput[0].usUsage = 6;			//desktop control - Keyboard
			rawinput[0].dwFlags = 0;			//how to handle device
			rawinput[0].hwndTarget = _window;	// restrict message to window, if NULL the window in focus is used
			_keyboard = new RawKeyboard;
			break;
		}
		case JOYSTICK:
		{
			rawinput[0].usUsagePage = 1;
			rawinput[0].usUsage = 4;
			rawinput[0].dwFlags = 0;
			rawinput[0].hwndTarget = _window;
			//_Joystick = new RawJoystick;
			break;
		}
	}

	//||TODO|| can currently only have 1 of each input device
	if (RegisterRawInputDevices(rawinput, 1 /*device quantity*/, sizeof(rawinput[0])) == false)
	{
		return false;
	}

	return true;
}


RawInput::~RawInput()
{
}

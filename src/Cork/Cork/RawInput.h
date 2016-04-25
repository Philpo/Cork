//http://codereal.blogspot.co.uk/2009/11/raw-input-introduction-part-1-keyboard.html
//https://www.youtube.com/watch?v=IEQSB5lDD_I
#pragma once
//||TODO|| use singleton

#include <Windows.h>
#include <string>
#include "RawDevice.h"
#include "RawKeyboard.h"
#include "InputMethod.h"

using namespace std;


class RawInput : public InputMethod
{
public:
	RawInput();
	RawInput(HWND currentWindow);
	~RawInput();

	bool InitializeInput(int inputType);
	RawDevice* GetKeyboard() { return _keyboard; }
	RawDevice* GetJoystick() { return _Joystick; }
	RawDevice* GetMouse()	 { return _mouse; }

private:
	HWND _window = 0;
	RawDevice* _keyboard = nullptr;
	RawDevice* _Joystick = nullptr;
	RawDevice* _mouse	 = nullptr;
};


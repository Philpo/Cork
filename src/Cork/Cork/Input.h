#pragma once

#include <windows.h>
#include <vector>
#include "RawInput.h"
#include "InputTypeEnums.h"

using namespace std;

//#include "DirectInput.h"

class Input
{
public:
	Input();
	Input(HWND window);
	~Input();

	void setCurrentWindow(HWND window) { _window = window; }
	HWND GetCurrentWindow = _window;

	RawDevice* GetRawInputDevice(int inputType);

	vector<InputMethod*> inputMethods;

	bool IsInputMethodInUse(InputMethod*);

	//bool InputMethodsInUse(InputMethod*);
	//InputMethod* GetInputMethod(string inputMethod)
	//{
	//	if (inputMethod == "rawInput")		{	return _rawInput;	}
	//};

	bool CheckInputMethod(string inputMethod)
	{
		return (inputMethod == "rawInput" && _rawInput != nullptr) ? (true) : (false);
	};

private:

	//|| TODO || make this into an vector so it doesn't need to be updated each time

	RawInput* _rawInput = nullptr;
	//InputMethod* _xInput = nullptr;
	//InputMethod* _directInput = nullptr;
	HWND _window;
};


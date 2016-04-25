#pragma once
#pragma comment(lib, "dinput8.lib")		//lib needed?
//#pragma comment(lib, "dxguip.lib")		//lib needed?

#define DIRECTINPUT_VERSON 0x0800		//Define input version


#include <dinput.h>

class DirectInput
{
public:
	DirectInput(void);
	~DirectInput(void);

	bool Initialise(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	bool Update();


	bool IsKeyDown(unsigned int key);
	bool IsKeyHit(unsigned int key);
	void GetMousePosition(int& x, int& y);

private:
	const static int _NumberOfKeys = 256;

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	IDirectInput8* _directInput;
	IDirectInputDevice8* _keyboard;
	IDirectInputDevice8* _mouse;
	DIMOUSESTATE _mouseState;

	bool _keys[_NumberOfKeys];
	bool _previousKeys[_NumberOfKeys];

	int _screenWidth;
	int _screenHeight;
	int _mouseX;
	int _mouseY;
};


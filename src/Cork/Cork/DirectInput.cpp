#include "DirectInput.h"

//using namespace std;

//https://www.youtube.com/watch?v=D4_HUSj-pNg

//acquire into
//https://msdn.microsoft.com/en-us/library/windows/desktop/ee415221(v=vs.85).aspx

DirectInput::DirectInput(void)
{
	_directInput = 0;
	_keyboard = 0;
	_mouse = 0;
	memset(_keys, 0, sizeof(bool)*_NumberOfKeys);
}


DirectInput::~DirectInput(void)
{
	if (_directInput)
	{
		_directInput->Release();
		_directInput = nullptr;
	}

	if (_keyboard)
	{
		_keyboard->Unacquire();
		_keyboard->Release();
		_keyboard = nullptr;
	}

	if (_mouse)
	{
		_mouse->Unacquire();
		_mouse->Release();
		_mouse = nullptr;
	}
}

bool DirectInput::Initialise(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;		//error testing

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_mouseX = 0;
	_mouseY = 0;

	////////////////////////////
	// direct input interface //
	////////////////////////////

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	////////////////////////
	// keyboard interface //
	////////////////////////

	result = _directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = _keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//stop keyboard from sharing with other programs - cooperative level
	result = _keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = _keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	/////////////////////
	// Mouse Interface //
	/////////////////////

	result = _directInput->CreateDevice(GUID_SysMouse, &_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = _mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	//stop mouse from sharing with other programs - cooperative level
	result = _mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = _mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool DirectInput::Update()
{
	memcpy(_previousKeys, _keys, sizeof(bool)*_NumberOfKeys);

	bool result;

	result = ReadKeyboard();
	if (FAILED(result))
	{
		return false;
	}

	result = ReadMouse();
	if (FAILED(result))
	{
		return false;
	}

	//mouse possition
	ProcessInput();

	return true;
}

bool DirectInput::ReadKeyboard()
{
	HRESULT result;

	//read keyboard
	result = _keyboard->GetDeviceState(sizeof(_keys), (LPVOID)&_keys); //LPVOID?
	result = ReadMouse();
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST || (result == DIERR_NOTACQUIRED)))
		{
			_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool DirectInput::ReadMouse()
{
	if (_mouse == nullptr)
	{
		_directInput->CreateDevice(GUID_SysMouse, &_mouse, NULL);
		return false;
	}

	HRESULT result;

	result = _mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST || (result == DIERR_NOTACQUIRED)))
		{
			_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void DirectInput::ProcessInput()
{
	_mouseX += _mouseState.lX;
	_mouseY += _mouseState.lY;

	//Ensure the mouse doesn't go off screen
	if (_mouseX < 0) _mouseX = 0;
	if (_mouseY < 0) _mouseY = 0;
	if (_mouseX > _screenWidth) _mouseX = _screenWidth;
	if (_mouseY > _screenHeight) _mouseY = _screenHeight;
}

bool DirectInput::IsKeyDown(unsigned int key)
{
	return _keys[key] == true;
}

bool DirectInput::IsKeyHit(unsigned int key)
{
	//if last key if up, and current key is down. Hit == true;
	return (_keys[key] == true) && (_previousKeys[key] == false);
}

void DirectInput::GetMousePosition(int &X, int &Y)
{
	X = _mouseX;
	Y = _mouseY;
}
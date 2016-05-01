#include "InputSystem.h"
#include "IMessageable.h"
#include "IMessage.h"
#include "Message.h"
#include "MessageHandler.h"
#include "rawInput.h"

#include <string>


//http://www.codeproject.com/Articles/185522/Using-the-Raw-Input-API-to-Process-Joystick-Input

using namespace std;

InputSystem::InputSystem(HWND window)
{
	setCurrentWindow(window);

  temp.push_back("CheckInputMessage");

	_rawInput = new RawInput;

	//inputMethods.push_back(new RawInput);
	//inputMethods.push_back(new XInput);
	//inputMethods.push_back(new DirectInput);


}


InputSystem::~InputSystem()
{
	delete _rawInput;
	_rawInput = nullptr;
}


//bool InputSystem::IsInputMethodInUse(InputMethod* inputMethod)
//{
//	//http://stackoverflow.com/questions/571394/how-to-find-an-item-in-a-stdvector
//	if (find(inputMethods.begin(), inputMethods.end(), inputMethod) != inputMethods.end())
//		return true;
//	else
//		return false;
//}


//
//IRawDevice* InputSystem::GetRawInputDevice(string inputType)
//{
//	if (inputType == INPUTMETHOD_KEYBOARD)
//		return _rawInput->GetKeyboard();
//
//	if (inputType == INPUTMETHOD_JOYSTICK)
//		return _rawInput->GetJoystick();
//
//}
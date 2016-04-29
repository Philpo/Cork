#include "Input.h"
#include "IMessageable.h"
#include "IMessage.h"
#include "Message.h"
#include "MessageHandler.h"
#include "rawInput.h"

#include <string>

// rs scheduler
//http://www.codeproject.com/Articles/185522/Using-the-Raw-Input-API-to-Process-Joystick-Input

using namespace std;

Input::Input()
{
}

Input::Input(HWND window)
{
	setCurrentWindow(window);

  temp.push_back("CheckInputMessage");
	_rawInput = new RawInput;
	//InputMethod* rawInput = new RawInput;
	inputMethods.push_back(new RawInput);
	//inputMethods.push_back(new XInput);
	//inputMethods.push_back(new DirectInput);


}


Input::~Input()
{
}


//bool Input::IsInputMethodInUse(InputMethod* inputMethod)
//{
//	//http://stackoverflow.com/questions/571394/how-to-find-an-item-in-a-stdvector
//	if (find(inputMethods.begin(), inputMethods.end(), inputMethod) != inputMethods.end())
//		return true;
//	else
//		return false;
//}



RawDevice* Input::GetRawInputDevice(int inputType)
{
	switch (inputType)
	{
	case KEYBOARD:
		return _rawInput->GetKeyboard();
		break;
	case JOYSTICK:
		return _rawInput->GetJoystick();
		break;
	}
}
#include "IRawDevice.h"


IRawDevice::IRawDevice()
{
  _temp.push_back("CheckInputMessage");
}


IRawDevice::~IRawDevice()
{
	delete _keyMap;
	_keyMap = nullptr;
}

/*		With more time a combo system could be added. This would require a method of
 *		counting the time duration between each input so that e.g. pressing "up" "up" "up"
 *		quickly can have a different outcome to pressing them slowly.
 *
 *		A thread could be used to keep track of time, and a thread wrapper used to call .join
 *		(via the destructor) once it's task is completed and it goes out of scope. Thread objects
 *		are another option.
 *
 *		Once X amount of time has passed without any input the vector should be cleared.
 */

void IRawDevice::NewInput(USHORT input)
{
	SetLastInput(GetCurrentInput());
	SetCurrentInput(input);

	GetRecentInput().push_back(input);

	//thread timer(&RawDevice::StartTimer, this);		//http://stackoverflow.com/questions/28574004/how-do-i-use-threading-in-a-class

	ExecuteInputEvent(input);
}

//void RawDevice::StartTimer()
//{
//	Sleep(1000);
//	recentInput.clear();
//
//	//remeber to use guards for threads accessing vector
//}

void IRawDevice::ExecuteInputEvent(USHORT input)
{
	
}
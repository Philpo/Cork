#include "IRawDevice.h"


IRawDevice::IRawDevice()
{
  _temp.push_back("CheckInputMessage");
  UsingComboSystem(true);
}


IRawDevice::~IRawDevice()
{
	delete _keyMap;
	_keyMap = nullptr;

	//delete threadTimer;
	//threadTimer = nullptr;

	////stop thread, wait for it to complete and then delete
	//functorTimer.threadRunning = false;
	//while (!functorTimer.threadExited)
	//{
	//	if (functorTimer.threadExited)
	//	{
	//		delete _timer;
	//		_timer = nullptr;
	//	}
	//}
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

void IRawDevice::RecordInput(USHORT input)
{

	/*
	*		By creating an array of all input conbos can be tracked.
	*		After a certain period of time 
	*
	*/

	SetLastInput(GetCurrentInput());
	SetCurrentInput(input);
	SetRecentInput(input);
	functorTimer->UpdateInput(true);
}

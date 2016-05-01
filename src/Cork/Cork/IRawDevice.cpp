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

//void RawDevice::StartTimer()
//{
//	Sleep(1000);
//	recentInput.clear();
//
//	//remeber to use guards for thread accessing vector
//}

void IRawDevice::NewInput(USHORT input)
{
	SetLastInput(GetCurrentInput());
	SetCurrentInput(input);
	//thread timer(&RawDevice::StartTimer, this);		//http://stackoverflow.com/questions/28574004/how-do-i-use-threading-in-a-class
	//timer.join();

	ExecuteInputEvent(input);
}

void IRawDevice::ExecuteInputEvent(USHORT input)
{
	
}
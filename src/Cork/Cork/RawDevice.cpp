#include "RawDevice.h"


RawDevice::RawDevice()
{
  temp.push_back("CheckInputMessage");
}


RawDevice::~RawDevice()
{
}

//void RawDevice::StartTimer()
//{
//	Sleep(1000);
//	recentInput.clear();
//
//	//remeber to use guards for thread accessing vector
//}

void RawDevice::NewInput(USHORT input)
{
	lastInput = currentInput;
	currentInput = input;
	//thread timer(&RawDevice::StartTimer, this);		//http://stackoverflow.com/questions/28574004/how-do-i-use-threading-in-a-class
	//timer.join();

	ExecuteInputEvent(input);
}

void RawDevice::ExecuteInputEvent(USHORT input)
{
	
}
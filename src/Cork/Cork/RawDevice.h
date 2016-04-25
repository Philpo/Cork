#pragma once
#include <Windows.h>
#include <vector>
//#include <chrono>
#include <thread>
#include "KeyMap.h"

using namespace std;

class RawDevice
{
public:
	RawDevice();
	~RawDevice();

	void NewInput(USHORT input);

	vector <USHORT> recentInput;
	USHORT lastInput;
	USHORT currentInput;
	chrono::steady_clock::time_point lastInputTime;
	chrono::steady_clock::time_point currentInputTime;
	chrono::steady_clock::duration timeSinceLastInput = lastInputTime - currentInputTime;

	void ExecuteInputEvent(USHORT input);
	KeyMap keyMap;
	//chrono::duration_cast<chrono::milliseconds>(timeSinceLastInput).count()

	void StartTimer();

private:

};


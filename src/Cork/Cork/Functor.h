#pragma once
#include <Windows.h>
#include <chrono>
#include <vector>
#include "ThreadWrapper.h"

using namespace std;

class Functor
{
public:
	Functor();
	~Functor();


	void operator()(vector<USHORT>* recentInput, thread* thisThread)
	{
		DetectCombos(recentInput);
		ThreadWrapper w(thisThread);
		threadExited = true;
	}

	void DetectCombos(vector<USHORT>* recentInput);

	USHORT newInput;
	void UpdateInput(bool update) { _updateInput = update; }
	bool threadRunning = true;
	bool threadExited = false;


	chrono::steady_clock::time_point GetLastInputTime()			{ return _lastInputTime; }
	chrono::steady_clock::time_point GetCurrentInputTime()		{ return _currentInputTime; }
	const void SetLastInputTime(chrono::steady_clock::time_point lastInputTime)			{ _lastInputTime = lastInputTime; }
	const void SetCurrentInputTime(chrono::steady_clock::time_point currentInputTime)	{ _currentInputTime = currentInputTime; }

private:
	chrono::steady_clock::time_point		_lastInputTime;
	chrono::steady_clock::time_point		_currentInputTime;
	const chrono::steady_clock::duration	_timeSinceLastInput = _lastInputTime - _currentInputTime;
	const chrono::steady_clock::duration	_conboTimeLimit = chrono::milliseconds(500);

	bool _updateInput = new bool;
};


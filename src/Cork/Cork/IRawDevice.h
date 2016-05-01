#pragma once
#include <Windows.h>
#include <vector>
//#include <chrono>
#include <thread>
#include "KeyMap.h"
#include "IComponent.h"
#include "MessageHandler.h"

using namespace std;

class IRawDevice : public IComponent
{
public:
	IRawDevice();
	~IRawDevice();

	virtual void InitialiseRawInput() = 0;
	virtual void NewInput(USHORT input);
	virtual void ExecuteInputEvent(USHORT input);

	//||TODO|| move
	KeyMap* GetKeyMap() { return _keyMap; }

	USHORT GetLastInput()										{ return _lastInput; }
	USHORT GetCurrentInput()									{ return _currentInput; }
	chrono::steady_clock::time_point GetLastInputTime()			{ return _lastInputTime; }
	chrono::steady_clock::time_point GetCurrentInputTime()		{ return _currentInputTime; }

	const void SetLastInput(USHORT lastInput)										{ _lastInput = lastInput; }
	const void SetCurrentInput(USHORT currentInput)									{ _currentInput = currentInput; }
	const void SetLastInput(chrono::steady_clock::time_point lastInputTime)			{ _lastInputTime = lastInputTime; }
	const void SetCurrentInput(chrono::steady_clock::time_point currentInputTime)	{ _currentInputTime = currentInputTime; }

	//chrono::duration_cast<chrono::milliseconds>(timeSinceLastInput).count()

	void StartTimer();

	IMessageable* player;

  const std::string& getType() const		{ return INPUT_COMPONENT; }
  const std::vector<std::string>& getSupportedMessages() const
  {
    return _temp;
  }


private:
  vector < string >  _temp;

  KeyMap* _keyMap = new KeyMap;

  vector <USHORT>	_recentInput;
  USHORT			_lastInput;
  USHORT			_currentInput;

  chrono::steady_clock::time_point		_lastInputTime;
  chrono::steady_clock::time_point		_currentInputTime;
  const chrono::steady_clock::duration	_timeSinceLastInput = _lastInputTime - _currentInputTime;
};


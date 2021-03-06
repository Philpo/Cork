#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <thread>
#include "KeyMap.h"
#include "IComponent.h"
#include "MessageHandler.h"
#include "Functor.h"
#include <string>
#include <iostream>
#include <mutex>

using namespace std;

class IRawDevice : public IComponent
{
public:
	IRawDevice();
	~IRawDevice();

	virtual void InitialiseRawInput() = 0;
	virtual void RecordInput(USHORT input);

	KeyMap* GetKeyMap() { return _keyMap; }

	void UsingComboSystem(bool option)	{	(option = true) ?
											(_timer = new thread(*functorTimer, GetRecentInput(), _timer)) :
											(_timer = nullptr); }

	Functor* functorTimer = new Functor;


	USHORT GetLastInput()										{ return _lastInput; }
	USHORT GetCurrentInput()									{ return _currentInput; }
	vector<USHORT>*GetRecentInput()								{ return _recentInput; }

	const void SetLastInput(USHORT lastInput)										{ _lastInput = lastInput; }
	const void SetCurrentInput(USHORT currentInput)									{ _currentInput = currentInput; }
	const void SetRecentInput(USHORT input)											{ _recentInput->push_back(input); }

	const void ClearRecentInput()								{ _recentInput->clear(); }

	mutex guard;

	//chrono::duration_cast<chrono::milliseconds>(timeSinceLastInput).count()

	IMessageable* player;

  size_t getType() const		{ return INPUT_COMPONENT; }
  const std::vector<size_t>& getSupportedMessages() const
  {
    return _temp;
  }


private:
  vector <size_t>  _temp;

  KeyMap* _keyMap = new KeyMap(INPUTMETHOD_KEYBOARD);

  vector<USHORT>*	_recentInput = new vector <USHORT>;
  USHORT			_lastInput;
  USHORT			_currentInput;

  chrono::steady_clock::time_point		_lastInputTime;
  chrono::steady_clock::time_point		_currentInputTime;
  const chrono::steady_clock::duration	_timeSinceLastInput = _lastInputTime - _currentInputTime;

  thread* _timer = nullptr;
};


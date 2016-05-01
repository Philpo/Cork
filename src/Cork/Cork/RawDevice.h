#pragma once
#include <Windows.h>
#include <vector>
//#include <chrono>
#include <thread>
#include "KeyMap.h"
#include "IComponent.h"
#include "MessageHandler.h"

using namespace std;

class RawDevice : public IComponent
{
public:
	RawDevice();
	~RawDevice();

	virtual void InitialiseRawInput() = 0;
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

  const std::string& getType() const { return INPUT_COMPONENT; }
  const std::vector<std::string>& getSupportedMessages() const {
    return temp;
  }
private:
  vector < string >  temp;
};


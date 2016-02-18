#pragma once
#include "IComponent.h"
#include "Window.h"
#include "MessageHandler.h"
#include "Message.h"
#include <vector>
#include <functional>

using namespace std;

typedef function<void (double)> gameLoopFunction;

class Scheduler {
public:
  Scheduler();
  Scheduler(const Window& window, double frameRateTarget, const wstring caption);
  ~Scheduler();

  inline void registerPollComponent(IComponent* const component) { pollEveryFrame.push_back(component); }
  inline void setGameLoopFunction(gameLoopFunction function) { this->function = function; }

  WPARAM gameLoop();
private:
  double timeLastFrame, frameRate, freq;
  __int64 counterStart; 
  wstring caption;
  Window window;
  gameLoopFunction function;
  vector<IComponent* const> pollEveryFrame;

  HRESULT startCounter();
  double getCounter();
  void calculateFrameRateStats();
};
#pragma once
#include "IComponent.h"
#include "Window.h"
#include "MessageHandler.h"
#include "Message.h"
#include "ServiceLocator.h"
#include "IGraphics.h"
#include "ResourceManager.h"
#include "EntityLoader.h"
#include <map>
#include <functional>

using namespace std;

typedef function<void (double)> GameLoopFunction;

class Scheduler {
public:
  Scheduler();
  Scheduler(double frameRateTarget, const wstring caption);
  ~Scheduler();

  void scheduleComponent(size_t messageType, IComponent* const component) { pollEveryFrame.insert(pair<size_t, IComponent* const>(messageType, component)); }
  void unscheduleComponent(size_t messageType) { pollEveryFrame.erase(messageType); }
  void setGameLoopFunction(GameLoopFunction function) { this->function = function; }

  WPARAM gameLoop();
private:
  double timeLastFrame, frameRate, freq;
  __int64 counterStart; 
  wstring caption;
  GameLoopFunction function;
  map<size_t, IComponent* const> pollEveryFrame;

  HRESULT startCounter();
  double getCounter();
  void calculateFrameRateStats();
};
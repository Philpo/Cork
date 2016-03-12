#include "Scheduler.h"

Scheduler::Scheduler() : timeLastFrame(0.0), frameRate(0.0), function(nullptr), caption(L"") {}

Scheduler::Scheduler(double frameRateTarget, const wstring caption) : 
  timeLastFrame(0.0), frameRate(1000.0 / frameRateTarget), function(nullptr), caption(caption) {
  startCounter();
}

Scheduler::~Scheduler() {}

void shutdown() {
  ResourceManager::cleanup();
  EntityLoader::cleanup();
  if (ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)) {
    ((IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT))->cleanup();
  }
  ServiceLocator::cleanup();
}

WPARAM Scheduler::gameLoop() {
  MSG msg = { 0 };

  while (WM_QUIT != msg.message) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      switch (msg.message) {
        // forward Windows key messages to the DirectXTK keyboard handler
        case WM_ACTIVATEAPP:
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
          // TODO maybe use dx toolkit keyboard class for input handling
          //Keyboard::ProcessMessage(msg.message, msg.wParam, msg.lParam);
          break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      calculateFrameRateStats();
      double currentTime = getCounter();
      double elapsedTime = currentTime - timeLastFrame;

      //TODO figure out how to poll components every frame; is there a better way than the below?
      for (auto kvp : pollEveryFrame) {
        MessageHandler::forwardMessage(Message(kvp.first, nullptr, kvp.second));
      }

      if (function) {
        function(elapsedTime);
      }

      double sleepTime = frameRate - (getCounter() - currentTime);
      if (sleepTime > 0) {
        Sleep(sleepTime);
      }
      timeLastFrame = currentTime;
    }
  }
  shutdown();
  return msg.wParam;
}

/*
* Taken from https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
*/
HRESULT Scheduler::startCounter() {
  LARGE_INTEGER li;
  if (!QueryPerformanceFrequency(&li)) {
    return -1;
  }

  freq = double(li.QuadPart) / 1000.0;

  QueryPerformanceCounter(&li);
  counterStart = li.QuadPart;

  return S_OK;
}

/*
* Taken from https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
*/
double Scheduler::getCounter() {
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return double(li.QuadPart - counterStart) / freq;
}

/*
* Taken from Frank Luna: 3D Game Programming with DirectX 11
*/
void Scheduler::calculateFrameRateStats() {
  static int frameCnt = 0;
  static double timeElapsed = 0.0;

  frameCnt++;

  if (getCounter() - timeElapsed >= 1.0f) {
    float fps = (float) frameCnt;
    float mspf = 1000.0f / fps;

    wostringstream outs;
    outs.precision(6);
    outs  << L"Cork    " << L"FPS: " << fps << L"    " << L"Frame Time: " << mspf << L" (ms)";
    Window::setWindowCaption(outs);

    frameCnt = 0;
    timeElapsed += 1000.0;
  }
}
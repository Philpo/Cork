#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <timeapi.h>
#include "MessageHandler.h"
#include "IComponent.h"
#include "Scheduler.h"
#include "GameObject.h"
#include "Window.h"
#include <iostream>

UINT min(UINT lhs, UINT rhs) {
  return lhs <= rhs ? lhs : rhs;
}

UINT max(UINT lhs, UINT rhs) {
  return lhs >= rhs ? lhs : rhs;
}

int WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPWSTR lpCmdLine, _In_ int cmdShow) {
  UNREFERENCED_PARAMETER(prevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  Window window;

  if (FAILED(window.initWindow(instance, cmdShow))) {
    return 0;
  }

  AllocConsole();
  //freopen("CONOUT$", "wb", stdout);

  // timer resolution code taken from https://msdn.microsoft.com/en-us/library/windows/desktop/dd743626%28v=vs.85%29.aspx
  TIMECAPS tc;
  UINT wTimerRes;

  //if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
  //  std::cerr << "error getting timer capabilities" << std::endl;
  //  return 0;
  //}

  //// set the timer resolution to the lowest possible, so that we can sleep the thread as accurately as possible
  //wTimerRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
  //timeBeginPeriod(wTimerRes);

  //timeEndPeriod(wTimerRes);
  return 0;
}
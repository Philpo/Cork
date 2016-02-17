#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#pragma comment(lib, "winmm.lib")  /* include winmm.lib */
#include <windows.h>
#include <timeapi.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Game.h"

Player* player;

UINT min(UINT lhs, UINT rhs) {
  return lhs <= rhs ? lhs : rhs;
}

UINT max(UINT lhs, UINT rhs) {
  return lhs >= rhs ? lhs : rhs;
}

int WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPWSTR lpCmdLine, _In_ int cmdShow) {
  UNREFERENCED_PARAMETER(prevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  AllocConsole();
  HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
  FILE *COutputHandle = _fdopen(SystemOutput, "w");
  *stdout = *COutputHandle;
  setvbuf(stdout, NULL, _IONBF, 0);

  // timer resolution code taken from https://msdn.microsoft.com/en-us/library/windows/desktop/dd743626%28v=vs.85%29.aspx
  TIMECAPS tc;
  UINT wTimerRes;

  if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
    std::cerr << "error getting timer capabilities" << std::endl;
    return 0;
  }

  // set the timer resolution to the lowest possible, so that we can sleep the thread as accurately as possible
  wTimerRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
  timeBeginPeriod(wTimerRes);

  Game game;

  if (FAILED(game.initGame(instance, cmdShow))) {
    return -1;
  }

  WPARAM param = game.startGame();

  timeEndPeriod(wTimerRes);
  return (int) param;
}
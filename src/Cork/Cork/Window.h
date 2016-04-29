#pragma once
#include <windows.h>
#include <sstream>
#include "Message.h"
#include "MessageHandler.h"
//#include "resource.h"

class Window {
public:
  Window() {}
  ~Window() {}

  static HWND getWindowHandle() { return window; };
  static void setWindowCaption(const std::wostringstream& caption) { SetWindowText(window, caption.str().c_str()); }
  static HRESULT initWindow(HINSTANCE instance, int cmdShow, int height, int width);
  static void setPlayer(IMessageable* const player);
private:
  static HWND window;
};
#pragma once
#include <windows.h>
#include <sstream>
//#include "resource.h"

class Window {
public:
  Window() {}
  ~Window() {}

  static HWND getWindowHandle() { return window; };
  static void setWindowCaption(const std::wostringstream& caption) { SetWindowText(window, caption.str().c_str()); }
  static HRESULT initWindow(HINSTANCE instance, int cmdShow, int height, int width);
private:
  static HWND window;
};
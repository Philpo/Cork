#pragma once
#include <windows.h>
#include <sstream>
//#include "resource.h"

class Window {
public:
  Window() {}
  ~Window() {}

  static inline HWND getWindowHandle() { return window; };
  static inline void setWindowCaption(const std::wostringstream& caption) { SetWindowText(window, caption.str().c_str()); }
  static HRESULT initWindow(HINSTANCE instance, int cmdShow);
private:
  static HWND window;
};
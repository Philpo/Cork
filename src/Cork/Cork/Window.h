#pragma once
#include <windows.h>
#include <sstream>
//#include "resource.h"

class Window {
public:
  Window() {}
  ~Window() {}

  inline HWND getWindowHandle() const { return window; };
  inline void setWindowCaption(const std::wostringstream& caption) const { SetWindowText(window, caption.str().c_str()); }

  HRESULT initWindow(HINSTANCE instance, int cmdShow);
private:
  HWND window;
};
#include "Window.h"

HWND Window::window;

LRESULT CALLBACK wndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

HRESULT Window::initWindow(HINSTANCE instance, int cmdShow, int height, int width) {
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = wndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = instance;
  wcex.hIcon = LoadIcon(instance, (LPCTSTR) 107);
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
  wcex.lpszMenuName = nullptr;
  wcex.lpszClassName = L"SampleWindowClass";
  wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR) 107);
  if (!RegisterClassEx(&wcex)) {
    return E_FAIL;
  }

  RECT rc = { 0, 0, width, height };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  window = CreateWindow(L"SampleWindowClass", L"DirectXTK Simple Sample", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, instance, nullptr);
  if (!window) {
    return E_FAIL;
  }

  ShowWindow(window, cmdShow);

  return S_OK;
}

LRESULT CALLBACK wndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message) {
    case WM_PAINT:
      hdc = BeginPaint(window, &ps);
      EndPaint(window, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(window, message, wParam, lParam);
  }
  return 0;
}

#include "RawInput.h"
#include "InputSystem.h"

#include <algorithm>
#include <iterator>
//#include "InputMethod.h"

HWND Window::window;

LRESULT CALLBACK wndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

InputSystem* inputSystem;
//RawInput* RawInput;

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

void Window::setPlayer(IMessageable* const player) {
	inputSystem->setPlayer(player);
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

    case WM_CREATE:	//on creating a window
    {
		inputSystem = new InputSystem(window);
    }
    break;

    case WM_INPUT:
    {
      {
        UINT dwSize = 0;

        GetRawInputData((HRAWINPUT) lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));			//calling buffer to find size

        LPBYTE inputBuffer = new BYTE[dwSize];															//create buffer of correct size | LPBYTE == BYTE*
        if (inputBuffer == NULL)
          return 0;

        GetRawInputData((HRAWINPUT) lParam, RID_INPUT, inputBuffer, &dwSize, sizeof(RAWINPUTHEADER));	//Call function with correct data
        RAWINPUT* raw = (RAWINPUT*) inputBuffer;

        switch (raw->header.dwType) {
          case RIM_TYPEKEYBOARD:
          {
            if (raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN) {
              std::wstring information =
                L"VKey - " + std::to_wstring(raw->data.keyboard.VKey) + L"\n";
              OutputDebugString(information.c_str());

              MessageHandler::forwardMessage(Message("CheckInputMessage", &raw->data.keyboard.VKey, inputSystem));
            }
          }
        }


      }
      break;


    }

    default:
      return DefWindowProc(window, message, wParam, lParam);
  }
  return 0;
}
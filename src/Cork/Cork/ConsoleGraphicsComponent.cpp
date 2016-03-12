#include "ConsoleGraphicsComponent.h"
#include "MessageHandler.h"
#include <Windows.h>

ConsoleGraphicsComponent::ConsoleGraphicsComponent() {
  //MessageHandler::addForwardingMapping(DRAW_MESSAGE, this);
}

void ConsoleGraphicsComponent::receiveMessage(IMessage& message) {
  COORD topLeft = { 0, 0 };
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO screen;
  DWORD written;

  GetConsoleScreenBufferInfo(console, &screen);
  FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
  FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
  SetConsoleCursorPosition(console, topLeft);

  Vector3 position = *(Vector3*) message.getData();
  stringstream s;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == position.getY() && j == position.getX()) {
        s << "P";
      }
      else {
        s << "_";
      }
    }
    s << std::endl;
  }
  std::cout << s.str();
}
#include "RawKeyboard.h"


RawKeyboard::RawKeyboard()
{
	InitialiseRawInput();
}

RawKeyboard::~RawKeyboard()
{
}

void RawKeyboard::InitialiseRawInput()
{
	RAWINPUTDEVICE rawinput[1];

	rawinput[0].usUsagePage = 1;		//Generic desktop control
	rawinput[0].usUsage = 6;			//desktop control - Keyboard
	rawinput[0].dwFlags = 0;			//how to handle device
	rawinput[0].hwndTarget = 0;			// restrict message to window, if NULL the window in focus is used

	(RegisterRawInputDevices(rawinput, 1, sizeof(rawinput[0])));
}

void RawKeyboard::receiveMessage(IMessage &message)
{
	Message returnMessage;
	string event;

  USHORT input = *(USHORT*) message.getData();

	if (player)
	{
		returnMessage.setType(INPUT_RECEIVED_MESSAGE);
		returnMessage.setTarget(player);

		USHORT i;

    //for (auto kvp : keyMap.inputMap) {
    //  if (input == kvp.second) {
    //    returnMessage.setData((void*) &kvp.first);
    //    break;
    //  }
    //}

		for (auto iter = GetKeyMap()->inputMap.begin(); iter != GetKeyMap()->inputMap.end(); iter++)
	{
      if (input == iter->second) 
	  {
        returnMessage.setData((void*) &iter->first);
        break;
      }
    }

		//for (i = keyMap.inputMap.begin; i != keyMap.inputMap.end; i++)
		//{
		//	if (currentInput == i)
		//	{
		//		int w = 2;
		//	}
		//}

		//if (currentInput == keyMap.inputMap.begin)
		//{

		//}


		MessageHandler::forwardMessage(returnMessage);
	}



}
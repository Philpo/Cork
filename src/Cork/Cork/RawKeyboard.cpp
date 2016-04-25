#include "RawKeyboard.h"


RawKeyboard::RawKeyboard()
{
}


RawKeyboard::~RawKeyboard()
{
}

void RawKeyboard::recieveMessage(IMessage &message)
{
	Message returnMessage;
	string event;

	keyMap;

	if (player)
	{
		returnMessage.setType(INPUT_RECEIVED_MESSAGE);
		returnMessage.setTarget(player);

		USHORT i;

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
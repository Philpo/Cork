#include "RawKeyboard.h"


RawKeyboard::RawKeyboard()
{
}


RawKeyboard::~RawKeyboard()
{
}

void RawKeyboard::receiveMessage(IMessage &message)
{
	Message returnMessage;
	string event;

	keyMap;

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

    for (auto iter = keyMap.inputMap.begin(); iter != keyMap.inputMap.end(); iter++) {
      if (input == iter->second) {
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
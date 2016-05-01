#include "KeyMap.h"


KeyMap::KeyMap(string inputType)
{
	if (inputType == INPUTMETHOD_KEYBOARD)
	{
		inputMap[MOVE_LEFT] = 65; // A
		inputMap[MOVE_RIGHT] = 68; // D
		inputMap[MOVE_FORWARD] = 87; // W
		inputMap[MOVE_BACK] = 83; // S
		inputMap[ROTATE_YAW_CLOCKWISE] = 76; // L
		inputMap[ROTATE_YAW_ANTICLOCKWISE] = 74; // J
		inputMap[ROTATE_PITCH_UP] = 73; // I
		inputMap[ROTATE_PITCH_DOWN] = 75; // K
		inputMap[FIRE] = 70; // F
	}
	else if (inputType == INPUTMETHOD_MOUSE)
	{
		///customise
		inputMap[MOVE_LEFT] = 65; // A
		inputMap[MOVE_RIGHT] = 68; // D
		inputMap[MOVE_FORWARD] = 87; // W
		inputMap[MOVE_BACK] = 83; // S
		inputMap[ROTATE_YAW_CLOCKWISE] = 76; // L
		inputMap[ROTATE_YAW_ANTICLOCKWISE] = 74; // J
		inputMap[ROTATE_PITCH_UP] = 73; // I
		inputMap[ROTATE_PITCH_DOWN] = 75; // K
		inputMap[FIRE] = 70; // F
	}
	else if (inputType == INPUTMETHOD_JOYSTICK)
	{
		///customise
		inputMap[MOVE_LEFT] = 65; // A
		inputMap[MOVE_RIGHT] = 68; // D
		inputMap[MOVE_FORWARD] = 87; // W
		inputMap[MOVE_BACK] = 83; // S
		inputMap[ROTATE_YAW_CLOCKWISE] = 76; // L
		inputMap[ROTATE_YAW_ANTICLOCKWISE] = 74; // J
		inputMap[ROTATE_PITCH_UP] = 73; // I
		inputMap[ROTATE_PITCH_DOWN] = 75; // K
		inputMap[FIRE] = 70; // F
	}
	else if (inputType == INPUTMETHOD_MISC)
	{
		///customise
		inputMap[MOVE_LEFT] = 65; // A
		inputMap[MOVE_RIGHT] = 68; // D
		inputMap[MOVE_FORWARD] = 87; // W
		inputMap[MOVE_BACK] = 83; // S
		inputMap[ROTATE_YAW_CLOCKWISE] = 76; // L
		inputMap[ROTATE_YAW_ANTICLOCKWISE] = 74; // J
		inputMap[ROTATE_PITCH_UP] = 73; // I
		inputMap[ROTATE_PITCH_DOWN] = 75; // K
		inputMap[FIRE] = 70; // F
	}
	else
	{
		//throw error
	}
}


KeyMap::~KeyMap()
{
}

void ChangeMappedKey(USHORT previousKey, USHORT newKey)
{
	//inputMap
}
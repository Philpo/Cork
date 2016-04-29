#include "KeyMap.h"


KeyMap::KeyMap()
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

	//inputMap[MOVE_UP] = 87;
	//inputMap[MOVE_DOWN] = 83;
	//inputMap[MOVE_LEFT] = 75;
	//inputMap[MOVE_RIGHT] = 68;
	//inputMap[MOVE_FORWARD] = 38;
	//inputMap[MOVE_BACK] = 40;
	//inputMap[ROTATE_YAW_CLOCKWISE] = 69;
	//inputMap[ROTATE_YAW_ANTICLOCKWISE] = 81;
	//inputMap[ROTATE_PITCH_UP] = 82;
	//inputMap[ROTATE_PITCH_DOWN] = 70;
}


KeyMap::~KeyMap()
{
}

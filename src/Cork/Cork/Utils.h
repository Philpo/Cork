#pragma once
#include <string>
#include <sstream>

enum MessageType {
  DRAW_MESSAGE = 0
, ADD_FORCE_MESSAGE = 1
, POLL_INPUT_MESSAGE = 2
, INPUT_RECEIVED_MESSAGE = 3
};

enum ComponentType {
  GRAPHICS_COMPONENT = 0
, PHYSICS_COMPONENT = 1
, INPUT_COMPONENT = 2
};

enum InputEvent {
  NONE = 0
, MOVE_UP = 1
, MOVE_DOWN = 2
, MOVE_LEFT = 3
, MOVE_RIGHT = 4
, STRAFE_LEFT = 5
, STRAFE_RIGHT = 6
, ROTATE_YAW_CLOCKWISE = 7
, ROTATE_YAW_ANTICLOCKWISE = 8
, ROTATE_PITCH_UP = 9
, ROTATE_PITCH_DOWN = 10
};

inline bool convertStringToBool(const std::string& toConvert) {
  if (toConvert == "true") {
    return true;
  }
  else {
    return false;
  }
}

template <class T>
inline T convertStringToNumber(const std::string& toConvert) {
  T r;
  std::stringstream(toConvert) >> r;
  return r;
}
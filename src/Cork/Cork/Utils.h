#pragma once
#include <string>
#include <sstream>

// general message types for use in any game
const std::string DRAW_MESSAGE = "DrawMessage";
const std::string ADD_FORCE_MESSAGE = "AddForceMessage";
const std::string POLL_INPUT_MESSAGE = "PollInputMessage";
const std::string INPUT_RECEIVED_MESSAGE = "InputReceivedMessage";

// general component types for use in any game
const std::string GRAPHICS_COMPONENT = "GraphicsComponent";
const std::string PHYSICS_COMPONENT = "PhysicsComponent";
const std::string INPUT_COMPONENT = "InputComponent";

// general input events for use in any game
const std::string NONE = "None";
const std::string MOVE_UP = "MoveUp";
const std::string MOVE_DOWN = "MoveDown";
const std::string MOVE_LEFT = "MoveLeft";
const std::string MOVE_RIGHT = "MoveRight";
const std::string STRAFE_LEFT = "StrafeLeft";
const std::string STRAFE_RIGHT = "StrafeRight";
const std::string ROTATE_YAW_CLOCKWISE = "RotateYawClockwise";
const std::string ROTATE_YAW_ANTICLOCKWISE = "RotateYawAntiClockwise";
const std::string ROTATE_PITCH_UP = "RotatePitchUp";
const std::string ROTATE_PITCH_DOWN = "RotatePitchDown";

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
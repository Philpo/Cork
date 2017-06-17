#pragma once
#include <string>
#include <sstream>
#include <vector>

// general message types for use in any game
const std::size_t DRAW_MESSAGE = std::hash<std::string>{}("DrawMessage");
const std::size_t ADD_FORCE_MESSAGE = std::hash<std::string>{}("AddForceMessage");
const std::size_t POLL_INPUT_MESSAGE = std::hash<std::string>{}("PollInputMessage");
const std::size_t INPUT_RECEIVED_MESSAGE = std::hash<std::string>{}("InputReceivedMessage");
const std::size_t APPLY_FORCE_MESSAGE = std::hash<std::string>{}("ApplyForceMessage");
const std::size_t UPDATE_AFTER_COLLISION_MESSAGE = std::hash<std::string>{}("UpdateAfterCollisionMessage");
const std::size_t JUMP_MESSAGE = std::hash<std::string>{}("JumpMessage");

// general component types for use in any game
const std::size_t GRAPHICS_COMPONENT = std::hash<std::string>{}("GraphicsComponent");
const std::size_t PHYSICS_COMPONENT = std::hash<std::string>{}("PhysicsComponent");
const std::size_t INPUT_COMPONENT = std::hash<std::string>{}("InputComponent");
const std::size_t APPLY_FORCE_COMPONENT = std::hash<std::string>{}("ApplyForceComponent");
const std::size_t TRANSFORM_COMPONENT = std::hash<std::string>{}("TransformComponent");
const std::size_t MESH_COMPONENT = std::hash<std::string>{}("MeshComponent");
const std::size_t CAMERA_COMPONENT = std::hash<std::string>{}("CameraComponent");
const std::size_t BOUNDING_BOX_COMPONENT = std::hash<std::string>{}("BoundingBoxComponent");
const std::size_t PARTICLE_COMPONENT = std::hash<std::string>{}("ParticleComponent");

// general input events for use in any game
const std::size_t NONE = std::hash<std::string>{}("None");
const std::size_t MOVE_UP = std::hash<std::string>{}("MoveUp");
const std::size_t MOVE_DOWN = std::hash<std::string>{}("MoveDown");
const std::size_t MOVE_LEFT = std::hash<std::string>{}("MoveLeft");
const std::size_t MOVE_RIGHT = std::hash<std::string>{}("MoveRight");
const std::size_t MOVE_FORWARD = std::hash<std::string>{}("MoveForward");
const std::size_t MOVE_BACK = std::hash<std::string>{}("MoveBack");
const std::size_t ROTATE_YAW_CLOCKWISE = std::hash<std::string>{}("RotateYawClockwise");
const std::size_t ROTATE_YAW_ANTICLOCKWISE = std::hash<std::string>{}("RotateYawAntiClockwise");
const std::size_t ROTATE_PITCH_UP = std::hash<std::string>{}("RotatePitchUp");
const std::size_t ROTATE_PITCH_DOWN = std::hash<std::string>{}("RotatePitchDown");
const std::size_t FIRE = std::hash<std::string>{}("Fire");
const std::size_t JUMP = std::hash<std::string>{}("Jump");

// input methods
const std::string INPUTMETHOD_KEYBOARD = "Keyboard";
const std::string INPUTMETHOD_JOYSTICK = "Joystick";
const std::string INPUTMETHOD_MOUSE = "Mouse";
const std::string INPUTMETHOD_MISC = "MiscInput";


inline bool convertStringToBool(const std::string& toConvert) {
  return toConvert == "true";
}

template <class T>
T convertStringToNumber(const std::string& toConvert) {
  T r;
  std::stringstream(toConvert) >> r;
  return r;
}

template <class T>
bool contains(const std::vector<T>& toCheck, const T& value) {
  for (auto t : toCheck) {
    if (t == value) {
      return true;
    }
  }
  return false;
}

template <class T>
bool remove(std::vector<T>& v, const T& toRemove) {
  for (std::vector<T>::iterator iter = v.begin(); iter != v.end(); iter++) {
    if (*iter == toRemove) {
      v.erase(iter, iter + 1);
      return true;
    }
  }
  return false;
}
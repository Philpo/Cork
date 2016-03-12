#pragma once
#include <string>
#include "TransformComponent.h"

const std::string BEGIN_FRAME_MESSAGE = "BeginFrameMessage";
const std::string SWAP_BUFFER_MESSAGE = "SwapBufferMessage";
const std::string SET_CONSTANT_BUFFER = "SetConstantBufferMessage";
const std::string SET_LIGHT = "SetLightMessage";
const std::string SET_CAMERA = "SetCameraMessage";

struct DrawInfo {
  int meshId;
  Transform transform;
};
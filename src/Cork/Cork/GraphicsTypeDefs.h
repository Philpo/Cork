#pragma once
#include <string>
#include "TransformComponent.h"

const std::string BEGIN_FRAME_MESSAGE = "BeginFrameMessage";
const std::string SWAP_BUFFER_MESSAGE = "SwapBufferMessage";
const std::string SET_CONSTANT_BUFFER = "SetConstantBuffer";

struct DrawInfo {
  int meshId;
  Transform transform;
};
#pragma once

const std::size_t BASIC_MOVE_COMPONENT = std::hash<string>{}("BasicMoveComponent");
const std::size_t CAMERA_MOVE_COMPONENT = std::hash<string>{}("CameraMovementComponent");
const std::size_t UPDATE_POSITION_COMPONENT = std::hash<string>{}("UpdatePositionComponent");
const std::size_t JUMP_COMPONENT = std::hash<string>{}("JumpComponent");
const std::size_t LIGHT_COMPONENT = std::hash<string>{}("LightComponent");
const std::size_t JUMP_DATA_COMPONENT = std::hash<string>{}("JumpDataComponent");
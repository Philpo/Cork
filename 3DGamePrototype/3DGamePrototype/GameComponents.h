#pragma once

const std::size_t BASIC_MOVE_COMPONENT = std::hash<string>{}("BasicMoveComponent");
const std::size_t CAMERA_MOVE_COMPONENT = std::hash<string>{}("CameraMovementComponent");
const std::size_t UPDATE_POSITION_COMPONENT = std::hash<string>{}("UpdatePositionComponent");
const std::size_t JUMP_COMPONENT = std::hash<string>{}("JumpComponent");
const std::size_t LIGHT_COMPONENT = std::hash<string>{}("LightComponent");
const std::size_t JUMP_DATA_COMPONENT = std::hash<string>{}("JumpDataComponent");
const std::size_t BULLET_COMPONENT = std::hash<string>{}("BulletComponent");
const std::size_t BULLET_DATA_COMPONENT = std::hash<string>{}("BulletDataComponent");
const std::size_t ADD_BULLET_MESSAGE = std::hash<string>{}("AddBulletMessage");
const std::size_t REMOVE_BULLET_MESSAGE = std::hash<string>{}("RemoveBulletMessage");
const std::size_t OBJECT_POOL_DATA_COMPONENT = std::hash<string>{}("ObjectPoolDataComponent");
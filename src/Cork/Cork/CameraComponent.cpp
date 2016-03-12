#include "CameraComponent.h"

CameraComponent::CameraComponent() {
  camera = new Camera;
}

CameraComponent::~CameraComponent() {
  if (camera) {
    delete camera;
  }
}

void CameraComponent::setData(void* data) {
  Camera cameraData = *(Camera*) data;

  camera->position = cameraData.position;
  camera->look = cameraData.look;
  camera->right = cameraData.right;
  camera->up = cameraData.up;
}
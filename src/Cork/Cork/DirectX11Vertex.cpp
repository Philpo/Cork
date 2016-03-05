#include "DirectX11Vertex.h"

DirectX11Vertex::DirectX11Vertex(int sizeInBytes) : sizeInBytes(sizeInBytes), buffer(new char[sizeInBytes]), currentPosition(buffer), currentBufferSize(0) {}

DirectX11Vertex::~DirectX11Vertex() {
  delete buffer;
}

void DirectX11Vertex::addFloat2(void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT2) <= sizeInBytes) {
      XMFLOAT2 vector = *(XMFLOAT2*) toAdd;

      XMFLOAT2& insertAt = *(XMFLOAT2*) currentPosition;
      insertAt = vector;
      currentPosition += sizeof(XMFLOAT2);
      currentBufferSize += sizeof(XMFLOAT2);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT2));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11Vertex::addFloat3(void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT3) <= sizeInBytes) {
      XMFLOAT3 vector = *(XMFLOAT3*) toAdd;

      XMFLOAT3& insertAt = *(XMFLOAT3*) currentPosition;
      insertAt = vector;
      currentPosition += sizeof(XMFLOAT3);
      currentBufferSize += sizeof(XMFLOAT3);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT3));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}
void DirectX11Vertex::addFloat4(void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT4) <= sizeInBytes) {
      XMFLOAT4 vector = *(XMFLOAT4*) toAdd;

      XMFLOAT4& insertAt = *(XMFLOAT4*) currentPosition;
      insertAt = vector;
      currentPosition += sizeof(XMFLOAT4);
      currentBufferSize += sizeof(XMFLOAT4);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT4));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}
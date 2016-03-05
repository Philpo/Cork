#include "DirectX11ConstantBuffer.h"

DirectX11ConstantBuffer::DirectX11ConstantBuffer(int sizeInBytes) : sizeInBytes(sizeInBytes), buffer(new char[sizeInBytes]), currentPosition(buffer), currentBufferSize(0) {}


DirectX11ConstantBuffer::~DirectX11ConstantBuffer() {
  delete buffer;
}

void DirectX11ConstantBuffer::clearBuffer() {
  ZeroMemory(buffer, sizeInBytes);
  currentPosition = buffer;
  currentBufferSize = 0;
}

char* DirectX11ConstantBuffer::addMatrix(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(XMMATRIX) <= sizeInBytes) {
      XMMATRIX vector = *(XMMATRIX*) toAdd;

      XMMATRIX& insertAt = *(XMMATRIX*) currentPosition;
      insertAt = vector;
      returnPointer = currentPosition;
      currentPosition += sizeof(XMMATRIX);
      currentBufferSize += sizeof(XMMATRIX);

      return returnPointer;
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMMATRIX));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addFloat2(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT2) <= sizeInBytes) {
      XMFLOAT2 vector = *(XMFLOAT2*) toAdd;

      XMFLOAT2& insertAt = *(XMFLOAT2*) currentPosition;
      insertAt = vector;
      returnPointer = currentPosition;
      currentPosition += sizeof(XMFLOAT2);
      currentBufferSize += sizeof(XMFLOAT2);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT2));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addFloat3(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT3) <= sizeInBytes) {
      XMFLOAT3 vector = *(XMFLOAT3*) toAdd;

      XMFLOAT3& insertAt = *(XMFLOAT3*) currentPosition;
      insertAt = vector;
      returnPointer = currentPosition;
      currentPosition += sizeof(XMFLOAT3);
      currentBufferSize += sizeof(XMFLOAT3);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT3));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addFloat4(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT4) <= sizeInBytes) {
      XMFLOAT4 vector = *(XMFLOAT4*) toAdd;

      XMFLOAT4& insertAt = *(XMFLOAT4*) currentPosition;
      insertAt = vector;
      returnPointer = nullptr;
      currentPosition += sizeof(XMFLOAT4);
      currentBufferSize += sizeof(XMFLOAT4);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMFLOAT4));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addLight(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(LightStruct) <= sizeInBytes) {
      LightStruct vector = *(LightStruct*) toAdd;

      LightStruct& insertAt = *(LightStruct*) currentPosition;
      insertAt = vector;
      returnPointer = currentPosition;
      currentPosition += sizeof(LightStruct);
      currentBufferSize += sizeof(LightStruct);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(LightStruct));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addMaterial(void* toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(Material) <= sizeInBytes) {
      Material vector = *(Material*) toAdd;

      Material& insertAt = *(Material*) currentPosition;
      insertAt = vector;
      returnPointer = currentPosition;
      currentPosition += sizeof(Material);
      currentBufferSize += sizeof(Material);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(Material));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addFloat(float toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(float) <= sizeInBytes) {
      float& insertAt = *(float*) currentPosition;
      insertAt = toAdd;
      returnPointer = nullptr;
      currentPosition += sizeof(float);
      currentBufferSize += sizeof(float);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(float));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}

char* DirectX11ConstantBuffer::addInt(int toAdd) {
  char* returnPointer = nullptr;

  if (toAdd) {
    if (currentBufferSize + sizeof(int) <= sizeInBytes) {
      int& insertAt = *(int*) currentPosition;
      insertAt = toAdd;
      returnPointer = currentPosition;
      currentPosition += sizeof(int);
      currentBufferSize += sizeof(int);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(int));
      throw std::exception(errorMessage.str().c_str());
    }
  }
  return returnPointer;
}
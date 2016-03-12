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

void DirectX11ConstantBuffer::addMatrix(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMMATRIX) <= sizeInBytes) {
      XMMATRIX matrix = *(XMMATRIX*) toAdd;

      XMMATRIX& insertAt = *(XMMATRIX*) currentPosition;
      insertAt = matrix;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
      currentPosition += sizeof(XMMATRIX);
      currentBufferSize += sizeof(XMMATRIX);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(XMMATRIX));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11ConstantBuffer::addFloat2(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT2) <= sizeInBytes) {
      XMFLOAT2 vector = *(XMFLOAT2*) toAdd;

      XMFLOAT2& insertAt = *(XMFLOAT2*) currentPosition;
      insertAt = vector;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
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

void DirectX11ConstantBuffer::addFloat3(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT3) <= sizeInBytes) {
      XMFLOAT3 vector = *(XMFLOAT3*) toAdd;

      XMFLOAT3& insertAt = *(XMFLOAT3*) currentPosition;
      insertAt = vector;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
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

void DirectX11ConstantBuffer::addFloat4(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(XMFLOAT4) <= sizeInBytes) {
      XMFLOAT4 vector = *(XMFLOAT4*) toAdd;

      XMFLOAT4& insertAt = *(XMFLOAT4*) currentPosition;
      insertAt = vector;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
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

void DirectX11ConstantBuffer::addLight(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(LightStruct) <= sizeInBytes) {
      LightStruct vector = *(LightStruct*) toAdd;

      LightStruct& insertAt = *(LightStruct*) currentPosition;
      insertAt = vector;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
      currentPosition += sizeof(LightStruct);
      currentBufferSize += sizeof(LightStruct);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(LightStruct));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11ConstantBuffer::addMaterial(string variableName, void* toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(Material) <= sizeInBytes) {
      Material vector = *(Material*) toAdd;

      Material& insertAt = *(Material*) currentPosition;
      insertAt = vector;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
      currentPosition += sizeof(Material);
      currentBufferSize += sizeof(Material);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(Material));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11ConstantBuffer::addFloat(string variableName, float toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(float) <= sizeInBytes) {
      float& insertAt = *(float*) currentPosition;
      insertAt = toAdd;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
      currentPosition += sizeof(float);
      currentBufferSize += sizeof(float);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(float));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11ConstantBuffer::addInt(string variableName, int toAdd) {
  if (toAdd) {
    if (currentBufferSize + sizeof(int) <= sizeInBytes) {
      int& insertAt = *(int*) currentPosition;
      insertAt = toAdd;
      variablePositions.insert(pair<string, char*>(variableName, currentPosition));
      currentPosition += sizeof(int);
      currentBufferSize += sizeof(int);
    }
    else {
      std::stringstream errorMessage;
      errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(int));
      throw std::exception(errorMessage.str().c_str());
    }
  }
}

void DirectX11ConstantBuffer::updateMatrix(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    XMMATRIX matrix = *(XMMATRIX*) data;

    XMMATRIX& insertAt = *(XMMATRIX*) location;
    insertAt = matrix;
  }
}

void DirectX11ConstantBuffer::updateFloat2(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    XMFLOAT2 vector = *(XMFLOAT2*) data;

    XMFLOAT2& insertAt = *(XMFLOAT2*) location;
    insertAt = vector;
  }
}

void DirectX11ConstantBuffer::updateFloat3(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    XMFLOAT3 vector = *(XMFLOAT3*) data;

    XMFLOAT3& insertAt = *(XMFLOAT3*) location;
    insertAt = vector;
  }
}

void DirectX11ConstantBuffer::updateFloat4(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    XMFLOAT4 vector = *(XMFLOAT4*) data;

    XMFLOAT4& insertAt = *(XMFLOAT4*) location;
    insertAt = vector;
  }
}

void DirectX11ConstantBuffer::updateLight(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    LightStruct light = *(LightStruct*) data;

    LightStruct& insertAt = *(LightStruct*) location;
    insertAt = light;
  }
}

void DirectX11ConstantBuffer::updateMaterial(string variableName, void* data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    Material material = *(Material*) data;

    Material& insertAt = *(Material*) location;
    insertAt = material;
  }
}

void DirectX11ConstantBuffer::updateFloat(string variableName, float data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];

    float& insertAt = *(float*) location;
    insertAt = data;
  }
}

void DirectX11ConstantBuffer::updateInt(string variableName, int data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];

    int& insertAt = *(int*) location;
    insertAt = data;
  }
}
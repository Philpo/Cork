#include "BinaryData.h"

BinaryData::BinaryData(size_t sizeInBytes) : sizeInBytes(sizeInBytes), buffer(new char[sizeInBytes]), currentPosition(buffer), currentBufferSize(0) {}

BinaryData::~BinaryData() {
  delete[] buffer;
}

void BinaryData::addVariable(const string& variableName, size_t variableSize) {
  if (currentBufferSize + variableSize <= sizeInBytes) {
    variablePositions.insert(pair<string, char*>(variableName, currentPosition));
    currentPosition += variableSize;
    currentBufferSize += variableSize;
  }
  else {
    std::stringstream errorMessage;
    errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + variableSize);
    throw std::exception(errorMessage.str().c_str());
  }
}
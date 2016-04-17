#pragma once
#include <exception>
#include <sstream>
#include <map>

using namespace std;

class BinaryData {
public:
  BinaryData(size_t sizeInBytes);
  BinaryData(BinaryData& toCopy) = delete;
  ~BinaryData();

  BinaryData& operator=(BinaryData& rhs) = delete;

  char* const getData() const { return buffer; }
  size_t getSizeInBytes() const { return sizeInBytes; }

  void addVariable(const string& variableName, size_t variableSize);

  template <class T>
  T* const getVariable(const string& variableName) const;

  template <class T>
  void addData(const string& variableName, T& toAdd);

  template <class T>
  void updateData(const string& variableName, T& data);
private:
  size_t sizeInBytes, currentBufferSize;
  char *buffer, *currentPosition;
  map<string, char*> variablePositions;
};

template <class T>
T* const BinaryData::getVariable(const string& variableName) const {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    return (T*) variablePositions.at(variableName);
  }
  return nullptr;
}

template <class T>
void BinaryData::addData(const string& variableName, T& toAdd) {
  if (currentBufferSize + sizeof(T) <= sizeInBytes) {
    T& insertAt = *(T*) currentPosition;
    insertAt = toAdd;
    variablePositions.insert(pair<string, char*>(variableName, currentPosition));
    currentPosition += sizeof(T);
    currentBufferSize += sizeof(T);
  }
  else {
    std::stringstream errorMessage;
    errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(T));
    throw std::exception(errorMessage.str().c_str());
  }
}

template <class T>
void BinaryData::updateData(const string& variableName, T& data) {
  if (variablePositions.find(variableName) != variablePositions.end()) {
    char* location = variablePositions[variableName];
    T& insertAt = *(T*) location;
    insertAt = data;
  }
}
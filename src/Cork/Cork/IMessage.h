#pragma once
#include "Utils.h"

class IMessage {
public:
  virtual ~IMessage() {}

  inline virtual MessageType getType() const = 0;
  inline virtual void* getData() const = 0;
  virtual void setData(void* data) = 0;
};
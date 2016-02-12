#pragma once
#include "Utils.h"

class IMessage {
public:
  virtual ~IMessage() {}

  inline virtual MessageType getType() const = 0;
};
#pragma once
#include "Utils.h"
#include "IMessage.h"

class IMoveable {
public:
  virtual ~IMoveable() {}

  virtual void receiveInput(const IMessage& input) = 0;
};
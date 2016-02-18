#pragma once
#include "Utils.h"

class IMessageable;

class IMessage {
public:
  virtual ~IMessage() {}

  inline virtual MessageType getType() const = 0;
  inline virtual void* getData() const = 0;
  inline virtual IMessageable* const getTarget() const = 0;

  virtual void setType(MessageType type) = 0;
  virtual void setData(void* data) = 0;
  virtual void setTarget(IMessageable* const target) = 0;
};
#pragma once
#include "Utils.h"

class IMessageable;

class IMessage {
public:
  virtual ~IMessage() {}

  virtual std::size_t getType() const = 0;
  virtual void* getData() const = 0;
  virtual IMessageable* const getTarget() const = 0;

  virtual void setType(std::size_t type) = 0;
  virtual void setData(void* data) = 0;
  virtual void setTarget(IMessageable* const target) = 0;
};
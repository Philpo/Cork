#pragma once
#include "IMessage.h"

class Message : public IMessage {
public:
  Message() : type(-1), data(nullptr), target(nullptr) {}
  Message(std::size_t type, void* data, IMessageable* const target) : type(type), data(data), target(target) {}
  ~Message() {}

  std::size_t getType() const override { return type; }
  void* getData() const override { return data; }
  IMessageable* const getTarget() const override { return target; }

  void setType(std::size_t type) override { this->type = type; }
  void setData(void* data) override { this->data = data; }
  void setTarget(IMessageable* const target) override { this->target = target; }
private:
  std::size_t type;
  void* data;
  IMessageable* target;
};
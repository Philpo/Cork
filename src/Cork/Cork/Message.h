#pragma once
#include "IMessage.h"

class Message : public IMessage {
public:
  Message() : data(nullptr), target(nullptr) {}
  Message(MessageType type, void* data, IMessageable* const target) : type(type), data(data), target(target) {}
  ~Message() {}

  MessageType getType() const override { return type; }
  void* getData() const override { return data; }
  IMessageable* const getTarget() const override { return target; }

  void setType(MessageType type) override { this->type = type; }
  void setData(void* data) override { this->data = data; }
  void setTarget(IMessageable* const target) override { this->target = target; }
private:
  MessageType type;
  void* data;
  IMessageable* target;
};
#pragma once
#include "IMessage.h"

class Message : public IMessage {
public:
  Message() : type(""), data(nullptr), target(nullptr) {}
  Message(const std::string& type, void* data, IMessageable* const target) : type(type), data(data), target(target) {}
  ~Message() {}

  const std::string& getType() const override { return type; }
  void* getData() const override { return data; }
  IMessageable* const getTarget() const override { return target; }

  void setType(const std::string& type) override { this->type = type; }
  void setData(void* data) override { this->data = data; }
  void setTarget(IMessageable* const target) override { this->target = target; }
private:
  std::string type;
  void* data;
  IMessageable* target;
};
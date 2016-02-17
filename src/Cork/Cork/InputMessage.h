#pragma once
#include "IMessage.h"

class InputMessage : public IMessage {
public:
  InputMessage() : data(nullptr) {}
  ~InputMessage() {}

  MessageType getType() const override { return INPUT_RECEIVED_MESSAGE; }
  void* getData() const override { return data; }
  void setData(void* data) { this->data = data; }
private:
  void* data;
};
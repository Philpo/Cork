#pragma once
#include "IMessage.h"

class PollInputMessage : public IMessage {
public:
  PollInputMessage() : data(nullptr) {}
  ~PollInputMessage() {}

  MessageType getType() const override { return POLL_INPUT_MESSAGE; }
  void* getData() const override { return data; }
  void setData(void* data) { this->data = data; }
private:
  void* data;
};
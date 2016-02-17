#pragma once
#include "IMessage.h"

class DrawMessage : public IMessage {
public:
  DrawMessage() : data(nullptr) {}
  ~DrawMessage() {}

  MessageType getType() const override { return DRAW_MESSAGE; }
  void* getData() const override { return data; }
  void setData(void* data) { this->data = data; }
private:
  void* data;
};
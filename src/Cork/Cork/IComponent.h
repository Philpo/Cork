#pragma once
#include "Utils.h"
#include "IMessage.h"
#include "MessageHandler.h"

class IComponent {
public:
  virtual ~IComponent() {}

  inline virtual ComponentType getType() const = 0;
  virtual void sendMessage(const MessageHandler& messageHandler) const = 0;
  virtual void receiveMessage(const IMessage& message) = 0;
};
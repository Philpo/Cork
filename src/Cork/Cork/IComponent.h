#pragma once
#include "Utils.h"
#include "IMessageable.h"

class IComponent : public IMessageable {
public:
  virtual ~IComponent() {}

  inline virtual ComponentType getType() const = 0;
  //virtual void sendMessage(const MessageHandler& messageHandler) const = 0;
};
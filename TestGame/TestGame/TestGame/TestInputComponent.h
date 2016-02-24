#pragma once
#include "IComponent.h"
#include "IMessageable.h"
#include "MessageHandler.h"
#include "Message.h"
#include <windows.h>

class TestInputComponent : public IComponent {
public:
  TestInputComponent(IMessageable& player);
  ~TestInputComponent();

  const string& getType() const override { return INPUT_COMPONENT; }
private:
  IMessageable& player;
  void receiveMessage(IMessage& message) override;
};
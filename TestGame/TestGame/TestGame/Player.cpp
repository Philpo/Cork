#include "Player.h"

Player::Player() : GameObject() {}

Player::Player(const Vector3<float> position) : GameObject(position) {
  addComponent(new ConsoleGraphicsComponent());
}

Player::~Player() {
}

void Player::receiveMessage(const IMessage& message) {
  if (message.getType() == INPUT_RECEIVED_MESSAGE) {
    InputEvent* event = (InputEvent*) message.getData();

    if (event) {
      switch (*event) {
        case MOVE_UP:
          position.setY(position.getY() - 1.0f);
          break;
        case MOVE_DOWN:
          position.setY(position.getY() + 1.0f);
          break;
        case MOVE_LEFT:
          position.setX(position.getX() - 1.0f);
          break;
        case MOVE_RIGHT:
          position.setX(position.getX() + 1.0f);
          break;
        case NONE:
          break;
      }
    }
  }
}

void Player::draw() const {
  DrawMessage message;
  message.setData((void*) &position);
  MessageHandler::forwardMessage(message);
}
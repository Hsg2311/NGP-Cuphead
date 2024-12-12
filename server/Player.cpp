#include "Player.hpp"
#include "Timer.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

#include <ranges>
#include <algorithm>

Player::Player() {

}

void Player::update() {

}

void Player::onCollision(Object* other) {
}

void Player::onCollisionEntry(Object* other) {
	getCollider()->addCollisionCount();
}

void Player::onCollisionExit(Object* other) {
	getCollider()->subCollisionCount();
}


#include "Player.hpp"
#include "ResourceHandler.hpp"
#include "Camera.hpp"
#include "InputDeviceHandler.hpp"
#include "Timer.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

#include "Projectile.hpp"
#include <ranges>
#include <algorithm>

Player::Player(const std::vector<texInfo>& info): Object(), inputEnabled_(false) {
	createAnimator();

	

	getAnimator()->play(info.front().resKey);

	createCollider();
	getCollider()->setScale(Vec2{ 100.f, 100.f });
}

void Player::update() {
	if (!inputEnabled_) {
		return;
	}

	bool bUp = false;
	bool bDown = false;
	bool bLeft = false;
	bool bRight = false;


	if (KEY_HOLD(InputData::LEFT)) {
		bLeft = true;
	}
	if (KEY_HOLD(InputData::RIGHT)) {
		bRight = true;
	}

	auto packet = Packet{
		.type = PacketType::INPUT,
		.in = {
			.id = getID().value(),
			.left = bLeft,
			.right = bRight,
			.up = bUp,
			.down = bDown,
		}
	};

	if (bUp || bDown || bRight || bLeft) {
		SendingStorage::getInst().pushPacket(packet);
	}
}

void Player::render(HDC hdc) {
	componentRender(hdc);
}

void Player::onCollision(Object* other) {
}

void Player::onCollisionEntry(Object* other) {
	getCollider()->addCollisionCount();
}

void Player::onCollisionExit(Object* other) {
	getCollider()->subCollisionCount();
}

void Player::createProjectile( ) {
	auto playerPos = getObjPos( );
	playerPos.y -= getObjScale( ).y / 2.f;

	Projectile* projectile = new Projectile{ };
	projectile->setObjName( L"Player_Projectile" );
	projectile->setObjPos( playerPos );
	projectile->setObjScale( Vec2{ 30.f, 30.f } );
	projectile->setDirection( Vec2( 0.f, 1.f ) );

	createObject( GROUP_TYPE::PLAYER_PROJECTILE, projectile );
};


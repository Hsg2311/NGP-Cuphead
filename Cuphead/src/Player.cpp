#include "Player.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "Projectile.hpp"
#include "func.hpp"
#include "SendingStorage.hpp"

#include <ranges>
#include <algorithm>


Player::Player(const std::vector<texInfo>& info) : Object(), inputEnabled_(false) {
	createAnimator();



	getAnimator()->play(info.front().resKey);

	createCollider();
	getCollider()->setScale(Vec2{ 100.f, 100.f });
}


Player::~Player( ) {}

void Player::update() {
	if (!inputEnabled_) {
		return;
	}

	bool bUp = false;
	bool bDown = false;
	bool bLeft = false;
	bool bRight = false;
	bool bAttack = false;


	if (KEY_HOLD(InputData::LEFT)) {
		bLeft = true;
	}
	if (KEY_HOLD(InputData::RIGHT)) {
		bRight = true;
	}
	if (KEY_HOLD(InputData::Z)) {
		bAttack = true;
	}

	auto packet = Packet{
		.type = PacketType::INPUT,
		.in = {
			.id = getID().value(),
			.left = bLeft,
			.right = bRight,
			.up = bUp,
			.down = bDown,
			.attack = bAttack
		}
	};

	if (bUp || bDown || bRight || bLeft|| bAttack) {
		SendingStorage::getInst().pushPacket(packet);
	}
}

void Player::render( HDC hdc ) {
	componentRender( hdc );
}

void Player::createProjectile(Vec2 dir ) {
	auto playerPos = getObjPos( );
	playerPos.y -= getObjScale( ).y / 2.f;

	Projectile* projectile = new Projectile{ };
	projectile->setObjName( L"Player_Projectile" );
	projectile->setObjPos( playerPos );
	projectile->setObjScale( Vec2{ 30.f, 30.f } );
	projectile->setDirection( Vec2( 0.f, 1.f ) );

	createObject( GROUP_TYPE::PLAYER_PROJECTILE, projectile );
};

void Player::onCollision( Object* other ) {
}

void Player::onCollisionEntry( Object* other ) {
	getCollider( )->addCollisionCount( );
}

void Player::onCollisionExit( Object* other ) {
	getCollider( )->subCollisionCount( );
}

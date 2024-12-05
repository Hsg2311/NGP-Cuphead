#include "Player.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "ResourceHandler.hpp"
#include "Projectile.hpp"
#include "func.hpp"
#include "SendingStorage.hpp"

char buf[512];

Player::Player( ) {
	createCollider( );
	getCollider( )->setScale( Vec2{ 100.f, 100.f } );

	auto tex = ResourceHandler::getInst( ).loadTexture( L"Player_Texture", L"/texture/idle/cuphead_idle.png" );
	createAnimator( );
	getAnimator( )->createAnimation( L"Player_Idle", tex, Vec2{ 0.f, 0.f },
									Vec2{ 100.f, 155.f }, Vec2{ 100.f, 0.f }, 0.065f, 9 );
	getAnimator( )->play( L"Player_Idle" );
}

Player::~Player( ) {}

void Player::update( ) {
	Vec2 objPos = getObjPos( );

	InputPacket p;
	if ( KEY_HOLD( InputData::LEFT ) ) {
		//objPos.x -= 200.f * fDT;

		p.dir = 1;
		p.type = ClientPacketType::Input;
		//bool inputFlag = true;
		//sendInput(p);
	}
	if ( KEY_HOLD( InputData::RIGHT ) ) {
		//objPos.x += 200.f * fDT;

		p.dir = 2;
		p.type = ClientPacketType::Input;
	}
	if ( KEY_HOLD( InputData::UP) ) {
		//objPos.y -= 200.f * fDT;

		p.dir = 3;
		p.type = ClientPacketType::Input;
	}
	if ( KEY_HOLD( InputData::DOWN) ) {
		//objPos.y += 200.f * fDT;

		p.dir = 4;
		p.type = ClientPacketType::Input;
	}
	if ( KEY_TAP( InputData::Z ) ) {
<<<<<<< HEAD
		createProjectile( );
=======
		CreateProjectile( );
		
		p.attack = 1;
		p.type = ClientPacketType::Input;
>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52
	}

	memset(buf, 0, sizeof(buf));
	memcpy(buf, &p, sizeof(InputPacket));

	setObjPos( objPos );
}

void Player::render( HDC hdc ) {
	componentRender( hdc );
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

void Player::onCollision( Object* other ) {
}

void Player::onCollisionEntry( Object* other ) {
	getCollider( )->addCollisionCount( );
}

void Player::onCollisionExit( Object* other ) {
	getCollider( )->subCollisionCount( );
}

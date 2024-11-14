#include "Monster.hpp"
#include "Timer.hpp"
#include "func.hpp"
#include <cmath>

Monster::Monster( )
	: centerPos_{ Vec2{ 0.f, 0.f } }
	, speed_{ 100.f }
	, maxDistance_{ 100.f }
	, dir_{ 1 }
	, hp_{ 5 }
{
	CreateCollider( );
	getCollider( )->setScale( Vec2{ 40.f, 40.f } );
}

Monster::~Monster( )
{}

void Monster::update( ) {
	auto objPos = getObjPos( );

	objPos.x += speed_ * fDT * dir_;
	auto moveDist = abs( centerPos_.x - objPos.x ) - maxDistance_;

	if ( moveDist > 0.f ) {
		dir_ *= -1;
		objPos.x += moveDist * dir_;
	}

	setObjPos( objPos );
}

void Monster::render( HDC hdc ) {
	Object::render( hdc );
}

void Monster::OnCollision( Object* other )
{
}

void Monster::OnCollisionEntry( Object* other )
{
	getCollider( )->addCollisionCount( );

	if ( other->getObjName( ) == L"Player_Projectile" ) {
		--hp_;

		if ( hp_ <= 0 ) {
			DestroyObject( this );
		}
	}
}

void Monster::OnCollisionExit( Object* other )
{
	getCollider( )->subCollisionCount( );
}

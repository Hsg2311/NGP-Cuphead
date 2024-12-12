#include "Bullet.hpp"

#include "ResourceHandler.hpp"

Bullet::Bullet(Vec2 charPos, Direction dir)
{
	createAnimator();
	auto bullet = ResourceHandler::getInst().loadTexture(L"bullet", L"/texture/smilescene/bullet/bullet.png");

	getAnimator()->createAnimation(L"bullet", bullet, Vec2{ 0.f, 0.f }, Vec2{ 119.f, 28.f }, Vec2{30.f, 0.f }, 0.07f, 48);
	getCollider()->setScale(Vec2{ 50.f, 50.f });

}

Bullet::~Bullet()
{
}

void Bullet::update()
{
}

void Bullet::render(HDC hdc)
{
}

void Bullet::onCollision(Object* other)
{
}

void Bullet::onCollisionEntry(Object* other)
{
}

void Bullet::onCollisionExit(Object* other)
{
}

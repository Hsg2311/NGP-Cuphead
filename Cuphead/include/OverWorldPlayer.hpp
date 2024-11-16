#ifndef __OVERWORLDPLAYER_HPP
#define __OVERWORLDPLAYER_HPP

#include "Object.hpp"
#include <Windows.h>

class Texture;

class OverWorldPlayer : public Object {
public:
	OverWorldPlayer();
	virtual ~OverWorldPlayer();

	virtual void update() override;
	virtual void render(HDC hdc) override;


	virtual void OnCollision(Object* other) override;
	virtual void OnCollisionEntry(Object* other) override;
	virtual void OnCollisionExit(Object* other) override;

	virtual OverWorldPlayer* clone() override { return new OverWorldPlayer{ *this }; }

	
};

#endif // __OVERWORLDPLAYER_HPP
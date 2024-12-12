#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include "Object.hpp"
#include "WinUT.hpp"

class Texture;

class Player : public Object {
public:
	Player(const std::vector<texInfo>& info);
	virtual ~Player( );

	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

	void createProjectile( );

	virtual void onCollision( Object* other ) override;
	virtual void onCollisionEntry( Object* other ) override;
	virtual void onCollisionExit( Object* other ) override;

	virtual Player* clone( ) override { return new Player{ *this }; }


	void setInputEnabled(bool inputEnabled) { inputEnabled_ = inputEnabled; }

private:
	std::vector<Texture*> textures_;
	bool inputEnabled_;
};

#endif // __PLAYER_HPP
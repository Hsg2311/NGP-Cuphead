#ifndef OVERWORLD_PLAYER_HPP
#define OVERWORLD_PLAYER_HPP

#include "Object.hpp"
#include "Texture.hpp"

class OverworldPlayer : public Object {
public:
	OverworldPlayer( const std::vector<texInfo>& info );
	virtual ~OverworldPlayer( ) {}

	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

	virtual void onCollision( Object* other ) override;
	virtual void onCollisionEntry( Object* other ) override;
	virtual void onCollisionExit( Object* other ) override;

	virtual OverworldPlayer* clone( ) override { 
		return new OverworldPlayer( *this );
	}

	void setInputEnabled( bool inputEnabled ) { inputEnabled_ = inputEnabled; }

private:
	std::vector<Texture*> textures_;
	bool inputEnabled_;
};

#endif // OVERWORLD_PLAYER_HPP
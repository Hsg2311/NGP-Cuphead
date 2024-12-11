#ifndef TITLESCENE_HPP
#define TITLESCENE_HPP

#include "Scene.hpp"

class TitleScene : public Scene {
public:
	TitleScene( ) {}
	virtual ~TitleScene( ) {}

	virtual void update( ) override;
	virtual void entry( ) override;
	virtual void exit( ) override;

	virtual void handlePacket( const Packet& packet ) override {}
};

#endif // TITLESCENE_HPP
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "define.hpp"
#include "struct.hpp"
#include "Core.hpp"

class Object;

class Camera {
	SINGLETON( Camera );

public:
	void init( ) { lookAt_ = Vec2( Core::getInst( ).getResolution( ) ) / 2.f; }
	void update( );
	void calDiff( );
	
	void setLookAt( const Vec2& lookAt ) { lookAt_ = lookAt; }
	void setTarget( Object* target ) { target_ = target; }
	Vec2 getRenderPos( const Vec2& pos ) { return pos - diff_; }

private:
	Vec2 lookAt_;
	Object* target_;
	Vec2 diff_;
};

#endif // CAMERA_HPP
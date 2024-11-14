#ifndef __TIMER_HPP
#define __TIMER_HPP

#include "define.hpp"

class Timer {
	SINGLETON( Timer );

public:
	void init( );
	void update( );
	void render( );

	float getFDT( ) const { return static_cast<float>( deltaTime_ ); }
	double getDT( ) const { return deltaTime_; }

private:
	LARGE_INTEGER prevCount_;
	LARGE_INTEGER currCount_;
	LARGE_INTEGER frequency_;

	double deltaTime_;
	double accTime_;
	int fps_;
};

#endif // __TIMER_HPP
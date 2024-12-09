#include "Timer.hpp"
#include <iostream>

Timer::Timer( )
	: prevCount_{ }, currCount_{ }, frequency_{ }
	, deltaTime_{ 0. }, accTime_{ 0. }, fps_{ 0 } {}

Timer::~Timer( ) {}

void Timer::init( ) {
	QueryPerformanceCounter( &prevCount_ );
	QueryPerformanceFrequency( &frequency_ );
}

void Timer::update( ) {
	QueryPerformanceCounter( &currCount_ );

	deltaTime_ = static_cast<double>( currCount_.QuadPart - prevCount_.QuadPart ) 
				/ static_cast<double>( frequency_.QuadPart );

	prevCount_ = currCount_;

//#ifdef _DEBUG
//	if( deltaTime_ > ( 1. / 60. ) )
//		deltaTime_ = ( 1. / 60. );
//#endif
}
/**
 * timer.cpp
 * 
 * Author   :   Fatih Erol
 * Date     :   15.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "timer.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

Timer::Timer()
{
    start();
}

void Timer::start()
{
	GETTIME(_time);
}

float Timer::getSeconds() const
{
	TIMETYPE now;
    GETTIME(now);
    
#ifdef WIN32
	ULARGE_INTEGER timeInteger, nowInteger, diffInteger;
	timeInteger.HighPart = _time.dwHighDateTime;
	timeInteger.LowPart = _time.dwLowDateTime;
	nowInteger.HighPart = now.dwHighDateTime;
	nowInteger.LowPart = now.dwLowDateTime;
	// Calculate difference in 100 nanoseconds' multiple
	diffInteger.QuadPart = nowInteger.QuadPart - timeInteger.QuadPart;

	// One second has 10000000 times 100 nanoseconds
	static const float hundredNanosPerSecond = 10000000.0f;
	return ( diffInteger.QuadPart*1.0f/hundredNanosPerSecond );
#else
	return ( ( now.tv_sec - _time.tv_sec ) + ( now.tv_usec - _time.tv_usec )/1000000.0f );
#endif
}

GRAPHICSLAB_NAMESPACE_END


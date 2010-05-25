/**
 * timer.hpp
 * 
 * Author   :   Fatih Erol
 * Date     :   15.03.2010
 *
 * All rights reserved.
 */


#ifndef GRAPHICSLAB_TIMER_HPP
#define GRAPHICSLAB_TIMER_HPP

// Includes
#include "defs.hpp"

#ifdef WIN32

#include <windows.h>
#define TIMETYPE FILETIME
#define GETTIME(a) GetSystemTimeAsFileTime(&a)

#else

#include <sys/time.h>
#define TIMETYPE timeval
#define GETTIME(a) gettimeofday(&a, NULL )

#endif

GRAPHICSLAB_NAMESPACE_BEGIN


/** Class to keep a timer */
class Timer
{
public:
    /** Constructor */
    Timer();
    
	/** Restart the timer */
    void start();

	/** 
	 * Get seconds from the last restart of the timer.
	 * 
	 * @return		Seconds from last restart
	 */
    float getSeconds() const;

private:
	/** Internal time data structure */
    TIMETYPE _time;
    
}; // class Timer

GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_TIMER_HPP



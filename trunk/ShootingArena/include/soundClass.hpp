/**
 * soundClass.hpp
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


//#include "/home/rahul/cg-finalproject/freealut-1.1.0/include/AL/alut.h"
#include <AL/alut.h>
#include <AL/alc.h>
#include <AL/al.h>

#define NUM_BUFFERS 5
#define NUM_SOURCES 5


#define START		0
#define CRASH	    1
#define BANG	    2
#define BOOM	    3
#define BELT	    4

#ifndef SOUNDCLASS_HPP
#define SOUNDCLASS_HPP

class SoundClass
{
public:
	SoundClass();
	~SoundClass();

	void playSound(int x);
	void playSound2(int x, int y);
    void stopSound(int x);
    
	void setSourcePosition(float x, float y, float z);
	void setListenerPosition(float x, float y, float z);
	void setListenerOrientation(float x, float y, float z, float a, float b, float c);
	void pause();

	void deleteData();

	ALuint buff[NUM_BUFFERS];
    ALuint srcc[NUM_SOURCES];

};


#endif  // SOUNDCLASS_HPP




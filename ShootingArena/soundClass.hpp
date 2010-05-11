/**
 * soundClass.hpp
 * Modified form a previous project
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


#include <AL/alure.h>


#define NUM_BUFFERS 6
#define NUM_SOURCES 6


#define START		0
#define CRASH	    1
#define BANG	    2
#define BOOM	    3

#ifndef SOUNDCLASS_HPP
#define SOUNDCLASS_HPP

class SoundClass
{
public:
	SoundClass();
	~SoundClass();

	void playSound(int x);
	void playSound2(int x, int y);

	void setSourcePosition(float x, float y, float z);
	void setListenerPosition(float x, float y, float z);
	void setListenerOrientation(float x, float y, float z, float a, float b, float c);
	void pause();

	void deleteData();

	ALuint buff[NUM_BUFFERS];
    ALuint srcc[NUM_SOURCES];

};


#endif  // SOUNDCLASS_HPP





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


#include <AL/alut.h>
#include <AL/alc.h>
#include <AL/al.h>

#define NUM_STAGE_BUFFERS 3
#define NUM_STAGE_SOURCES 3

#define START		0
#define WALK	    1
#define BOOM	    2

#ifndef STAGESOUNDCLASS_HPP_
#define STAGESOUNDCLASS_HPP_

class StageSoundClass
{
public:
	StageSoundClass();
	~StageSoundClass();

	void playSound(int x);
	void playSound2(int x, int y);
    void stopSound(int x);

	void setSourcePosition(float x, float y, float z);
	void setListenerPosition(float x, float y, float z);
	void setListenerOrientation(float x, float y, float z, float a, float b, float c);
	void pause();

	void deleteData();

	ALuint buff[NUM_STAGE_BUFFERS];
    ALuint srcc[NUM_STAGE_SOURCES];
    
    ALfloat sourcePosition1[];
    ALfloat sourceVelocity1[];

    ALfloat sourcePositionSTART[];
    ALfloat listenerPosition[];
    ALfloat listenerOrientation[];
};

#endif






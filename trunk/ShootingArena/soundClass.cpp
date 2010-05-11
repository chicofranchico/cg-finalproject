/**
 * soundClass.cpp
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */


#include "soundClass.hpp"
#include <iostream>

ALfloat sourcePosition1[] = { -1.0f, 0.0f, -4.0f};
ALfloat sourceVelocity1[] = { 0.0f, 0.0f, 0.0f };

ALfloat sourcePositionSTART[] = { 0.0f, 0.0f, 0.0f};
ALfloat listenerPosition[] = { 0.0f, 0.0f, 0.0f};
ALfloat listenerOrientation[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };



SoundClass::SoundClass()
{
    if (!alutInit (NULL, NULL))
    {
      ALenum error = alutGetError ();
      fprintf (stderr, "%s\n", alutGetErrorString (error));
      exit (EXIT_FAILURE);
    }
    
    if(alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Failed to create OpenAL source!\n");
        alutExit ();
    }

    alGenSources(NUM_SOURCES, srcc);

    buff[START] = alutCreateBufferFromFile("ambient.wav");
    buff[BOOM] = alutCreateBufferFromFile("a.wav");
    buff[CRASH] = alutCreateBufferFromFile("weap.wav");
    buff[BANG] = alutCreateBufferFromFile("shot2.wav");

    alListenerfv(AL_POSITION, listenerPosition);

    alSourcei ( srcc[START], AL_BUFFER, buff[START] );
    alSourcef ( srcc[START], AL_PITCH, 1.0f );
    alSourcef ( srcc[START], AL_GAIN, 1.0f );
    alSourcefv( srcc[START], AL_POSITION, listenerPosition );
    alSourcefv( srcc[START], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[START], AL_LOOPING, AL_TRUE );

    alSourcei ( srcc[CRASH], AL_BUFFER, buff[CRASH] );
    alSourcef ( srcc[CRASH], AL_PITCH, 1.0f );
    alSourcef ( srcc[CRASH], AL_GAIN, 1.7f );
    alSourcefv( srcc[CRASH], AL_POSITION, listenerPosition );
    alSourcefv( srcc[CRASH], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[CRASH], AL_LOOPING, AL_FALSE );

    alSourcei ( srcc[BANG], AL_BUFFER, buff[BANG] );
    alSourcef ( srcc[BANG], AL_PITCH, 2.5f );
    alSourcef ( srcc[BANG], AL_GAIN, 0.3f );
    alSourcefv( srcc[BANG], AL_POSITION, listenerPosition );
    alSourcefv( srcc[BANG], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[BANG], AL_LOOPING, AL_FALSE );

    alSourcei ( srcc[BOOM], AL_BUFFER, buff[BOOM] );
    alSourcef ( srcc[BOOM], AL_PITCH, 1.0f );
    alSourcef ( srcc[BOOM], AL_GAIN, 1.0f );
    alSourcefv( srcc[BOOM], AL_POSITION, listenerPosition );
    alSourcefv( srcc[BOOM], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[BOOM], AL_LOOPING, AL_FALSE );

    if(alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Failed to create OpenAL source!\n");
        alutExit ();
    }

 //   alSourcePlay(srcc[START]);
}

SoundClass::~SoundClass()
{
   deleteData();
}
void SoundClass::playSound(int x)
{
		alSourcePlay(srcc[x]);
}
void SoundClass::playSound2(int x, int y)
{
		alSourcePlay(srcc[x]);
		alSourceStop(srcc[y]);
}

void SoundClass::pause()
{
   alSourcePause(srcc[START]);
   alSourcePause(srcc[BOOM]);
   alSourcePause(srcc[BANG]);
   alSourcePause(srcc[CRASH]);
}

void SoundClass::setSourcePosition(float x, float y, float z)
{
	sourcePosition1[0] = x;
	sourcePosition1[1] = y;
	sourcePosition1[2] = z;

	alSourcefv( srcc[CRASH], AL_POSITION, sourcePosition1 );
	alSourcefv( srcc[BOOM], AL_POSITION, sourcePosition1 );
}

void SoundClass::setListenerPosition(float x, float y, float z)
{
	listenerPosition[0] = x;
	listenerPosition[1] = y;
	listenerPosition[2] = z;

	alSourcefv( srcc[START], AL_POSITION, listenerPosition );
	alSourcefv( srcc[BOOM], AL_POSITION, listenerPosition );
	alSourcefv( srcc[BANG], AL_POSITION, listenerPosition );

	alListenerfv(AL_POSITION, listenerPosition);
}

void SoundClass::setListenerOrientation(float x, float y, float z, float a, float b, float c)
{
	listenerOrientation[0] = x;
	listenerOrientation[1] = y;
	listenerOrientation[2] = z;

	listenerOrientation[3] = a;
	listenerOrientation[4] = b;
	listenerOrientation[5] = c;

	alListenerfv(AL_ORIENTATION, listenerOrientation);
}

void SoundClass::deleteData()
{
	std::cout << "deleting sound stuff..." << std::endl;
	alSourceStop(srcc[START]);
	alSourceStop(srcc[BOOM]);
	alSourceStop(srcc[BANG]);
	alSourceStop(srcc[CRASH]);

	alDeleteSources(NUM_SOURCES, srcc);
    alDeleteBuffers(NUM_BUFFERS, buff);


    alutExit ();

}

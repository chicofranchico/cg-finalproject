/**
 * soundClass.cpp
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */


#include "soundClass.hpp"
#include <iostream>

ALfloat sourcePosition1[] = { -1.0f, 0.0f, -4.0f};
ALfloat sourceVelocity1[] = { 0.0f, 0.0f, 0.0f };

ALfloat sourcePositionSTART[] = { 0.0f, 0.0f, -100.0f};
ALfloat listenerPosition[] = { 0.0f, 0.0f, 0.0f};
ALfloat listenerOrientation[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };



SoundClass::SoundClass()
{
    ALenum error;
    if (!alutInit (NULL, NULL))
    {
      error = alutGetError ();
      fprintf (stderr, "%s\n", alutGetErrorString (error));
      exit (EXIT_FAILURE);
    }
    
    ALCcontext *context;
    ALCdevice *device;
    const ALCchar *default_device;
    default_device = alcGetString(NULL,ALC_DEFAULT_DEVICE_SPECIFIER);
    printf("using default device: %s\n", default_device);

    if(alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Failed to create OpenAL source!\n");
        alutExit ();
    }

    alGenSources(NUM_SOURCES, srcc);

    buff[START] = alutCreateBufferFromFile("eveningForest.wav");
    if (buff[START] == AL_NONE)
    {
      error = alutGetError ();
      fprintf (stderr, "Error loading file: '%s'\n",
               alutGetErrorString (error));
      alutExit ();
      exit (EXIT_FAILURE);
    }    
    
    buff[BOOM] = alutCreateBufferFromFile("boom.wav");
    if (buff[BOOM] == AL_NONE)
    {
      error = alutGetError ();
      fprintf (stderr, "Error loading file: '%s'\n",
               alutGetErrorString (error));
      alutExit ();
      exit (EXIT_FAILURE);
    }    

/*
    buff[CRASH] = alutCreateBufferFromFile("weap.wav");
    if (buff[CRASH] == AL_NONE)
    {
      error = alutGetError ();
      fprintf (stderr, "Error loading file: '%s'\n",
               alutGetErrorString (error));
      alutExit ();
      exit (EXIT_FAILURE);
    }    
*/
    buff[BANG] = alutCreateBufferFromFile("bang.wav");
    if (buff[BANG] == AL_NONE)
    {
      error = alutGetError ();
      fprintf (stderr, "Error loading file: '%s'\n",
               alutGetErrorString (error));
      alutExit ();
      exit (EXIT_FAILURE);
    }    

    buff[BELT] = alutCreateBufferFromFile("movingTarget.wav");
    if (buff[BELT] == AL_NONE)
    {
      error = alutGetError ();
      fprintf (stderr, "Error loading file: '%s'\n",
               alutGetErrorString (error));
      alutExit ();
      exit (EXIT_FAILURE);
    }    

    alListenerfv(AL_POSITION, listenerPosition);

    alSourcei ( srcc[START], AL_BUFFER, buff[START] );
    
    alSourcef ( srcc[START], AL_PITCH, 1.0f );
    alSourcef ( srcc[START], AL_GAIN, 0.3f );
    alSourcefv( srcc[START], AL_POSITION,  sourcePositionSTART );
//    alSourcefv( srcc[START], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[START], AL_LOOPING, AL_TRUE );

    alSourcei ( srcc[CRASH], AL_BUFFER, buff[CRASH] );
/*    alSourcef ( srcc[CRASH], AL_PITCH, 1.0f );
    alSourcef ( srcc[CRASH], AL_GAIN, 1.7f );
    alSourcefv( srcc[CRASH], AL_POSITION, listenerPosition );
    alSourcefv( srcc[CRASH], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[CRASH], AL_LOOPING, AL_FALSE );
*/
    alSourcei ( srcc[BANG], AL_BUFFER, buff[BANG] );
    alSourcef ( srcc[BANG], AL_PITCH, 2.5f );
    alSourcef ( srcc[BANG], AL_GAIN, 0.3f );
    alSourcefv( srcc[BANG], AL_POSITION, listenerPosition );
//    alSourcefv( srcc[BANG], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[BANG], AL_LOOPING, AL_FALSE );

    alSourcei ( srcc[BOOM], AL_BUFFER, buff[BOOM] );
    alSourcef ( srcc[BOOM], AL_PITCH, 1.0f );
    alSourcef ( srcc[BOOM], AL_GAIN, 5.0f );
    alSourcefv( srcc[BOOM], AL_POSITION, listenerPosition );
//    alSourcefv( srcc[BOOM], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[BOOM], AL_LOOPING, AL_FALSE );

    alSourcei ( srcc[BELT], AL_BUFFER, buff[BELT] );
    alSourcef ( srcc[BELT], AL_PITCH, 1.0f );
    alSourcef ( srcc[BELT], AL_GAIN, 1.0f );
    alSourcefv( srcc[BELT], AL_POSITION, listenerPosition );
//    alSourcefv( srcc[BOOM], AL_VELOCITY, sourceVelocity1 );
    alSourcei ( srcc[BELT], AL_LOOPING, AL_TRUE );

    if(alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Failed to create OpenAL source!\n");
        alutExit ();
    }

    alSourcePlay(srcc[START]);
}

SoundClass::~SoundClass()
{
   deleteData();
}
void SoundClass::stopSound(int x)
{
    alSourceStop(srcc[x]);
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
    alSourceStop(srcc[BELT]);
    
	alDeleteSources(NUM_SOURCES, srcc);
    alDeleteBuffers(NUM_BUFFERS, buff);


    alutExit ();

}

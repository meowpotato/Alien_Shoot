// Pedro 
// open al
#include <iostream>
#include <stdio.h>
#include <GL/glx.h>
#include <stdlib.h>
#include </usr/include/AL/alut.h>

ALuint alSource[10];
ALuint alBuffer[10];

void initSound();
void emptyDriver();
void loadSounds();
void playSound(int sndSet);

using namespace std;

int main()
{
    initSound();
    cout << "init sound\n";

    emptyDriver();
    cout << "empty driver\n";

    loadSounds();
    cout << "load\n";

    playSound(1);
    cout << "sound set\n";

    return 0;
}

void initSound()
{
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("error in initilization\n");
    }
    alGetError();

    float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

}

void loadSounds()
{
    alBuffer[6] = alutCreateBufferFromFile("sound.wav");
    alGenSources(1, &alSource[6]);
    alSourcei(alSource[6], AL_BUFFER, alBuffer[6]);

}


void emptyDriver()
{
    alDeleteSources(1, &alSource[0]);
    alDeleteSources(1, &alSource[1]);
    alDeleteSources(1, &alSource[2]);

    alDeleteBuffers(1, &alBuffer[0]);
    alDeleteBuffers(1, &alBuffer[1]);
    alDeleteBuffers(1, &alBuffer[2]);

    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);

    alcCloseDevice(Device);
}


void playSound(int sndSet)
{
    alSourcef(alSource[sndSet], AL_GAIN, 1.0f);
    alSourcef(alSource[sndSet], AL_PITCH, 1.0f);
    alSourcei(alSource[sndSet], AL_LOOPING, AL_TRUE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }

    alSourcePlay(alSource[sndSet]);
}

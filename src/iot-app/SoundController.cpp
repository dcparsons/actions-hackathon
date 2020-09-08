#include "SoundController.h"
#include "AudioClassV2.h"
#include "Arduino.h"

// Declare an instance of the AudioClass
AudioClass &Audio = AudioClass::getInstance();

// The size of the buffer used to play samples
const int BUFFER_SIZE = 32000 * 3 + 45;

//The size, in bytes, of our sound files
const int FAILURE_SOUND_SIZE = 87072;
const int SUCCESS_SOUND_SIZE = 121532;

// Our audio buffer
char *audioBuffer;

//Success Sound Data
static unsigned char successSoundData[SUCCESS_SOUND_SIZE] = {
#include "success-sound.h"
};

//Failure Sound Data
static unsigned char failureSoundData[FAILURE_SOUND_SIZE] = {
#include "failure-sound.h"
};

void SetupAudioBuffer()
{
    audioBuffer = (char *)malloc(BUFFER_SIZE + 1);
    memset(audioBuffer, 0x0, BUFFER_SIZE);
}

void PlaySuccessSound(){
    // Copy the sound sample into the audioBuffer
    memcpy(audioBuffer, successSoundData, SUCCESS_SOUND_SIZE);
    // Set the audio file properties
    Audio.format(8000, 16);
    Audio.setVolume(45);
    // Start playing
    Audio.startPlay(audioBuffer, SUCCESS_SOUND_SIZE);
    // Wait until the playing stops
    while (Audio.getAudioState() == AUDIO_STATE_PLAYING)
    {
        delay(10);
    }
}

void PlayFailureSound(){
    // Copy the sound sample into the audioBuffer
    memcpy(audioBuffer, failureSoundData, FAILURE_SOUND_SIZE);
    // Set the audio file properties
    Audio.format(4000, 16);
    Audio.setVolume(45);
    // Start playing
    Audio.startPlay(audioBuffer, FAILURE_SOUND_SIZE);
    // Wait until the playing stops
    while (Audio.getAudioState() == AUDIO_STATE_PLAYING)
    {
        delay(10);
    }
}
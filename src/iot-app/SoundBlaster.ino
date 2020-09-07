#include "AudioClassV2.h"
#include "OledDisplay.h"

// Declare an instance of the AudioClass
AudioClass& Audio = AudioClass::getInstance();
// The size of the buffer used to play samples
const int BUFFER_SIZE = 32000 * 3 + 45;
// The size of the sound file, in bytes
// You'll need to get this yourself from  your sound sample properties
const int SOUND_SIZE = 87072;
const int SUCCESS_SOUND_SIZE = 121532;
int lastButtonAState;
int buttonAState;

int lastButtonBState;
int buttonBState;

char *audioBuffer;

static unsigned char successSoundData[SUCCESS_SOUND_SIZE] = {
 #include "./sound/success-sound.h"
};

static unsigned char soundData[SOUND_SIZE] = {
 #include "./sound/failure-sound.h"
} ;



void playSuccessSound()
{
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

void playFailureSound()
{
 // Copy the sound sample into the audioBuffer
 memcpy(audioBuffer, soundData, SOUND_SIZE);
 // Set the audio file properties
 Audio.format(4000, 16);
 Audio.setVolume(45);
 // Start playing
 Audio.startPlay(audioBuffer, SOUND_SIZE);
 // Wait until the playing stops
 while (Audio.getAudioState() == AUDIO_STATE_PLAYING)
 {
  delay(10);
 }
}

/*
* sketch methods
*/
void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
 Serial.begin(115200);

 // initialize the button pin as a input
 pinMode(USER_BUTTON_A, INPUT);

 lastButtonAState = digitalRead(USER_BUTTON_A);

 pinMode(USER_BUTTON_B, INPUT);
 lastButtonBState = digitalRead(USER_BUTTON_B);

 // Setup your local audio buffer
 audioBuffer = (char *)malloc(BUFFER_SIZE + 1);
 memset(audioBuffer, 0x0, BUFFER_SIZE);
}

void loop()
{
 // Check the state of button A, and if pressed
 // call the playSound() function.
  buttonAState = digitalRead(USER_BUTTON_A);
  buttonBState = digitalRead(USER_BUTTON_B);

 if (buttonAState == LOW && lastButtonAState == HIGH)
 {
    Screen.clean();
    Screen.print(0, "Play Success Sound!");
    playSuccessSound();
 }

  if (buttonBState == LOW && lastButtonBState == HIGH)
  {
    Screen.clean();
    Screen.print(0, "Play Failure Sound!");
    playFailureSound();
  }

  lastButtonAState = buttonAState;
  lastButtonBState = buttonBState;
}
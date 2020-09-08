#include "Arduino.h"
#include "OledDisplay.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"
#include "AudioClassV2.h"

#include "Wifi.h"

static bool hasWifi = false;

int lastButtonAState;
int buttonAState;

int lastButtonBState;
int buttonBState;

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

/*
* sketch methods
*/
void setup()
{
  Screen.init();
  Screen.print(0, "CI Sound");
  Screen.print(2, "Initializing...");

  pinMode(LED_BUILTIN, OUTPUT);

  Screen.print(3, " > Serial");
  Serial.begin(115200);

  Screen.print(3, " > WiFi");

  hasWifi = InitializeWifi();

  // initialize the button pin as a input
  pinMode(USER_BUTTON_A, INPUT);

  lastButtonAState = digitalRead(USER_BUTTON_A);

  pinMode(USER_BUTTON_B, INPUT);
  lastButtonBState = digitalRead(USER_BUTTON_B);

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

  if (buttonBState == LOW && lastButtonBState == HIGH)
  {
    Screen.clean();
    Screen.print(0, "Play Failure Sound!");
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

  lastButtonAState = buttonAState;
  lastButtonBState = buttonBState;
}
#include "Arduino.h"
#include "OledDisplay.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"

#include "Wifi.h"
#include "SoundController.h"
#include "MQTT.h"

static bool hasWifi = false;
static bool soundPlaying = false;

int lastButtonAState;
int buttonAState;

int lastButtonBState;
int buttonBState;

void setup()
{
  Screen.init();
  Screen.print(0, "Noisy Build");
  Screen.print(2, "Initializing...");

  pinMode(LED_BUILTIN, OUTPUT);

  Screen.print(3, " > Serial");
  Serial.begin(115200);

  Screen.print(3, " > WiFi");

  hasWifi = InitializeWifi();

  SetupAudioBuffer();

  DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "NoisyBuild");
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetMessageCallback(ProcessMessage);

  pinMode(USER_BUTTON_A, INPUT);

  lastButtonAState = digitalRead(USER_BUTTON_A);

  pinMode(USER_BUTTON_B, INPUT);
  lastButtonBState = digitalRead(USER_BUTTON_B);

}

void loop()
{
  // This code exists simply to test the sounds. 
  /*
  buttonAState = digitalRead(USER_BUTTON_A);
  buttonBState = digitalRead(USER_BUTTON_B);

  if (buttonAState == LOW && lastButtonAState == HIGH)
  {
    Screen.clean();
    Screen.print(0, "Play Success Sound!");

    PlaySuccessSound();
  }

  if (buttonBState == LOW && lastButtonBState == HIGH)
  {
    Screen.clean();
    Screen.print(0, "Play Failure Sound!");
    PlayFailureSound();
  }

  lastButtonAState = buttonAState;
  lastButtonBState = buttonBState;
  */

  if(hasWifi){
    DevKitMQTTClient_Check();
  }

  while(soundPlaying){
    delay(10);
  }

  delay(1000);
}

void ProcessMessage(const char* payLoad, int size){
  soundPlaying = true;

  if(strcmp(payLoad, "success") == 0){
      PlaySuccessSound();
      Screen.print(1, payLoad, true);
    }
  else if(strcmp(payLoad, "failure") == 0){
      PlayFailureSound();
      Screen.print(1, payLoad, true);
    }
  soundPlaying = false;
}
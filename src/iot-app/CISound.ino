#include "Arduino.h"
#include "OledDisplay.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"

#include "Wifi.h"
#include "SoundController.h"
#include "MQTT.h"

static bool hasWifi = false;

int lastButtonAState;
int buttonAState;

int lastButtonBState;
int buttonBState;

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

  SetupAudioBuffer();

  ConfigureMQTTClient();

  // initialize the button pin as a input
  pinMode(USER_BUTTON_A, INPUT);

  lastButtonAState = digitalRead(USER_BUTTON_A);

  pinMode(USER_BUTTON_B, INPUT);
  lastButtonBState = digitalRead(USER_BUTTON_B);

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
}
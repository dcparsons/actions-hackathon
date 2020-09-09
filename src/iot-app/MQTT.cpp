#include "MQTT.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"
#include "parson.h"
#include "utility.h"

static bool messageSending = true;
static int interval = 5000;

void ConfigureMQTTClient(){
  DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "NoisyBuild");
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetMessageCallback(HubMessageCallback);
}

void HubMessageCallback(const char* payLoad, int size){
    Screen.print(1, payLoad, true);
}


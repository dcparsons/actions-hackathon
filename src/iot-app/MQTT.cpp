#include "MQTT.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"

void ConfigureMQTTClient(){
  DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "CISound");
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetMessageCallback(HubMessageCallback);
}

void HubMessageCallback(const char* payLoad, int size){
    Screen.print(1, payLoad, true);
}
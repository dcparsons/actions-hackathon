#include "MQTT.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"


void ConfigureMQTTClient(MESSAGE_CALLBACK message_callback){
  DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "NoisyBuild");
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetMessageCallback(message_callback);
}



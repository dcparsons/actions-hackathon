#ifndef MQTT_H
#define MQTT_H
#include "DevKitMQTTClient.h"
#include "Arduino.h"

void ConfigureMQTTClient(MESSAGE_CALLBACK message_callback);

#endif
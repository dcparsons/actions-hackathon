#ifndef MQTT_H
#define MQTT_H

#include "Arduino.h"

void ConfigureMQTTClient(void);
void HubMessageCallback(const char* payLoad, int size);


#endif
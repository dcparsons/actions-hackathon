#include "AZ3166WiFi.h"
#include "OledDisplay.h"
#include "Wifi.h"
#include "Arduino.h"

bool InitializeWifi()
{
  bool _hasWifi = false;

  Screen.print(2, "Connecting...");
  
  if (WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Screen.print(1, ip.get_address());
    _hasWifi = true;
    Screen.print(2, "Running... \r\n");
  }
  else
  {
    _hasWifi = false;
    Screen.print(1, "No Wi-Fi\r\n ");
  }
  return _hasWifi;
}
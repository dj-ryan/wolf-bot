#include <Arduino.h>

#include "WiFi.h"
#include "HTTPClient.h"

#include "bfcm_communication.h"
#include "wifi_handler.h"

const char *ssid = "Wolf2.4";
const char *password = "WolfTime!";
const char *basePath = "https://csce.unl.edu/socbattlebot/";
BfcmConnector connector = BfcmConnector(basePath, 0);

void setup()
{

  Serial.begin(115200);

  connectNUIoT();
  connector.initialize();
}

void loop()
{

  if (WiFi.status() == WL_CONNECTED)
  {
    connector.shoot();
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }
  Serial.println(WiFi.macAddress());

  delay(10000);
}
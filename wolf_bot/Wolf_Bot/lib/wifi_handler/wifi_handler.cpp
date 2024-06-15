
#include "wifi_handler.h"


void wifiConnect(char *ssid, char *password) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to the WiFi network");
}

void connectNUIoT() {
    Serial.println(WiFi.macAddress());
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
    char *ssid = "NU-IoT";
    std::map<String, char*> passwordMap = {
        {"94:B5:55:C7:0B:2C", "tggfntwx"},
        {"94:B5:55:C7:05:E8", "vpxdxtnp"}
    };

    wifiConnect(ssid, passwordMap[WiFi.macAddress()]);
}
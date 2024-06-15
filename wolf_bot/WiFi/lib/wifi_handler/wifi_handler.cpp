
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
    // uint8_t newMACAddress[] = {0x94, 0xB5, 0x55, 0xC7, 0x0B, 0x2C};
    // esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
    // Setting the Mac Address of the ESP 32
    Serial.println(WiFi.macAddress());
    char *ssid = "NU-IoT";
    std::map<String, char*> passwordMap = {
        {"94:B5:55:C7:0B:2C", "tggfntwx"},
        {"94:B5:55:C7:05:E8", "vpxdxtnp"}
    };

    wifiConnect(ssid, passwordMap[WiFi.macAddress()]);
}
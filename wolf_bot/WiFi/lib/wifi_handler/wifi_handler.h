#ifndef NUIOT_H
#define NUIOT_H

#include <Arduino.h>
#include <map>

#include "esp_wifi.h"
#include "Wifi.h"

using namespace std;

/**
 * @brief Connects the board to the wifi network with the given credentials
 * 
 * @param ssid 
 *  The SSID of the wifi network
 * @param password 
 *  The password of the wifi network
 */
void wifiConnect(char *ssid, char *password);

/**
 * @brief Connects the board to NU IoT based off of the credentials that match
 * up with the mac address of the board.
 * 
 */
void connectNUIoT();

#endif
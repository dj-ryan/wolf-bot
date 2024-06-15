#include <Arduino.h>

#include "WiFi.h"
#include "HTTPClient.h"

#include "wifi_handler.h"
#include "bfcm_communication.h"

#include <IRremote.h> // >v4.0.0

#define PIN_RECV 2

BfcmConnector connector = BfcmConnector("https://csce.unl.edu/socbattlebot/", 0);
//BfcmConnector connector = BfcmConnector("http://192.168.1.150:80/", 0);

void setup() {
    Serial.begin(115200);

    //IrSender.begin(DEFAULT_TX_PIN); // Initializes IR sender

    connectNUIoT();
    //wifiConnect("Samsung Galaxy 520 5G 6934", "StreamNet");

    //wifiConnect("Wolf2.4", "WolfTime!");

    connector.initialize();

    //WiFi.begin(ssid, password);

//    while (WiFi.status() != WL_CONNECTED) {
//        delay(1000);
//        Serial.println("Connecting to WiFi..");
//    }

    //Serial.println("Connected to the WiFi network");


    Serial.begin(115200);       // initialize serial connection to print on the Serial Monitor of the Arduino IDE
    IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
    //IrReceiver.blink13(true);   // enable blinking of the built-in LED when an IR signal is received
}

void loop() {

    if (IrReceiver.decode()) {
        // uint8_t *data;
        //Serial.println("Received something...");

        IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data

        //connector.shoot();

        // connector got hit code
        //Serial.print("command: ");
        //Serial.println(~IrReceiver.decodedIRData.command, HEX);
        Serial.print("Command: ");
        Serial.println(~IrReceiver.decodedIRData.command & 0x000000ff, HEX);
        Serial.print("Address: ");
        Serial.println(~IrReceiver.decodedIRData.address & 0x000000ff);
        if ((~IrReceiver.decodedIRData.address & 0x000000ff) == 0xab) {

            // reed stuff
            Serial.println("There was a hit.");
            connector.hit(~IrReceiver.decodedIRData.command & 0x000000ff);



        }


        // IRData *data = IrReceiver.read(); // Returns a pointer to the IRData struct
        // Serial.print("From arr - Addr: "); // Prints the address
        // Serial.print(data->address, HEX); // Prints the address
        // Serial.print(" | Cmd: "); // Prints the command
        // Serial.println(data->command, HEX); // Prints the command

        IrReceiver.resume(); // Important, enables to receive the next IR signal

    }
}
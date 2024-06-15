#include "bfcm_communication.h"


BfcmConnector::BfcmConnector(
    String baseURL, int gameID
) {
    this->baseURL = baseURL;
    this->gameID = gameID;
}


String BfcmConnector::putRequest(String endpoint) {
    HTTPClient http;
    String url = this->baseURL + endpoint;
    http.begin(url);
    http.addHeader("Content-Type", "text/plain");
    int responseCode = http.PUT("PUT sent from ESP32");
    if (responseCode > 0) {
        return http.getString();
    } else {
        return "";
    }
}


void BfcmConnector::initialize() {
    int robotID = this->joinGame();
    if (robotID == -1) {
        this->createGame();
        this->joinGame();
    }
    this->robotID = robotID;
}


int BfcmConnector::createGame() {
    String endpoint = "game/create";
    String response = this->putRequest(endpoint);
    if (response.equals("")) {
        return -1;
    } else {
        return response.toInt();
    }
}


int BfcmConnector::joinGame() {
    String endpoint = "join/";
    endpoint += this->gameID;
    String response = this->putRequest(endpoint);
    if (response.equals("")) {
        return -1;
    } else {
        return response.toInt();
    }
}

void BfcmConnector::shoot() {
    String endpoint = "shoot/";
    endpoint += this->gameID;
    endpoint += "?attacker_id=";
    endpoint += this->robotID;
    String response = this->putRequest(endpoint);
}


int BfcmConnector::hit(int attackerID) {
    Serial.println("Hit by robot with ID: ");
    Serial.println(attackerID);
    String endpoint = "hit/";
    endpoint += this->gameID;
    endpoint += "?attacker_id=";
    endpoint += attackerID;
    endpoint += "&defender_id=";
    endpoint += this->robotID;
    String response = this->putRequest(endpoint);
    Serial.println("Successfully sent hit request");
    if (response.equals("")) {
        return 0;
    } else {
        return response.toInt();
    }
}
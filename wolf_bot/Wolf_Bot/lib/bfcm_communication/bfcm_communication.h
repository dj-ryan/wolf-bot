#ifndef BFCM_H
#define BFCM_H

#include <Arduino.h>

#include "WiFi.h"
#include "HTTPClient.h"

using namespace std;

/**
 * @brief This acts as a way to communicate with the BFCM from the point of
 * view of a robot.
 * 
 */
class BfcmConnector {
    
    private:
        String baseURL;
        int gameID;
        /**
         * @brief Sends a put request to the requested endpoint and returns
         * the response on a valid request, or an empty string on an invalid
         * request.
         * 
         * @param endpoint 
         *  The endpoint that the request should bounce against.
         *  NOTE: The endpoint should be formatted "endpoint/"
         * @return String: 
         *  The response from the server.
         */
        String putRequest(String endpoint);
        /**
         * @brief Connects the robot to the game specified.
         * 
         * @return int:
         *  The identification number for the robot. 
         */
        int joinGame();

        /**
         * @brief Creates a new instances of a game in the API.
         * NOTE: This should only be called when there are no games in the API
         * currently.
         * 
         * @return int 
         *  The identification number for the game.
         */
        int createGame();
    public:
        int robotID;
        // Constructors
        /**
         * @brief Construct a new Bfcm Connector
         * 
         * @param baseURL:
         *  The base URL of the API
         * @param gameID:
         *  The game that the robot will be joining
         */
        BfcmConnector(String baseURL, int gameID);

        /**
         * @brief Causes the robot to join the specified game and updates
         * all information about the game.
         * 
         */
        void initialize();

        // API call functions
        /**
         * @brief sends a message to the server to inform it that this robot
         * was hit by a second robot.
         * 
         * @param attackerID 
         *  The ID of the robot that shot this robot.
         * @return int:
         *  1 if the robot received a valid hit, otherwise returns 0. 
         */
        int hit(int attackerID);
        /**
         * @brief Sends a shot to the BFCM to add to accuracy.
         * 
         */
        void shoot();
};

#endif
#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// Define the port you're listening on
#define PORT 12345

struct Landmark {
    float x, y, value; // Assuming 'value' might be an orientation or confidence score
};

class OscHandler {
public:
    void setup();
    void update();

    // Getters for the landmarks
    const std::vector<Landmark>& getLandmarks() const;


private:
    ofxOscReceiver receiver;
    float x,y; // Variables to store the current coordinates
    std::vector<Landmark> landmarks; // Vector to store landmarks

    void handleLandmarksMessage(const ofxOscMessage& m);
};


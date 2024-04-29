#include "OscHandler.h"

void OscHandler::setup() {
    receiver.setup(PORT);
}

void OscHandler::update() {
    ofxOscMessage m;
    while (receiver.hasWaitingMessages()) {
        receiver.getNextMessage(&m);

        if (m.getAddress() == "/landmarks") {
            handleLandmarksMessage(m);
        }
    }
}


const std::vector<Landmark>& OscHandler::getLandmarks() const
{
    // TODO: insert return statement here
    return landmarks;
}

void OscHandler::handleLandmarksMessage(const ofxOscMessage& m) {
    landmarks.clear(); // Clear previous landmarks
    for (int i = 0; i < m.getNumArgs(); i += 3) { // Assuming every landmark has 3 values
        Landmark landmark = {
            m.getArgAsFloat(i),   // x
            m.getArgAsFloat(i + 1), // y
            m.getArgAsFloat(i + 2)  // value
        };
        landmarks.push_back(landmark);
    }
}

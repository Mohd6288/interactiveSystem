#include "ofApp.h"

float calculateDistance(const glm::vec2& point1, const glm::vec2& point2) {
    return glm::distance(point1, point2);
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(100);
    ofBackground(0);
    oscHandler.setup();

	// Set default value for the flag to draw lines between particles
		bDrawLines = true;
    //load sound sample
        sound1.load("music.mp3");

	// Setup GUI parameters
	gui.setup();
	
	gui.add(trail.setup("#Trail", 6, 0, 20));
	gui.add(sizeDot.setup("Dot Size", 1, 1, 20));

	// Create color picker
	gui.add(redCol.setup("Red Color", 100, 1, 255));
	gui.add(greenCol.setup("Green Color", 150, 1, 255));
	gui.add(blueCol.setup("Blue Color", 190, 1, 255));

    //a variable used to manage the state of the program
    currentKey = '1';

	

	// Set font and size for the text
	font.load("myFont.ttf", 12);
    // Explanatory text
	explanationText = "";
}

void ofApp::update() {

    auto landmarks = oscHandler.getLandmarks(); // Get the landmarks once to avoid multiple calls
    if (landmarks.size() > 20) { // Ensure there are enough landmarks
        // Define the fingers using their landmark positions
        const auto& plamBase = glm::vec2(landmarks[0].x, landmarks[0].y);
        const auto& thumb = glm::vec2(landmarks[4].x, landmarks[4].y);
        const auto& index = glm::vec2(landmarks[8].x, landmarks[8].y);
        const auto& middle = glm::vec2(landmarks[12].x, landmarks[12].y);
        const auto& ring = glm::vec2(landmarks[16].x, landmarks[16].y);
        const auto& pinky = glm::vec2(landmarks[20].x, landmarks[20].y);

        // Draw circles for each finger

        ofDrawCircle(plamBase, 15);
        ofDrawCircle(thumb, 5);
        ofDrawCircle(index, 5);
        ofDrawCircle(middle, 5);
        ofDrawCircle(ring, 5);
        ofDrawCircle(pinky, 5);

    ParticleSys.update(plamBase.x, plamBase.y - 100, currentKey, redCol, greenCol, blueCol, sizeDot);

    }
    else {
    ParticleSys.update(mouseX, mouseY, currentKey, redCol, greenCol, blueCol, sizeDot);

    }
    oscHandler.update();
 
    

    ofSetBackgroundAuto(bDrawLines);
}





//--------------------------------------------------------------
void ofApp::draw() {
    frameCount++;
    std::cout << frameCount << std::endl;
	ofSetColor(255);

    if (frameCount > 0 && frameCount <= 5) {
        sound1.play();
    }

    
    //Drawing Interface at a certain time in the demonstration
   
        ParticleSys.draw();//draw the Particle system
        ofSetHexColor(0xf00ff); // Set color for GUI controls

        auto landmarks = oscHandler.getLandmarks(); // Get the landmarks once to avoid multiple calls
        if (landmarks.size() > 20) { // Ensure there are enough landmarks
            // Define the fingers using their landmark positions
            const auto& plamBase = glm::vec2(-landmarks[0].x, landmarks[0].y);
            const auto& thumb = glm::vec2(landmarks[4].x, landmarks[4].y);
            const auto& index = glm::vec2(landmarks[8].x, landmarks[8].y);
            const auto& middle = glm::vec2(landmarks[12].x, landmarks[12].y);
            const auto& ring = glm::vec2(landmarks[16].x, landmarks[16].y);
            const auto& pinky = glm::vec2(landmarks[20].x, landmarks[20].y);

            // Draw lines to connect the palm base with each finger
            ofDrawLine(palmBase, thumb);
            ofDrawLine(palmBase, index);
            ofDrawLine(palmBase, middle);
            ofDrawLine(palmBase, ring);
            ofDrawLine(palmBase, pinky);

            // Optionally, draw lines between fingers to mimic the webbing or connections
            //ofDrawLine(thumb, index);
            //ofDrawLine(index, middle);
            //ofDrawLine(middle, ring);
            //ofDrawLine(ring, pinky);

            // Draw the palm base
            ofDrawCircle(palmBase, 15);

            // Draw circles for each finger to represent the tips
            ofDrawCircle(thumb, 5);
            ofDrawCircle(index, 5);
            ofDrawCircle(middle, 5);
            ofDrawCircle(ring, 5);
            ofDrawCircle(pinky, 5);

            // Threshold for deciding if the distance is "close"
            float closeDistance = 150; // Adjust this value as needed

            // Function to draw lines if fingers are close to the thumb
            auto drawLineIfClose = [&](const glm::vec2& finger) {
                if (calculateDistance(thumb, finger) < closeDistance) {
                    
                    ofDrawLine(thumb, finger);
                    //bDrawLines = !bDrawLines;

                }
                
                };

            // Check each finger against the thumb
            drawLineIfClose(index);
            drawLineIfClose(middle);
            drawLineIfClose(ring);
            drawLineIfClose(pinky);
        }
        gui.draw();
        //Draw background rectangle
        ofSetColor(0);
        ofDrawRectangle(ofGetWidth() / 2, 0, font.stringWidth(explanationText) + 20, font.stringHeight(explanationText) + 20);
        ofSetColor(255,100);
        font.drawString(explanationText, ofGetWidth() / 2, 20);
 }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    ParticleSys.addParticle(x, y);//add Particles to our system
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    currentKey = key;//read the classes to figure out what key affects behaviour
	if (key == 'l') {
	bDrawLines = !bDrawLines;
    }
    if (key == ' ') {
        frameCount = 3150;
        sound1.stop();
    }
}

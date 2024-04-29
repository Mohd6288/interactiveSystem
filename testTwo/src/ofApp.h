#pragma once
#include "ofMain.h"
#include "ParticleSystem.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "OscHandler.h"

using namespace glm;
#define PORT 12345

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;
	void mouseDragged(int x, int y, int button) override;
	void keyPressed(int key) override;
	ParticleSystem ParticleSys{ 100 };


	char currentKey;

	//color picker
	ofxFloatSlider blueCol;
	ofxFloatSlider redCol;
	ofxFloatSlider greenCol;

	ofxFloatSlider sizeDot;
	ofxFloatSlider trail;
	int frameCount = 0;      //This framecount gives the timer for my slide show
	ofSoundPlayer sound1;    //sound sample
private:

	ofxPanel gui;
	bool bDrawLines;

	// Explanatory text
	ofTrueTypeFont font;
	string explanationText;
	
	//osc
	OscHandler oscHandler; // Instance of OscHandler
	// Declare variables for finger positions and palm base
	std::vector<Landmark> landmarks;
	float closeDistance;
	glm::vec2 palmBase;
	glm::vec2 thumb;
	glm::vec2 index;
	glm::vec2 middle;
	glm::vec2 ring;
	glm::vec2 pinky;
};


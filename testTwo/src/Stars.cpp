#include "Stars.h"

Stars::Stars(vec2 _location, vec2 _velocity, float _radius, ofColor _color, float _speedLimit, float _speed)
	:Particle(_location, _velocity, _radius, _color, _speedLimit, _speed)
{
	cout << "Constructed a Stars" << endl;

}

//--------------------------------------------------------------
void Stars::draw() {

	ofSetColor(color);
    drawStar(location.x, location.y);

	//DrawLine(location.x,location.y,location.x-radius*15,location.y-radius *15);
	
}

//--------------------------------------------------------------
void Stars::update(float msX, float msY, char key, float r, float g, float b, float size) {

    float mappedRed = ofMap(location.x, 0, ofGetWidth(), 0, r);
    float mappedGreen = ofMap(location.y, 0, ofGetHeight(), 0, g);
    float mappedBlue = ofMap(location.x + location.y, 0, ofGetWidth() + ofGetHeight(), 0, b);

	//update change the movement behaviourv.
    if (key == '1') {
        stickTop();
        color = ofColor(mappedRed, mappedGreen, mappedBlue, 155);
    }
    else if (key == '2') {
        simplePhysics();
        color = ofColor(mappedRed, mappedGreen, mappedBlue, 155);
    
    }
    else {
        color = ofColor(r, g, b, 255);
    }
	//moveAway(msX, msY);
    move();
    bounce();
}

void Stars::drawStar(float x, float y)
{
    int numPoints = 5;
    float radiusOuter = 10;
    float radiusInner = 15;

    float angleIncrement = 360.0 / (numPoints * 2);

    // Draw lines connecting points on the circle to form a star
    for (int i = 0; i < numPoints * 2; ++i) {
        float angle = ofDegToRad(i * angleIncrement);
        float x1 = x + cos(angle) * ((i % 2 == 0) ? radiusOuter : radiusInner);
        float y1 = y + sin(angle) * ((i % 2 == 0) ? radiusOuter : radiusInner);

        float angleNext = ofDegToRad((i + 1) * angleIncrement);
        float x2 = x + cos(angleNext) * ((i % 2 == 0) ? radiusOuter : radiusInner);
        float y2 = y + sin(angleNext) * ((i % 2 == 0) ? radiusOuter : radiusInner);

        ofDrawLine(x1, y1, x2, y2);
    }
}

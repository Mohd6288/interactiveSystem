#include "Particle.h"

//-------------------------------------------------------
Particle::Particle(vec2 _location, vec2 _velocity, float _radius, ofColor _color, float _speedLimit, float _speed)
{
    cout << "Constructed an Particle" << endl;

    location = _location;
    velocity = _velocity;
    radius = _radius;
    color = _color;
    speed = _speed;
    speedLimit = _speedLimit;
    gravity = vec2(0, 0.1);
    friction = vec2(0, 0);
}

void Particle::setup()
{
    color = ofColor(100, 150, 130, 1);
    location.x = ofRandomWidth();
    location.y = ofRandomHeight();
    velocity.x = ofRandom(-1, 1);
    velocity.y = ofRandom(-1, 1);
    t = ofRandom(35,-35);
}

//--------------------------------------------------------------
//make sure all your custom graphics are drawn within the diameter of the circle by using radius variable/data member
void Particle::draw() {
    ofSetColor(color);
    ofDrawCircle(location, radius);
}

// Update our Particle by calling various methods
void Particle::update(float msX, float msY, char key, float r, float g, float b, float size) {

    radius = size;
    t += 0.5;

    if (msX > 0 && msX < ofGetWidth() && msY > 0 && msY < ofGetHeight()) {
        // Map the x and y coordinates of the particle to the color channels
        float mappedRed = ofMap(location.x, 0, ofGetWidth(), 0, r);
        float mappedGreen = ofMap(location.y, 0, ofGetHeight(), 0, g);
        float mappedBlue = ofMap(location.x + location.y, 0, ofGetWidth() + ofGetHeight(), 0, b);

        if (key == '1') {
            // Set color based on the mapped values for an orange-like color
            color = ofColor(mappedRed, mappedGreen, mappedBlue, 255);
            moveAway(msX, msY);
        }
        else if (key == '2') {
            // Set color based on the mapped values for a purple-like color
            color = ofColor(mappedRed, mappedGreen, mappedBlue, 255);
            moveToPoint(msX, msY);
        }
        else {
            // If neither '1' nor '2' is pressed, set color based on the mapped values
            color = ofColor(r, g, b, 255);
        }
    }

    simplePhysics();
    move();
    //waveMovement();
    bounce();
   // spiralMovement(t);
}




//--------------------------------------------------------------
//draw our "collision" sphere
void Particle::drawDebugSphere() {
    ofPushStyle();
    ofSetLineWidth(1);
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofDrawCircle(location, radius);
    ofPopStyle();
}

//--------------------------------------------------------------
//move toward the repel X and Y point
void Particle::moveAway(float repelX, float repelY) {

    vec2 repel = vec2(repelX, repelY);
    vec2 direction = location - repel; // vector subtraction, the order matters!

    float directionMag = length(direction);
    //we have to make sure direction magnitude isn't 0 before normalizing
    if (directionMag > 0) {
        direction = normalize(direction);
    }

    if (directionMag < 200) {
        velocity += direction * speed;
    }

}

//--------------------------------------------------------------
//move toward the attract X and Y point
void Particle::moveToPoint(float attractX, float attractY) {

    vec2 attractor = vec2(attractX, attractY);
    vec2 direction = attractor - location; // vector subtraction, the order matters!

    float directionMag = length(direction);
    //we have to make sure direction magnitude isn't 0 before normalizing
    if (directionMag > 0) {
        direction = normalize(direction);
    }

    velocity += direction * speed;

}

//--------------------------------------------------------------
//apply forces to our Particle
void Particle::simplePhysics() {
    friction = velocity * -1; //reverse of velocity
    //we have to make sure velocity magnitude isn't 0 before normalizing
    if (length(velocity) > 0) {
        friction = normalize(friction);
    }
    friction *= 0.01;//make it a really small factor

    velocity += friction;
    velocity += gravity;
}

void Particle::stickTop() {
    friction = velocity * -1; //reverse of velocity
    //we have to make sure velocity magnitude isn't 0 before normalizing
    if (length(velocity) > 0) {
        friction = normalize(friction);
    }
    friction *= 0.01;//make it a really small factor

    velocity -= friction;
    velocity -= gravity;
}

//--------------------------------------------------------------
//move our Particle by adding velocity to location
void Particle::move() {

    if (length(velocity) > speedLimit) {
        velocity = normalize(velocity) * speedLimit;
    }

    location += velocity;
}

//--------------------------------------------------------------
//reverse direction/velocity when Particle gets to an edge
void Particle::bounce() {

    if (location.x < radius) {
        location.x = radius;
        velocity.x *= -1;
    }
    if (location.x > ofGetWidth() - radius) {
        location.x = ofGetWidth() - radius;
        velocity.x *= -1;
    }
    if (location.y < radius) {
        location.y = radius;
        velocity.y *= -1;
    }
    if (location.y > ofGetHeight() - radius) {
        location.y = ofGetHeight() - radius;
        velocity.y *= -1;
    }

}


void Particle::spiralMovement(float t) {
    const float a = 0.15f; // Adjustment factor
    const float scaleFactor = 200.0f; // Determines the spiral's size

    float newX = scaleFactor * cos(t) * cos(atan(a * t));
    float newY = -scaleFactor * sin(atan(a * t)); // Adapted for 2D display

    // Update the particle's location
    location.x = newX + ofGetWidth() / 2; // Centering the spiral on the screen
    location.y = newY + ofGetHeight() / 2;
}


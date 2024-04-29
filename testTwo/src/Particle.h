#pragma once
#include "ofMain.h"

using namespace glm;

class Particle {

    //public means things that can be used (or are visible to use) outside of the class
public:
    Particle(vec2 _location, vec2 _velocity, float _radius, ofColor _color, float _speedLimit, float _speed);

    void setup();

    void drawDebugSphere();
    virtual void draw();
    virtual void update(float msX, float msY, char key,float r,float g,float b,float size);

    //protected means anything beneath can only be used inside the class or in child classes
protected:
    float t;
    //protected functions you should call from update inside the class / children classes
    void moveAway(float repelX, float repelY);
    void moveToPoint(float attractX, float attractY);
    void bounce();
    void spiralMovement(float t);
    void waveMovement();
    void simplePhysics();
    void stickTop();
    void move();

    //member variables
    vec2 location;
    vec2 velocity;
    vec2 gravity;
    vec2 friction;

    float radius;
    ofColor color;
    float speedLimit;
    float speed;

    //private means anything beneath can only be used inside the class
private:

};

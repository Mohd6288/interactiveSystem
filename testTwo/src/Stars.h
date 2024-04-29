#pragma once
#include "ofMain.h"
#include "Particle.h"

using namespace glm;

//The definition of the constructor Stars::Stars has some extra syntax to tell it to also call the Agent constructor,
//  passing it the same arguments.So when you create a Stars, the constructor of Agent will be called, then the constructor of Stars.
class Stars : public Particle {

    //public means things below before private
    //can be used (or are visible to use) outside of the class
public:
    Stars(vec2 _location, vec2 _velocity, float _radius, ofColor _color, float _speedLimit, float _speed);

    void draw() override;
    void update(float msX, float msY, char key, float r, float g, float b, float size);

    //private means anything beneath can only be used inside the class
private:

    void drawStar(float x, float y);


};


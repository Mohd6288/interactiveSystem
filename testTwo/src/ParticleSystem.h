#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Stars.h"


using namespace glm;

class ParticleSystem {

public:
	ParticleSystem(int _numOfParticles);

	void update(float msX, float msY, char key,float r,float g,float b,float size);
	void draw();
	void addParticle(int x, int y);
	~ParticleSystem();

private:
	vector<Particle*> Particles;
	int numOfParticles;
};



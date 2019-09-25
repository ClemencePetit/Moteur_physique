#ifndef BUOYANCY_FORCE_GENERATOR
#define BUOYANCY_FORCE_GENERATOR

#include "ParticleForceGenerator.h"

class BuoyancyForceGenerator: public ParticleForceGenerator
{
private:

	float s_ = 2.f;
	// if r = 2.f
	float v_ = 33.51f;
	float zWater_ = 0.f;
	float density_ = 1000.f;
	Vector3D g_;

public:

	BuoyancyForceGenerator(Vector3D g);
	~BuoyancyForceGenerator();

	void updateForce(Particle* p, float t);
};

#endif
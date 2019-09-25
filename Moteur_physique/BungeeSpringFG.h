#ifndef PARTICLE_BUNGEE_SPRING
#define PARTICLE_BUNGEE_SPRING

#include "ParticleForceGenerator.h"
class BungeeSpringFG :
	public ParticleForceGenerator
{

private:
	Particle* other_;
	float k_; //elasticity
	float l0_; //distance between particles at rest

public:

	//constructors
	BungeeSpringFG(Particle* other, float k, float l0) :
		other_(other), k_(k), l0_(l0) {};

	void updateForce(Particle* p, float t);
};

#endif


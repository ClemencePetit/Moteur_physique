
#ifndef PARTICLE_ANCHORED_SPRING
#define PARTICLE_ANCHORED_SPRING

#include "ParticleForceGenerator.h"
class ParticleAnchoredSpring :
	public ParticleForceGenerator
{
private:
	Vector3D anchor_;
	float k_; //elasticity
	float l0_; //distance between particles at rest

public:

	//constructors
	ParticleAnchoredSpring(Vector3D anchor, float k, float l0) :
		anchor_(anchor), k_(k), l0_(l0) {};

	void updateForce(Particle* p, float t);

};


#endif


#ifndef WEAK_SPRING_FORCE_GENERATOR
#define WEAK_SPRING_FORCE_GENERATOR

#include "ParticleForceGenerator.h"

class WeakSpringFG : public ParticleForceGenerator
{
private:
	Vector3D anchor_;
	float k_; //elasticity
	float d_; //dampings
public:
	WeakSpringFG(Vector3D anchor, float k, float d);
	~WeakSpringFG();

	void updateForce(Particle* p, float t);
};

#endif
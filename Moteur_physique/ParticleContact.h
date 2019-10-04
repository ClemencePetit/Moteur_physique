#ifndef PARTICLE_CONTACT
#define PARTICLE_CONTACT

#include "Particle.h"

class ParticleContact
{
private:
	Particle* particles_[2];
	float restit_;
	float dPene_;
	Vector3D n_; //Dans le sens particles_[0] -> particles_[1]

public:
	ParticleContact(Particle* pa1, Particle* pa2, float restit, float dPene, Vector3D n);
	~ParticleContact();

	void resolve(float t);
	float calculVs();
	void resolveVelocity(float t);
	void resolveInterpenetration();

};

#endif
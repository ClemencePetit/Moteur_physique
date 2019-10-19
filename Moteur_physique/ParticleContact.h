#ifndef PARTICLE_CONTACT
#define PARTICLE_CONTACT

#include "Particle.h"
#include "Shape.h"

class ParticleContact
{
private:
	Particle* particles_[2];
	float restit_;
	float dPene_;
	float vs_;

	Vector3D n_; //Dans le sens particles_[0] -> particles_[1]

public:

	ParticleContact(Particle* pa1, Particle* pa2, float restit, float dPene, Vector3D n);
	~ParticleContact();

	float getVs() {
		return vs_;
	}

	void resolve(float t);
	float calculVs();
	void resolveVelocity();
	void resolveInterpenetration();

	static ParticleContact* getContact(Particle* pa, Particle* pb);

	static ParticleContact* getContact(Sphere sphere1, Sphere sphere2);
	static ParticleContact* getContact(Rect3D rect1, Rect3D rect2);
	static ParticleContact* getContact(Sphere sphere, Rect3D rect);
	static ParticleContact* getContact(Rect3D rect, Sphere sphere);


};

#endif
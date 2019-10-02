#ifndef PARTICLE_FACTORY
#define PARTICLE_FACTORY


#include "IParticle.h"
#include "Particle.h"

class ParticleFactory
{
public:

	static IParticle* getBasicBall();
	static IParticle* getCannonBall();
	static IParticle* getLaser();
	static IParticle* getSnowflake();
	static IParticle* getDefaultCrosshair();


};

#endif


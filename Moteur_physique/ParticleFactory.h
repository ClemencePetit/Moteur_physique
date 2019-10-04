#ifndef PARTICLE_FACTORY
#define PARTICLE_FACTORY


#include "IParticle.h"
#include "Particle.h"


#include "DragFG.h"
#include "GravityFG.h"
#include "SpringFG.h"
#include "BuoyancyFG.h"
#include "AnchoredSpringFG.h"
#include "BungeeSpringFG.h"
#include "WeakSpringFG.h"


class ParticleFactory
{
private:
	int currentProjectileIndex_;

public:

	ParticleFactory() : currentProjectileIndex_(0) {}

	IParticle* getCurrentProjectile();

	IParticle* nextProjectile() {
		currentProjectileIndex_++;
		currentProjectileIndex_ %= 7; //nb projectiles
		return getCurrentProjectile();
	}

	static IParticle* getBasicBall();
	static IParticle* getCannonBall();
	static IParticle* getLaser();
	static IParticle* getSnowflake();

	static IParticle* getYoyo();

	static IParticle* getBlob1();
	static IParticle* getBlob2();



};

#endif


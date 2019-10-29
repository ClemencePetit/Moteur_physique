#ifndef PARTICLE_FACTORY
#define PARTICLE_FACTORY


#include "IParticle.h"
#include "Particle.h"
#include "Color.h"


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

	int currentProjectileIndex_ = 0;

public:

	ParticleFactory() :	currentProjectileIndex_(0) {}

	int getCurrentProjectileIndex() { return currentProjectileIndex_; };

	IParticle* getCurrentProjectile();

	IParticle* nextProjectile() {
		currentProjectileIndex_++;
		currentProjectileIndex_ %= 8; //nb projectiles
		return getCurrentProjectile();
	}

	IParticle* getBasicBall();
	IParticle* getCannonBall();
	IParticle* getLaser();
	IParticle* getSnowflake();

	IParticle* getYoyo();

	IParticle* getBlob1();
	IParticle* getBlob2();
	IParticle* getTestWater();

	IParticle* getTestBlop();
	IParticle* getBlob3();


};

#endif


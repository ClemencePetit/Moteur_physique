
#ifndef PHYSIC_SIMULATOR
#define PHYSIC_SIMULATOR

#include "ParticleForceRegister.h"
#include "ContactResolver.h"
#include "ParticleGroup.h"


#include "DragFG.h"
#include "GravityFG.h"
#include "SpringFG.h"
#include "BuoyancyFG.h"
#include "AnchoredSpringFG.h"
#include "BungeeSpringFG.h"
#include "WeakSpringFG.h"

class PhysicSimulator
{

private:


	//Registre des forces
	ParticleForceRegister register_;

	//Collisions
	ContactResolver contactResolver_;

	//Particules à simuler
	list <Particle*> particles_; //liste des particules créées
	list <ParticleGroup*> particlesGroups_;

	//Constantes
	Vector3D g_ = Vector3D(0, 0, -9.8f);
	float k1 = 0.5f;
	float k2 = 1.2f;


	//Updates de la simulation

	int resolveCollisions();

	void applyRegister(float elapsedTime);
	void applyCollisions(float elapsedTime);
	void applyMovements(float elapsedTime);
	void verifyDeletion();

	bool isInPool(Particle* p);

	void drawParticles();
	void drawGroupParticles();

public:


	PhysicSimulator() {};

	~PhysicSimulator() {
		deleteAllParticles();
	}

	void addParticle(IParticle* pa);
	void deleteParticle(Particle* pa);
	void deleteParticleGroup(ParticleGroup* paG);
	void deleteAllParticles();
	void deleteAndClearAll();

	void updatePhysics(float elapsedTime);

	void draw();

	list <Particle*> getParticles() {
		return particles_;
	}

	list <ParticleGroup*> getParticuleGroups() {
		return particlesGroups_;
	}

};


#endif
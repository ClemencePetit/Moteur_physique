#include "ParticleGroup.h"

void ParticleGroup::Draw() {
	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{

		(*it)->Draw();
	}
}

void ParticleGroup::addTo(list<Particle*> list) {

	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		(*it)->addTo(list);
	}
}

void ParticleGroup::addRecurringForce(Particle* pa, ParticleForceGenerator* fg) {

	forcesRegister_.add(pa, fg);
}

void ParticleGroup::addParticle(Particle* pa) {

	particles_.push_back(pa);
}

void ParticleGroup::applyForces(float t) {
	forcesRegister_.updateForces(t);

	//We do not clear the register because we want to re-apply
	//those forces each loop
}



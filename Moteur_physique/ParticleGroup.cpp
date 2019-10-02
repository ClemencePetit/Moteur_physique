#include "ParticleGroup.h"

void ParticleGroup::Draw() {
	std::vector<Particle>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		it->Draw();
	}
}

void ParticleGroup::addTo(list<Particle*> list) {

	std::vector<Particle>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		it->addTo(list);
	}
}

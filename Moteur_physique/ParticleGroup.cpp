#include "ParticleGroup.h"


ParticleGroup::~ParticleGroup() {
	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		delete(*it);
	}

	forcesRegister_.clear();
}

void ParticleGroup::Draw() {

	Particle* centerParticle = *particles_.begin();
	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		if (*it != centerParticle) {
			Shape::drawLine(
				*(*it)->getPos(),
				*centerParticle->getPos());
		}
		(*it)->Draw();
	}
}

void ParticleGroup::updateForces(float t) {
	forcesRegister_.updateForces(t);

	//We do not clear the register because we want to re-apply
	//those forces each loop
}

void ParticleGroup::addRandomOffsets() {


	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		//Skip the first particle
		if (it == particles_.begin()) continue;

		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));

		Vector3D offset(x, y, z);
		Vector3D newPos = *(*it)->getPos() + offset;
		(*it)->setPos(newPos);
	}

	//We do not clear the register because we want to re-apply
	//those forces each loop
}


bool ParticleGroup::hasNullParticle() {
	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		if (*it == NULL) {
			return true;
		}
	}

	return false;
}


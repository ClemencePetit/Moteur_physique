#include "ParticleGroup.h"

void ParticleGroup::Draw() {
	std::vector<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
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


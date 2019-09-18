#pragma once
#include "Particle.h"

//Interface des générateurs de force pour les particules
class ParticleForceGenerator {

	virtual void updateForce(Particle* particle, float t) = 0;
};
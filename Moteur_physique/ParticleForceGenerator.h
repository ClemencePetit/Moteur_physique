#pragma once
#include "Particle.h"

//Interface des g�n�rateurs de force pour les particules
class ParticleForceGenerator {

	virtual void updateForce(Particle* particle, float t) = 0;
};
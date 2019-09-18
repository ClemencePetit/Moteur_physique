#include "ParticleForceRegister.h"

ParticleForceRegister::ParticleForceRegister()
{
}


ParticleForceRegister::~ParticleForceRegister()
{
}

void ParticleForceRegister::add(Particle* p, ParticleForceGenerator* fg) {
	ForceRecord fr;
	fr.fg = fg;
	fr.p = p;
	register_.push_back(fr);
}

void ParticleForceRegister::remove() {
	register_.pop_back();
}

void ParticleForceRegister::clear() {
	register_.clear();
}

void ParticleForceRegister::updateForces(float t) {
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		it->fg->updateForce(it->p, t);
	}
}
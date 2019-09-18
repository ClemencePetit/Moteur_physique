#ifndef PARTICLEFORCEREGISTER_H
#define PARTICLEFORCEREGISTER_H

#include <vector>
#include "Particle.h"
#include "ParticleForceGenerator.h"

struct ForceRecord {
	Particle* p;
	ParticleForceGenerator* fg;
};

class ParticleForceRegister {

private:
	std::vector<ForceRecord> register_;

public:

	void add(Particle* p, ParticleForceGenerator* fg);
	void remove();
	void clear();
	void updateForces(float t);

	ParticleForceRegister();
	~ParticleForceRegister();
};

#endif
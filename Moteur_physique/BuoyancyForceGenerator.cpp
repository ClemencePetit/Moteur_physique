#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(Vector3D g)
{
	g_ = g;
}


BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
}

void BuoyancyForceGenerator::updateForce(Particle* p, float t) {
	if (p->getPos()->z <= zWater_ - s_) {
		p->addForce(g_ * (- v_ * density_));
	}
	else if (p->getPos()->z < zWater_ + s_) {
		float propWater = abs(p->getPos()->z - s_ - zWater_) / (2 * s_);
		p->addForce(g_ * (- v_ * density_) * propWater);
	}
}

#include "GravityForceGenerator.h"


void GravityForceGenerator::updateForce(Particle* p, float t) {

	if (p->getMassInv() > 0) {

		p->addForce(
			gravity_ * (1 / p->getMassInv())
		);

	}
}
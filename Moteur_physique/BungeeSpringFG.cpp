#include "BungeeSpringFG.h"

void ParticleBungeeSpring::updateForce(Particle* p, float t) {

	Vector3D d = *p->getPos() - *other_->getPos();

	//No elasticity if too close.
	if (d.norm() >= l0_) {
		p->addForce(
			d.normalized() * -k_ * (d.norm() - l0_));
	}

}

#include "SpringFG.h"


void SpringFG::updateForce(Particle* p, float t) {

	Vector3D d = *p->getPos() - *other_->getPos();

	p->addForce(
		d.normalized()  * -k_ * (d.norm() - l0_));

}

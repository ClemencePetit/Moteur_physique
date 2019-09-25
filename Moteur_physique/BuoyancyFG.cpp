#include "BuoyancyFG.h"

BuoyancyFG::BuoyancyFG()
{
}


BuoyancyFG::~BuoyancyFG()
{
}

void BuoyancyFG::updateForce(Particle* p, float t) {
	if (p->getPos()->z > (s_ + zWater_))
	{
		cout << "out" << endl;
		return;
	}
	else if (p->getPos()->z <= (zWater_ - s_)) {
		cout << "in" << endl;
		p->addForce(Vector3D(0, 0, v_ * density_));
	}
	else{
		cout << "middle" << endl;
		float propWater = (p->getPos()->z - s_ - zWater_) / (2 * s_);
		p->addForce(Vector3D(0, 0, v_ * density_*propWater));
	}
}
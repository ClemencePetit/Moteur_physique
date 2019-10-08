#include "WeakSpringFG.h"

WeakSpringFG::WeakSpringFG(float k, float d) : k_(k), d_(d)
{
}


WeakSpringFG::~WeakSpringFG()
{
}


void WeakSpringFG::updateForce(Particle* p, float t) {
	float gamma = 0.5f * sqrt(4 * k_ - (d_ * d_));
	//cout << gamma << endl;
	Vector3D c = (p->getPosWS()) * (d_ / (2 * gamma)) + p->getVitWS() * (1 / gamma);
	//p->getPosWS().display();
	//p->getVitWS().display();
	//c.display();
	Vector3D pt = ((p->getPosWS()) * cos(gamma * t) + c * sin(gamma * t))*exp(-0.5*d_*p->getDureeWS());
	//cout << p->getDureeWS() << endl;
	//pt.display();
	Vector3D test = ((pt - (p->getPosWS())) * (1 / (p->getDureeWS()*p->getDureeWS())) - p->getVitWS());
	//test.display();
	p->addForce(test);
}

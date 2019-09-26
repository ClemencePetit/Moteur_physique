#include "Particle.h"

Particle::Particle(Vector3D* pos, Vector3D vit, float m) : pos_(pos), vel_(vit), massInv_(1/m), forceAccum_(0, 0, 0)
{
}

void Particle::integrer(float t)
{
	if (massInv_ >= 0 && t > 0) {
		*pos_ = *pos_ + vel_ * t;//calcul de la nouvelle position
		vel_ = vel_ + forceAccum_ * massInv_ * t;//calcul de la nouvelle velocite
		clearAccum();
	}
	else {
		*pos_ = *pos_ + vel_ * t;
	}
}

Particle::~Particle()
{
	delete(shape_);
}

void Particle::addForce(const Vector3D &force) {
	forceAccum_ = forceAccum_ + force;
}

void Particle::clearAccum() {
	forceAccum_ = Vector3D(0, 0, 0);
}
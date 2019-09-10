#include "Particule.h"

Particle::Particle(float g, Vector3D* pos, Vector3D vit, float m, float d) : g_(0, 0, -g), pos_(pos), vel_(vit), m_(m), massInv_(1/m), d_(d)
{
}

void Particle::integrer(float t)
{
	*pos_ = *pos_ + vel_ * t;
	vel_ = vel_ * pow(d_, t) + g_ * m_ * massInv_ * t;
}

Particle::~Particle()
{
	delete(shape_);
}
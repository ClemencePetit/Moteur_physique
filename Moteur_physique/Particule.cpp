#include "Particule.h"

Particule::Particule(float g, Vecteur3D* pos, Vecteur3D vit, 
	float m, float d, float r, float v, float b) : g_(0, 0, -g), pos_(pos), vit_(vit), massInv_(1./m), d_(d), r_(d), v_(d), b_(d), m_(m)
{
}

void Particule::integrer(float t)
{
	*pos_ = *pos_ + vit_ * t;
	vit_ = vit_ * pow(d_, t) + g_ * t; //m_ * massInv_ ; pas utilisé car simplifié par g
}


Particule::~Particule()
{
	delete(shape_);
}
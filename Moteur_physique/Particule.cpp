#include "Particule.h"

Particule::Particule(float g, Vecteur3D* pos, Vecteur3D vit, float m, float d) : g_(0, 0, -g), pos_(pos), vit_(vit), m_(m), massInv_(1/m), d_(d)
{
}

void Particule::integrer(float t)
{
	*pos_ = *pos_ + vit_ * t;
	vit_ = vit_ * pow(d_, t) + g_ * m_ * massInv_ * t;
}

Particule::~Particule()
{
	delete(shape_);
}
#include "Particule.h"

Particule::Particule(float g, Vecteur3D* pos, Vecteur3D vit, float m, float d) : g_(0, 0, -g), pos_(pos), vel_(vit), m_(m), massInv_(1/m), d_(d)
{
}

void Particule::integrer(float t)
{
	*pos_ = *pos_ + vel_ * t;//calcul de la nouvelle position
	vel_ = vel_ * pow(d_, t) + g_ * m_ * massInv_ * t;//calcul de la nouvelle velocite
}

Particule::~Particule()
{
	delete(shape_);
}
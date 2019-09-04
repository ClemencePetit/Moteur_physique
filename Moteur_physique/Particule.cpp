#include "Particule.h"

Particule::Particule(float g, Vecteur3D pos, Vecteur3D vit, float m, float d, float r, float v, float b) : g_(0, 0, -g), pos_(pos), vit_(vit), massInv_(1/m), d_(d), r_(d), v_(d), b_(d), m_(m)
{
}

void Particule::integrer(float t)
{
	pos_ = pos_.addition(vit_.multScalaire(t));
	vit_ = vit_.multScalaire(pow(d_, t)).addition(g_.multScalaire(m_).multScalaire(massInv_).multScalaire(t));
}


Particule::~Particule()
{
}

#include "Shape.h"

//Dessine les 6 faces du parall�l�pip�de rectangle, centr� sur la position de la particule
void Rect3D::draw() {
	GlutUtils::drawRectangle(*position_, width_, height_, depth_, color_);
}

ParticleContact* Rect3D::collideWith(const Shape& shape) const
{
	shape.collideWithInternal(*this);
}

ParticleContact* Rect3D::collideWithInternal(const Sphere& sphere) const
{
	return ParticleContact::getContact(*this, sphere);
}

ParticleContact* Rect3D::collideWithInternal(const Rect3D& rect) const
{
	return ParticleContact::getContact(*this, rect);
}


//dessine la sph�re centr�e sur la position de la particule
void Sphere::draw() {
	GlutUtils::drawSphere(*position_, radius_, color_);
}

ParticleContact* Sphere::collideWith(const Shape& shape) const
{
	shape.collideWithInternal(*this);
}

ParticleContact* Sphere::collideWithInternal(const Sphere& sphere) const
{
	return ParticleContact::getContact(*this, sphere);
}

ParticleContact* Sphere::collideWithInternal(const Rect3D& rect) const
{
	return ParticleContact::getContact(*this, rect);
}



float Sphere::getRadius() {
	return radius_;
}

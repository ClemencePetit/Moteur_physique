#include "Shape.h"

//Dessine les 6 faces du parall�l�pip�de rectangle, centr� sur la position de la particule
void Rect3D::draw() {
	GlutUtils::drawRectangle(*position_, width_, height_, depth_, color_);
}

Contact Rect3D::collideWith(const Shape& shape) const
{
	shape.collideWithInternal(*this);
}

Contact Rect3D::collideWithInternal(const Sphere& sphere) const
{
	return Contact::getContact(*this, sphere);
}

Contact Rect3D::collideWithInternal(const Rect3D& rect) const
{
	return Contact::getContact(*this, rect);
}


//dessine la sph�re centr�e sur la position de la particule
void Sphere::draw() {
	GlutUtils::drawSphere(*position_, radius_, color_);
}

Contact Sphere::collideWith(const Shape& shape) const
{
	shape.collideWithInternal(*this);
}

Contact Sphere::collideWithInternal(const Sphere& sphere) const
{
	return Contact::getContact(*this, sphere);
}

Contact Sphere::collideWithInternal(const Rect3D& rect) const
{
	return Contact::getContact(*this, rect);
}



float Sphere::getRadius() {
	return radius_;
}

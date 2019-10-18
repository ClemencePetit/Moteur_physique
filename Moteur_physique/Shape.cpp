#include "Shape.h"

//Dessine les 6 faces du parall�l�pip�de rectangle, centr� sur la position de la particule
void Rect3D::draw() {
	GlutUtils::drawRectangle(*position_, width_, height_, depth_, color_);
}

float Rect3D::getRadius() {
	return (width_ + height_ + depth_) / 3;
}

//dessine la sph�re centr�e sur la position de la particule
void Sphere::draw() {
	GlutUtils::drawSphere(*position_, radius_, color_);
}

float Sphere::getRadius() {
	return radius_;
}

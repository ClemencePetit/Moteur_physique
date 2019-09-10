#include "Shape.h"

void Rect3D::Draw() {

	glPushMatrix();

	glColor3f(r_, v_, b_);

	glTranslatef(position_->x, position_->y, position_->z);

	glBegin(GL_QUADS);
	glVertex3f(-width/2, -height/2, depth/2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	//devant
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	//gauche
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//haut
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	//bas
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//droite
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glEnd();
	glPopMatrix();
}

void Sphere::Draw() {

	glPushMatrix();

	glColor3f(r_, v_, b_);

	glTranslatef(position_->x, position_->y, position_->z);

	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, rayon, 20, 20);
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}
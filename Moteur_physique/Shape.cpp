#include "Shape.h"

//Dessine les 6 faces du parall�l�pip�de rectangle, centr� sur la position de la particule
void Rect3D::draw() {

	glPushMatrix();

	glColor3f(r_, v_, b_);

	glTranslatef(position_->x, position_->y, position_->z);

	glBegin(GL_QUADS);
	//derriere
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

//dessine la sph�re centr�e sur la position de la particule
void Sphere::draw() {

	glPushMatrix();

	glColor3f(r_, v_, b_);

	glTranslatef(position_->x, position_->y, position_->z);

	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, rayon, 20, 20);
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}

//Trace une ligne entre a et b.
void Shape::drawLine(Vector3D a, Vector3D b) {

	glPushMatrix();

	glColor3f(1, 0, 0);
	glTranslatef(0, 0, 0);

	glBegin(GL_LINES);

	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glEnd();

	glPopMatrix();
}
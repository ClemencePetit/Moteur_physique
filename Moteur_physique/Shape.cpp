#include "Shape.h"

void Rect3D::Draw() {

	Vecteur3D position = particule_.getPos();
	glPushMatrix();

	glColor3f(1, 0, 0);

	glTranslatef(position.x, position.y, 0);

	glBegin(GL_QUADS);
	glVertex3f(-width/2, -height/2, prof/2);
	glVertex3f(-width / 2, height / 2, prof / 2);
	glVertex3f(width / 2, height / 2, prof / 2);
	glVertex3f(width / 2, -height / 2, prof / 2);
	//devant
	glVertex3f(-width / 2, -height / 2, -prof / 2);
	glVertex3f(-width / 2, height / 2, -prof / 2);
	glVertex3f(width / 2, height / 2, -prof / 2);
	glVertex3f(width / 2, -height / 2, -prof / 2);
	//gauche
	glVertex3f(-width / 2, -height / 2, prof / 2);
	glVertex3f(-width / 2, height / 2, prof / 2);
	glVertex3f(-width / 2, height / 2, -prof / 2);
	glVertex3f(-width / 2, -height / 2, -prof / 2);
	//haut
	glVertex3f(width / 2, height / 2, prof / 2);
	glVertex3f(-width / 2, height / 2, prof / 2);
	glVertex3f(-width / 2, height / 2, -prof / 2);
	glVertex3f(width / 2, height / 2, -prof / 2);
	//bas
	glVertex3f(-width / 2, -height / 2, prof / 2);
	glVertex3f(width / 2, -height / 2, prof / 2);
	glVertex3f(width / 2, -height / 2, -prof / 2);
	glVertex3f(-width / 2, -height / 2, -prof / 2);
	//droite
	glVertex3f(width / 2, height / 2, prof / 2);
	glVertex3f(width / 2, -height / 2, prof / 2);
	glVertex3f(width / 2, -height / 2, -prof / 2);
	glVertex3f(width / 2, height / 2, -prof / 2);
	glEnd();
	glPopMatrix();
}

void Sphere::Draw() {

	Vecteur3D position = particule_.getPos();

	glPushMatrix();

	glColor3f(1, 0, 0);

	glTranslatef(position.x, position.y, 0);

	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, rayon, 20, 20);
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}
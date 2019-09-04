#include "Shape.h"

void Rect::Draw() {

	glPushMatrix();

	glColor3f(1, 0, 0);

	glTranslatef(position.getX(), position.getY(), 0);

	glBegin(GL_QUADS);
	glVertex2f(0, height);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glEnd();
	glPopMatrix();
}
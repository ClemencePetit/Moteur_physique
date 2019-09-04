#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"
class Shape
{
public:
	Vecteur3D position;
	//float rotation;

	virtual void Draw() = 0; //pure virtual function

	//Constructors
	Shape(Vecteur3D pos = Vecteur3D()) : position(pos) { }
};

class Rect : public Shape {
public:
	float width;
	float height;

	void Draw();

	//Constructors
	Rect(Vecteur3D pos = Vecteur3D(), float w = 2, float h = 2) : width(w), height(h), Shape(pos) { }
};


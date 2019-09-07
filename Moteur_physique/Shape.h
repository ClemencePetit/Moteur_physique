#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"

class Shape
{
protected:
	Vecteur3D* position_;

public:
	//float rotation;

	virtual void Draw() = 0; //pure virtual function

	//Constructors
	Shape(Vecteur3D* pos) : position_(pos) { }
};

class Rect3D : public Shape {
public:
	float width;
	float height;
	float prof;

	void Draw();

	//Constructors
	Rect3D(Vecteur3D* pos, float w = 2, float h = 2, float p=2) : width(w), height(h), prof(p), Shape(pos) { }
};

class Sphere : public Shape {
public:
	float rayon;

	void Draw();

	//Constructors
	Sphere(Vecteur3D* pos, float r = 2) : rayon(r), Shape(pos) { }
};


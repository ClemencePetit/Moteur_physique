#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"

class Shape
{

protected:

	Vecteur3D* position_;
	
	//colors
	float r_;
	float v_;
	float b_;

public:

	virtual void Draw() = 0; //pure virtual function

	//Constructors
	Shape(Vecteur3D* pos, float r, float v, float b) : position_(pos), r_(r), v_(v), b_(b) { }
};

class Rect3D : public Shape {

private:

	float width;
	float height;
	float prof;

public:

	void Draw();

	//Constructors
	Rect3D(Vecteur3D* pos, float r = 0, float v = 0, float b = 0, float w = 2, float h = 2, float p = 2) : width(w), height(h), prof(p), Shape(pos, r, v, b) { }
};

class Sphere : public Shape {

private:

	float rayon;

public:
	void Draw();

	//Constructors
	Sphere(Vecteur3D* pos, float r = 0, float v = 0, float b = 0,  float rayon = 2) : rayon(rayon), Shape(pos, r, v, b) { }
};
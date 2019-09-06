#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"
#include "Particule.h"

class Shape
{
public:
	Particule particule_;
	//float rotation;

	virtual void Draw() = 0; //pure virtual function

	//Constructors
	Shape(Particule pa) : particule_(pa) { }
};

class Rect3D : public Shape {
public:
	float width;
	float height;
	float prof;

	void Draw();

	//Constructors
	Rect3D(Particule pa, float w = 2, float h = 2, float p=2) : width(w), height(h), prof(p), Shape(pa) { }
};

class Sphere : public Shape {
public:
	float rayon;

	void Draw();

	//Constructors
	Sphere(Particule pa, float r = 2) : rayon(r), Shape(pa) { }
};


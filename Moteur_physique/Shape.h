#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vector3D.h"

// Classe abstraite gérant l'affichage des particules, deux dérivées pour l'instant : sphère et rectangle 3D
class Shape
{

protected:

	Vector3D* position_;
	
	//colors
	float r_;
	float v_;
	float b_;

public:

	virtual void Draw() = 0; //pure virtual function

	Vector3D getColor() {
		return Vector3D(r_, v_, b_);
	}

	//Constructors
	Shape(Vector3D* pos, float r, float v, float b) : position_(pos), r_(r), v_(v), b_(b) { }


};

class Rect3D : public Shape {

private:

	float width;
	float height;
	float depth;

public:

	void Draw();

	//Constructors
	Rect3D(Vector3D* pos, float r = 0, float v = 0, float b = 0, float w = 2, float h = 2, float p = 2) : width(w), height(h), depth(p), Shape(pos, r, v, b) { }
};

class Sphere : public Shape {

private:

	float rayon;

public:
	void Draw();

	//Constructors
	Sphere(Vector3D* pos, float r = 0, float v = 0, float b = 0,  float rayon = 2) : rayon(rayon), Shape(pos, r, v, b) { }
};

#endif
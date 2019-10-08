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

	//Constructors
	Shape(Vector3D* pos, float r, float v, float b) : position_(pos), r_(r), v_(v), b_(b) { }


	Vector3D getColor() {
		return Vector3D(r_, v_, b_);
	}

	void setColor(float r, float v, float b) {
		r_ = r;
		v_ = v;
		b_ = b;
	}

	virtual float getRadius() = 0; //Used for collision, only really makes sense for spheres

	virtual void draw() = 0; //pure virtual function

	static void drawLine(Vector3D a, Vector3D b);

};

class Rect3D : public Shape {

private:

	float width_;
	float height_;
	float depth_;

public:

	float getRadius();
	void draw();

	//Constructors
	Rect3D(Vector3D* pos, float r = 0, float v = 0, float b = 0, float w = 2, float h = 2, float p = 2) : width_(w), height_(h), depth_(p), Shape(pos, r, v, b) { }
};

class Sphere : public Shape {

private:

	float radius_;

public:

	float getRadius();
	void draw();

	//Constructors
	Sphere(Vector3D* pos, float r = 0, float v = 0, float b = 0,  float radius_ = 2) : radius_(radius_), Shape(pos, r, v, b) { }
};

#endif
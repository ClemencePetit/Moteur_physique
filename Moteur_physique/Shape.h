#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GlutUtils.h"

#include "Vector3D.h"

// Classe abstraite gérant l'affichage des particules, deux dérivées pour l'instant : sphère et rectangle 3D
class Shape
{

protected:

	Vector3D* position_;
	
	Vector3D color_;

public:

	//Constructors
	Shape(Vector3D* pos, Vector3D rgb) : position_(pos), color_(rgb) { }

	Vector3D getColor() {
		return color_;
	}

	void setColor(float r, float g, float b) {
		color_ = Vector3D(r, g, b);
	}

	void setColor(Vector3D rgb) {
		color_ = rgb;
	}

	virtual float getRadius() = 0; //Used for collision, only really makes sense for spheres

	virtual void draw() = 0; //pure virtual function


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
	Rect3D(Vector3D* pos, Vector3D color, float w = 2, float h = 2, float p = 2) : width_(w), height_(h), depth_(p), Shape(pos, color) { }
};

class Sphere : public Shape {

private:

	float radius_;

public:

	float getRadius();
	void draw();

	//Constructors
	Sphere(Vector3D* pos, Vector3D color,  float radius_ = 2) : radius_(radius_), Shape(pos, color) { }
};

#endif
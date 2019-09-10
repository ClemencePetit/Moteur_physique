#ifndef DEF_VECTEUR3D
#define DEF_VECTEUR3D

#include <iostream>

using namespace std;

class Vecteur3D
{
public:
	
	//position
	float x;
	float y;
	float z;

	//constructors
	Vecteur3D();
	Vecteur3D(float x, float y, float z);

	~Vecteur3D();

	//static functions
	static Vecteur3D zero();

	//Operations
	Vecteur3D operator+(const Vecteur3D& b);
	Vecteur3D operator*(const float& lambda);

	Vecteur3D componentMult (Vecteur3D v);

	float dotProd(Vecteur3D v);
	Vecteur3D crossProd(Vecteur3D v);
	float tripleProd(Vecteur3D u, Vecteur3D v);

	float norm();
	Vecteur3D normalized();

	void display();
};

#endif
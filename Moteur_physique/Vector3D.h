#ifndef DEF_VECTEUR3D
#define DEF_VECTEUR3D

#include <iostream>

using namespace std;

class Vector3D
{
public:
	
	//position
	float x;
	float y;
	float z;

	//constructors
	Vector3D();
	Vector3D(float x, float y, float z);

	~Vector3D();

	//static functions
	static Vector3D zero();

	//Operations
	Vector3D operator+(const Vector3D& b);
	Vector3D operator*(const float& lambda);

	Vector3D componentMult (Vector3D v);

	float dotProd(Vector3D v);
	Vector3D crossProd(Vector3D v);
	float tripleProd(Vector3D u, Vector3D v);

	float norm();
	Vector3D normalized();

	void display();
};

#endif
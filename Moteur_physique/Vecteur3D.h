#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

using namespace std;

// Classe permettant de manipuler les vecteurs 3D
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

	Vecteur3D componentMult (Vecteur3D v);//produit des composantes

	float dotProd(Vecteur3D v);//produit scalaire
	Vecteur3D crossProd(Vecteur3D v);//produit vectoriel
	float tripleProd(Vecteur3D u, Vecteur3D v);//produit mixte : this.(u^v)

	float norm();
	Vecteur3D normalized();

	void display();
};

#endif
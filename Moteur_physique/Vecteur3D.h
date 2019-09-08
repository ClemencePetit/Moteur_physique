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

	Vecteur3D multScalaire(float k);
	Vecteur3D prodComposantes (Vecteur3D v);

	float prodScalaire(Vecteur3D v);
	Vecteur3D prodVectoriel(Vecteur3D v);
	float prodMixte(Vecteur3D u, Vecteur3D v);

	float magnitude();
	Vecteur3D normalized();

	void afficher();
};

#endif
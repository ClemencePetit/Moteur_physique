#ifndef DEF_VECTEUR3D
#define DEF_VECTEUR3D

#include <iostream>

using namespace std;

class Vecteur3D
{
private:

	float x_;
	float y_;
	float z_;

public:

	Vecteur3D();
	Vecteur3D(float x, float y, float z);

	~Vecteur3D();

	void setX(float x) { x_ = x; };
	void setY(float y) { y_ = y; };
	void setZ(float z) { z_ = z; };

	float getX() { return x_; };
	float getY() { return y_; };
	float getZ() { return z_; };

	Vecteur3D addition(Vecteur3D v);
	Vecteur3D multScalaire(float k);
	Vecteur3D prodComposantes (Vecteur3D v);
	float prodScalaire(Vecteur3D v);
	Vecteur3D prodVectoriel(Vecteur3D v);
	float prodMixte(Vecteur3D u, Vecteur3D v);

	void afficher();
};

#endif

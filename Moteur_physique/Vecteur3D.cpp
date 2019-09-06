#include "Vecteur3D.h"

Vecteur3D::Vecteur3D() : x(0), y(0), z(0)
{

}

Vecteur3D::Vecteur3D(float x, float y, float z) : x(x), y(y), z(z)
{

}

Vecteur3D::~Vecteur3D()
{

}

//static


Vecteur3D Vecteur3D::zero() {
	return Vecteur3D();
}

//Opérateurs
Vecteur3D Vecteur3D::operator+(const Vecteur3D& b) {
	Vecteur3D result(x + b.x, y + b.y, z + b.z);
	return result;
}


Vecteur3D Vecteur3D::operator*(const double& lambda) {
	Vecteur3D result(lambda * x, lambda * y, lambda * z);
	return result;
}

Vecteur3D Vecteur3D::multScalaire(float k)
{
	Vecteur3D result(k * x, k * y, k * z);
	return result;
}

Vecteur3D Vecteur3D::prodComposantes(Vecteur3D v)
{
	Vecteur3D result(x * v.x, y * v.y, z * v.z);
	return result;
}

float Vecteur3D::prodScalaire(Vecteur3D v)
{
	float result = x * v.x + y * v.y + z * v.z;
	return result;
}

Vecteur3D Vecteur3D::prodVectoriel(Vecteur3D v)
{
	Vecteur3D result(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return result;
}

float Vecteur3D::prodMixte(Vecteur3D u, Vecteur3D v)
{
	return this->prodScalaire(u.prodVectoriel(v));
}

float Vecteur3D::magnitude() {
	return sqrt(x * x + y * y + z * z);
}

Vecteur3D Vecteur3D::normalized() {
	return *this * (1. / this->magnitude());
}

void Vecteur3D::afficher()
{
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

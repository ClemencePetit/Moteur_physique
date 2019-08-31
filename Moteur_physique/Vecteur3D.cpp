#include "Vecteur3D.h"

Vecteur3D::Vecteur3D() : x_(0), y_(0), z_(0)
{

}

Vecteur3D::Vecteur3D(float x, float y, float z) : x_(x), y_(y), z_(z)
{

}

Vecteur3D::~Vecteur3D()
{

}

Vecteur3D Vecteur3D::addition(Vecteur3D v)
{
	Vecteur3D result(x_ + v.x_, y_ + v.y_, z_ + v.z_);
	return result;
}

Vecteur3D Vecteur3D::multScalaire(float k)
{
	Vecteur3D result(k * x_, k * y_, k * z_);
	return result;
}

Vecteur3D Vecteur3D::prodComposantes(Vecteur3D v)
{
	Vecteur3D result(x_ * v.x_, y_ * v.y_, z_ * v.z_);
	return result;
}

float Vecteur3D::prodScalaire(Vecteur3D v)
{
	float result = x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
	return result;
}

Vecteur3D Vecteur3D::prodVectoriel(Vecteur3D v)
{
	Vecteur3D result(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
	return result;
}

float Vecteur3D::prodMixte(Vecteur3D u, Vecteur3D v)
{
	return this->prodScalaire(u.prodVectoriel(v));
}

void Vecteur3D::afficher()
{
	cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << endl;
}

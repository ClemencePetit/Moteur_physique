#pragma once

#include "Vecteur3D.h"
#include "Shape.h"

class Particule
{

private:

	Vecteur3D* pos_;
	Vecteur3D vit_;
	Vecteur3D g_;

	float massInv_;

	//damping
	float d_;

	//mass
	float m_;

	Shape* shape_;

public:

	Particule(float g, Vecteur3D* pos, Vecteur3D vit, float m, float d);

	~Particule();

	void setPos(Vecteur3D* pos) { pos_ = pos; };
	void setVit(Vecteur3D vit) { vit_ = vit; };
	void setG(Vecteur3D g) { g_ = g; };
	void setD(float d) { d_ = d; };
	void setM(float m) { m_ = m; };
	void setMassInv(float massInv) { massInv_ = massInv; };	
	void setShape(Shape* sh) { shape_ = sh; }

	Vecteur3D* getPos() { return pos_; };
	Vecteur3D getVit() { return vit_; };
	Vecteur3D getG() { return g_; };
	float getD() { return d_; };
	float getM() { return m_; };
	float getMassInv() { return massInv_; };
	Shape* getShape() { return shape_; }

	void integrer(float t);
};


// Fonctions static retournant des projectiles paramétrés

static Particule* getProjectile1(float g) {
	Particule* pa = new Particule(g, new Vecteur3D(0, 0, 5), Vecteur3D(0, 50, 50), 500.0, 0.5);
	pa->setShape(new Sphere(pa->getPos(), 0, 1.0, 0.0, 2));
	return pa;
}

static Particule* getProjectile2(float g) {
	Particule* pa = new Particule(g, new Vecteur3D(0, 0, 5), Vecteur3D(0, 100, 100), 5000.0, 0.95);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 0.0, 2));
	return pa;
}

static Particule* getProjectile3(float g) {
	Particule* pa = new Particule(g, new Vecteur3D(0, 0, 5), Vecteur3D(0, 300, 0), 1.0, 0.3);
	pa->setShape(new Rect3D(pa->getPos(), 1.0, 0.0, 0.0, 200, 2, 2));
	return pa;
}

static Particule* getProjectile4(float g) {
	Particule* pa = new Particule(g, new Vecteur3D(0, 0, 5), Vecteur3D(0, 100, 50), 55.0, 0.7);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 1.0, 2));
	return pa;
}
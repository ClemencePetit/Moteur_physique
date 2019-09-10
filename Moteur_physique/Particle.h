#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"
#include "Shape.h"

// Classe contenant les données concernant la particule d'un point de vue physique, plus la forme qui est associée à la particule
class Particle
{

private:

	Vector3D* pos_;//position
	Vector3D vel_;//velocité
	Vector3D g_;//loi de la gravitation universelle

	float d_;//damping
		
	float m_;//mass
	float massInv_;

	Shape* shape_;//forme associée à la particule pour la dessiner

public:

	Particle(float g, Vector3D* pos, Vector3D vit, float m, float d);

	~Particle();

	//get/set
	void setPos(Vector3D pos) { *pos_ = pos; };
	void setVit(Vector3D vit) { vel_ = vit; };
	void setG(Vector3D g) { g_ = g; };
	void setD(float d) { d_ = d; };
	void setM(float m) { m_ = m; };
	void setMassInv(float massInv) { massInv_ = massInv; };	
	void setShape(Shape* sh) { shape_ = sh; }

	Vector3D* getPos() { return pos_; };
	Vector3D getVit() { return vel_; };
	Vector3D getG() { return g_; };
	float getD() { return d_; };
	float getM() { return m_; };
	float getMassInv() { return massInv_; };
	Shape* getShape() { return shape_; }

	void integrer(float t);//integrator
};


// Fonctions static retournant des projectiles paramétrés

static Particle* getProjectile1(float g) {
	Particle* pa = new Particle(g, new Vector3D(0, 0, 5), Vector3D(0, 50, 50), 500.0, 0.5);
	pa->setShape(new Sphere(pa->getPos(), 0, 1.0, 0.0, 2));
	return pa;
}

static Particle* getProjectile2(float g) {
	Particle* pa = new Particle(g, new Vector3D(0, 0, 5), Vector3D(0, 100, 100), 5000.0, 0.95);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 0.0, 2));
	return pa;
}

static Particle* getProjectile3(float g) {
	Particle* pa = new Particle(g, new Vector3D(0, 0, 5), Vector3D(0, 3000, 0), 1.0, 1);
	pa->setShape(new Rect3D(pa->getPos(), 1.0, 0.0, 0.0, 1, 1, 1));
	return pa;
}//laser

static Particle* getProjectile4(float g) {
	Particle* pa = new Particle(g, new Vector3D(0, 0, 5), Vector3D(0, 100, 50), 55.0, 0.7);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 1.0, 2));
	return pa;
}

#endif
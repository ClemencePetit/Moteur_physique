#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"
#include "Shape.h"

// Classe contenant les données concernant la particule d'un point de vue physique, plus la forme qui est associée à la particule
class Particle
{

private:

	Vector3D* pos_; //position
	Vector3D vel_; //velocité

	Vector3D forceAccum_;
	float massInv_;

	Shape* shape_; //forme associée à la particule pour la dessiner

public:

	Particle(Vector3D* pos, Vector3D vit, float m);

	~Particle();

	//get/set
	void setPos(Vector3D pos) { *pos_ = pos; };
	void setVit(Vector3D vit) { vel_ = vit; };
	void setMassInv(float massInv) { massInv_ = massInv; };	
	void setShape(Shape* sh) { shape_ = sh; }

	Vector3D* getPos() { return pos_; };
	Vector3D getVit() { return vel_; };
	float getMassInv() { return massInv_; };
	Shape* getShape() { return shape_; }

	//methods for forceAccum
	void addForce(const Vector3D &force);
	void clearAccum();

	void integrer(float t);//integrator
};


// Fonctions static retournant des projectiles paramétrés

static Particle* getBasicBall() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 500.0);
	pa->setShape(new Sphere(pa->getPos(), 0, 1.0, 0.0, 2)); //Vert
	return pa;
}

static Particle* getCannonBall() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 5000.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 0.0, 2)); //Noir
	return pa;
}

static Particle* getLaser() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), -1.0);
	pa->setShape(new Rect3D(pa->getPos(), 1.0, 0.0, 0.0, 1, 1, 1)); //Rouge
	return pa;
}

static Particle* getSnowflake() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 55.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 1.0, 2)); //Bleu
	return pa;
}

static Particle* getTestWater() {
	Particle* pa = new Particle(new Vector3D(175, 0, -30), Vector3D(0, 0, 0), 10.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 1.0, 1.0, 2));
	return pa;
}
#endif
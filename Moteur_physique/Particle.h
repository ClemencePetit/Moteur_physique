#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"
#include "Shape.h"
#include "IParticle.h"

// Classe contenant les donn�es concernant la particule d'un point de vue physique, plus la forme qui est associ�e � la particule
class Particle : public IParticle
{

private:
	
	int index_;

	Vector3D* pos_; //position
	Vector3D vel_; //velocit�

	Vector3D forceAccum_;
	float massInv_;

	float collRadius_;

	Shape* shape_; //forme associ�e � la particule pour la dessiner

public:

	Particle(Vector3D* pos, Vector3D vit, float m, int index);

	~Particle();

	//get/set
	void setPos(Vector3D pos) { *pos_ = pos; };
	void setVit(Vector3D vit) { vel_ = vit; };
	void setMassInv(float massInv) { massInv_ = massInv; };	
	void setShape(Shape* sh) { 
		shape_ = sh; 
		collRadius_ = sh->getRadius();
	};
	void setCollRadius(float rad) { collRadius_ = rad; };

	Vector3D* getPos() { return pos_; };
	Vector3D getVit() { return vel_; };
	float getMassInv() { return massInv_; };
	Shape* getShape() { return shape_; };
	int getIndex() { return index_; };
	float getCollRadius() { return collRadius_; };

	//IPARTICLE
	void addTo(list<Particle*> list);
	void draw();
	void drawVelocity();

	//methods for forceAccum
	void addForce(const Vector3D &force);
	void clearAccum();

	void integrer(float t);//integrator
};

#endif
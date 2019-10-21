
#ifndef IPARTICLE
#define IPARTICLE

#include <list>
#include "Vector3D.h"

class IParticle {

public:
	virtual void setPos(Vector3D pos) = 0;
	virtual void setVit(Vector3D vit) = 0;

	virtual Vector3D* getPos() = 0;
	virtual Vector3D getVit() = 0;

	virtual void draw() = 0;

};

//En déclarant les classes ici on évite un problème de dépendance circulaire.
class Particle;
class ParticleGroup;

#endif

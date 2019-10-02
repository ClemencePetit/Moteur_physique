#include "ParticleFactory.h"


IParticle* ParticleFactory::getBasicBall() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 500.0);
	pa->setShape(new Sphere(pa->getPos(), 0, 1.0, 0.0, 2)); //Vert
	return pa;
}

IParticle* ParticleFactory::getCannonBall() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 5000.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 0.0, 2)); //Noir
	return pa;
}

IParticle* ParticleFactory::getLaser() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), -1.f);
	pa->setShape(new Rect3D(pa->getPos(), 1.0, 0.0, 0.0, 1, 1, 1)); //Rouge
	return pa;
}

IParticle* ParticleFactory::getSnowflake() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 55.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 1.0, 2)); //Bleu
	return pa;
}

IParticle* ParticleFactory::getDefaultCrosshair() {
	Particle* pa = new Particle(new Vector3D(0, 0, 5), Vector3D(0, 0, 0), 55.0);
	pa->setShape(new Sphere(pa->getPos(), 0.0, 0.0, 1.0, 2)); //Bleu
	return pa;
}
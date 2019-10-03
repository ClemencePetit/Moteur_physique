#include "ParticleFactory.h"
#include "ParticleGroup.h"

IParticle* ParticleFactory::getCurrentProjectile() {

	switch (currentProjectileIndex_) {
	case 0:
		return getBasicBall();
		break;
	case 1:
		return getCannonBall();
		break;
	case 2:
		return getLaser();
		break;
	case 3:
		return getSnowflake();
		break;
	case 4:
		return getYoyo();
		break;
	case 5:
		return getBlob1();
		break;
	case 6:
		return getBlob2();
		break;
	}
	return getBasicBall();
}

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


IParticle* ParticleFactory::getYoyo() {

	std::vector<Particle*> pas;

	Particle* a = (Particle*)getBasicBall();

	a->getShape()->setColor(50, 0, 120);

	pas.push_back(a);

	//Forces
	ParticleForceRegister fg;

	fg.add(a, new AnchoredSpringFG(Vector3D(), 0.5, 1000));

	ParticleGroup* pg = new ParticleGroup(pas, fg);

	return pg;
}

IParticle* ParticleFactory::getBlob1() {
	//Square linked blob

//Particles
	std::vector<Particle*> pas;

	Particle* a = (Particle*)getBasicBall();
	Particle* b = (Particle*)getBasicBall();
	Particle* c = (Particle*)getBasicBall();
	Particle* d = (Particle*)getBasicBall();

	float r = 100;
	float v = 100;
	float bl = 30;
	a->getShape()->setColor(r, v, bl);
	b->getShape()->setColor(r, v, bl);
	c->getShape()->setColor(r, v, bl);
	d->getShape()->setColor(r, v, bl);

	pas.push_back(a);
	pas.push_back(b);
	pas.push_back(c);
	pas.push_back(d);

	//Forces
	ParticleForceRegister fg;

	
	fg.add(a, new BungeeSpringFG(b, 0.5, 100));
	fg.add(b, new BungeeSpringFG(c, 0.5, 100));
	fg.add(c, new BungeeSpringFG(d, 0.5, 100));
	fg.add(d, new BungeeSpringFG(a, 0.5, 100));
	

	ParticleGroup* pg = new ParticleGroup(pas, fg);

	return pg;
}

IParticle* ParticleFactory::getBlob2() {

	//Square linked blob

	//Particles
	std::vector<Particle*> pas;

	Particle* a = (Particle*)getBasicBall();
	Particle* b = (Particle*)getBasicBall();
	Particle* c = (Particle*)getBasicBall();
	Particle* d = (Particle*)getBasicBall();

	//Colors
	float r = 140;
	float v = 100;
	float bl = 0;
	a->getShape()->setColor(r, v, bl);
	b->getShape()->setColor(r, v, bl);
	c->getShape()->setColor(r, v, bl);
	d->getShape()->setColor(r, v, bl);

	pas.push_back(a);
	pas.push_back(b);
	pas.push_back(c);
	pas.push_back(d);

	//Forces
	ParticleForceRegister fg;

	fg.add(a, new SpringFG(b, 1, 5));
	fg.add(b, new SpringFG(c, 1, 5));
	fg.add(c, new SpringFG(d, 1, 5));
	fg.add(d, new SpringFG(a, 1, 5));

	ParticleGroup* pg = new ParticleGroup(pas, fg);

	return pg;
}
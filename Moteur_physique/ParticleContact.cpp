#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* pa1, Particle* pa2, float restit, float dPene, Vector3D n): restit_(restit), dPene_(dPene), n_(n.normalized())
{
	particles_[0] = pa1;
	particles_[1] = pa2;
	vs_ = calculVs();
}

ParticleContact::~ParticleContact()
{
}

void ParticleContact::resolve(float t) {
	resolveInterpenetration();
	resolveVelocity(t);
}

float ParticleContact::calculVs() {
	//Cas d'un sol
	if (particles_[1] == NULL) {
		return (particles_[0]->getVit().dotProd(n_));
	}
	//Cas de 2 particules
	else {
		return ((particles_[0]->getVit() - particles_[1]->getVit()).dotProd(n_));
	}
}

void ParticleContact::resolveVelocity(float t) {

	if (vs_ <= 0) return; //ils ne se rapprochent pas et non donc pas besoin d'etre �loign�s

	float vTemp = restit_ * vs_;
	//Cas d'un sol
	if (particles_[1] == NULL) {
		particles_[0]->setVit(particles_[0]->getVit() + n_ * -vTemp * t);
	}
	//Cas de 2 particules
	else {
		particles_[0]->setVit(particles_[0]->getVit() + n_ * -vTemp * t);
		particles_[1]->setVit(particles_[1]->getVit() + n_ * -vTemp * t);
	}
}

void ParticleContact::resolveInterpenetration() {
	//Cas d'un sol
	if (particles_[1] == NULL) {
		particles_[0]->setPos(*particles_[0]->getPos() + n_ * -dPene_);
	}
	//Cas de 2 particules
	else {
		float ma = 1 / particles_[0]->getMassInv();
		float mb = 1 / particles_[1]->getMassInv();

		Vector3D deltaPA = n_ * (mb / (ma + mb)) * dPene_;
		Vector3D deltaPB = n_ * -1 * (ma / (ma + mb)) * dPene_;

		particles_[0]->setPos(*particles_[0]->getPos() + deltaPA);
		particles_[1]->setPos(*particles_[1]->getPos() + deltaPB);
	}
}
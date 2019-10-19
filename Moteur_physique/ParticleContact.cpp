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
	resolveVelocity();
}

float ParticleContact::calculVs() {

	Vector3D closingVelocityA = particles_[0]->getVit();
	//Cas d'un sol
	if (particles_[1] == NULL) {

		return closingVelocityA.dotProd(n_);
		
		/*
		Vector3D closingVelocityA = particles_[0]->getVit();
		float j = (closingVelocityA).dotProd(n_) * restit_;
		return j; */
	}
	//Cas de 2 particules
	else {

		Vector3D closingVelocityB = particles_[1]->getVit();
		return (closingVelocityA - closingVelocityB).dotProd(n_);

		
		/*
		float factor = (-1 + restit_) / (particles_[0]->getMassInv() + particles_[1]->getMassInv());
		float j = (closingVelocityA - closingVelocityB).dotProd(n_) * factor; 
		return j; */
	}
}

void ParticleContact::resolveVelocity() {

	if (vs_ <= 0) return; //ils ne se rapprochent pas et non donc pas besoin d'etre �loign�s

	float vsP = -restit_ * vs_;

	//Cas d'un sol
	if (particles_[1] == NULL) {

		particles_[0]->setVit(particles_[0]->getVit() + n_ * vsP);

		//particles_[0]->setVit(particles_[0]->getVit() + n_* vs_ * particles_[0]->getMassInv());
	}
	//Cas de 2 particules
	else {


		particles_[0]->setVit(particles_[0]->getVit() + n_ * vsP * particles_[0]->getMassInv());
		particles_[1]->setVit(particles_[1]->getVit() - n_ * vsP * particles_[1]->getMassInv());

		//particles_[0]->setVit(particles_[0]->getVit() + n_ * vs_ * particles_[0]->getMassInv());
		//particles_[1]->setVit(particles_[1]->getVit() - n_ * vs_ * particles_[1]->getMassInv());

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
		Vector3D deltaPB = n_ * (ma / (ma + mb)) * dPene_ * - 1;

		particles_[0]->setPos(*particles_[0]->getPos() + deltaPA);
		particles_[1]->setPos(*particles_[1]->getPos() + deltaPB);
	}
}

ParticleContact* ParticleContact::getContact(Particle* pa, Particle* pb)
{
	return nullptr;
}

ParticleContact* ParticleContact::getContact(Sphere s1, Sphere s2)
{
	ParticleContact* contact = nullptr;
	float restit = 0.95f;

	float distAB = s1.getPos().distanceWith(s2.getPos());
	float cumulatedRadius = s1.getRadius() + s2.getRadius();

	if (distAB < cumulatedRadius) {

		//PARAMETERS, TO MOVE

		float dPene = cumulatedRadius - distAB;
		Vector3D n = s2.getPos() - s1.getPos();

		contact = new ParticleContact(nullptr, nullptr, restit, dPene, n.normalized());
		
	}

	return contact;
}

ParticleContact* ParticleContact::getContact(Rect3D rect1, Rect3D rect2)
{
	return nullptr;
}

ParticleContact* ParticleContact::getContact(Sphere sphere, Rect3D rect)
{
	float restit = 0.75f;
	ParticleContact* contact = nullptr;

	//sphere and rect
	Vector3D minRect = rect.getMinPos();
	Vector3D maxRect = rect.getMaxPos();

	Vector3D nearestPoint(
		std::fmaxf(minRect.x, std::fminf(sphere.getPos().x, maxRect.x)),
		std::fmaxf(minRect.y, std::fminf(sphere.getPos().y, maxRect.y)),
		std::fmaxf(minRect.z, std::fminf(sphere.getPos().z, maxRect.z))
	);

	Vector3D delta(
		sphere.getPos().x - nearestPoint.x,
		sphere.getPos().y - nearestPoint.y,
		sphere.getPos().z - nearestPoint.z
	);

	float cornerDistanceSq = std::powf(delta.x, 2.f) + std::powf(delta.y, 2.f) + std::powf(delta.z, 2.f);


	if (cornerDistanceSq < std::powf(sphere.getRadius(), 2.f)) 
	{
		float dPene = cornerDistanceSq;
		Vector3D n = nearestPoint - sphere.getPos();

		contact = new ParticleContact(nullptr, nullptr, restit, dPene, n.normalized());
	}

	//Verify if the sphere is on the
	return contact;
}

ParticleContact* ParticleContact::getContact(Rect3D rect, Sphere sphere)
{
	return getContact(sphere, rect);
}

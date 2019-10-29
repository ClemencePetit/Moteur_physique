#include "PhysicSimulator.h"

#pragma region Private Methods

/**
	Test all collisions and resolve them, but only one iteration.
**/
int PhysicSimulator::resolveCollisions()
{
	int iter = 0;

	std::list<Particle*>::iterator itA;
	std::list<Particle*>::iterator itB;

	for (itA = particles_.begin(); itA != particles_.end(); itA++) {
		//Collisions entre particules
		for (itB = next(itA, 1); itB != particles_.end(); itB++) {

			ParticleContact* contact = getContact(*itA, *itB);

			if (contact != nullptr) {
				contactResolver_.addContact(contact);
				iter += 1;
			}
		}


	}

	return iter;
}


ParticleContact* PhysicSimulator::getContact(Particle* pa, Particle* pb)
{
	//Test shape contacts
	Contact contact = pa->getShape()->collideWith(*pb->getShape());

	if (contact.hasContact_) {
		return new ParticleContact(pa, pb, 0.8f, contact.dPene_, contact.n_);
	}
	else {
		return nullptr;
	}
}

/**
	Apply all registered Forces to the particles, then clear the register.
**/
void PhysicSimulator::applyRegister(float elapsedTime)
{
	std::list<Particle*>::iterator it;
	std::list<ParticleGroup*>::iterator ite;

	//Register Particules
	for (it = particles_.begin(); it != particles_.end(); it++)
	{

		//skip immovable objects
		if ((*it)->isStatic_) {
			continue;
		}

		register_.add(*it, new GravityFG(g_));
		register_.add(*it, new DragFG(k1, k2));

		if (isInPool(*it)) {
			register_.add(*it, new BuoyancyFG());
		}

		//If very low
		//if ((*it)->getPos()->z <= 2 && !isInPool(*it)) {
		//	//register_.add(*it, new WeakSpringFG(0.1f, 0.7f));
		//}
		//else {
		//	//basics
		//	register_.add(*it, new GravityFG(g_));
		//	register_.add(*it, new DragFG(k1, k2));
			//if in pool
		//	if (isInPool(*it)) {
		//		register_.add(*it, new BuoyancyFG());
		//	}
		//}
	}
	register_.updateForces(elapsedTime);
	register_.clear();

	//Register Group Particules
	for (ite = particlesGroups_.begin(); ite != particlesGroups_.end(); ite++)
	{
		(*ite)->updateForces(elapsedTime);
	}
}

void PhysicSimulator::applyCollisions(float elapsedTime)
{
	int nbCollisions = 0;
	nbCollisions = resolveCollisions();
	contactResolver_.setIter(2 * nbCollisions);

	//We resolve collisions with a limit of collisions resolved per frame.
	while (contactResolver_.limitNotReached()) {
		contactResolver_.resolveContacts(elapsedTime);
		resolveCollisions();
	}

	contactResolver_.limitReached();
}

void PhysicSimulator::applyMovements(float elapsedTime)
{
	std::list<Particle*>::iterator it;

	//update physics for each particles
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		//If particle isn't null for some reasons
		if (*it != NULL) {

			//Compute new positions !
			(*it)->integrer(elapsedTime);

		}
	}
}

void PhysicSimulator::verifyDeletion()
{
	std::list<Particle*>::iterator it;
	std::list<ParticleGroup*>::iterator ite;

	//Delete particle groups
	auto groups_to_erase = std::remove_if(
		std::begin(particlesGroups_),
		std::end(particlesGroups_),
		[](ParticleGroup* paG) { 
			return paG != NULL && paG->isMarkedToDeletion();
		}
	);

	//call destructors
	for (ite = groups_to_erase; ite != cend(particlesGroups_); ite++) {
		delete(*ite);
	}

	//erase from list
	particlesGroups_.erase(groups_to_erase, cend(particlesGroups_));
	

	auto particles_to_erase = std::remove_if(
		std::begin(particles_),
		std::end(particles_),
		[](Particle* pa) {
			return pa != NULL && pa->getPos()->z < -100 || pa->isMarkedToDeletion();
		}
	);

	//call destructors
	for (it = particles_to_erase; it != cend(particles_); it++) {
		delete(*it);
	}

	//erase from list
	particles_.erase(particles_to_erase, cend(particles_));


	/*
	ite = particlesGroups_.begin();
	while (ite != particlesGroups_.end())
	{
		if ( *ite != NULL && (*ite)->isMarkedToDeletion()) {
				deleteParticleGroup(*ite);
		}
		else {
			ite++; //Only increment iterator if there's no deletion.
		}
	} */

	//Delete particles
	/*
	it = particles_.begin();
	while (it != particles_.end())
	{
		//Delete them if they are too low
		if ((*it) != NULL && (*it)->getPos()->z < -100 || (*it)->isMarkedToDeletion()) {
			deleteParticle(*it);
		}
		else {
			it++; //Only increment iterator if there's no deletion.
		}
	} */

}

bool PhysicSimulator::isInPool(Particle* p)
{
	return (p->getPos()->x > -200
		&& p->getPos()->x < 200
		&& p->getPos()->y > 100
		&& p->getPos()->y < 300
		&& p->getPos()->z > -50
		&& p->getPos()->z < 5);
}

void PhysicSimulator::drawParticles()
{
	std::list<Particle*>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->draw();
		}
	}
}

void PhysicSimulator::drawGroupParticles()
{//redraw all link between grouped particles
	std::list<ParticleGroup*>::iterator it;
	for (it = particlesGroups_.begin(); it != particlesGroups_.end(); it++)
	{
		if (*it != NULL) {
			(*it)->DrawLinks();
		}
	}
}
#pragma endregion

#pragma region Public Methods 

void PhysicSimulator::addParticle(IParticle* pa)
{
	//Use a dynamic cast to determine if it's a Particle or ParticleGroup

	//If it's a Particle
	if (Particle * ptrPq = dynamic_cast<Particle*>(pa)) {
		particles_.push_back(ptrPq);
	}
	//If it's a ParticleGroup
	else if (ParticleGroup * ptrPg = dynamic_cast<ParticleGroup*>(pa)) {

		for (auto const& pa : ptrPg->getParticles()) {
			particles_.push_back(pa);
		}

		particlesGroups_.push_back(ptrPg);
	}
}

void PhysicSimulator::deleteParticle(Particle* pa)
{
	particles_.remove(pa);
	if (pa->getGroup() != nullptr) {
		deleteParticleGroup(pa->getGroup());
		pa->setGroup(nullptr);
	}
	delete(pa);
}

void PhysicSimulator::deleteParticleGroup(ParticleGroup* paG)
{
	particlesGroups_.remove(paG);
	paG->markToDeletion();
	delete(paG);
}

void PhysicSimulator::deleteAllParticles()
{
	while (!particlesGroups_.empty()) {
		deleteParticleGroup(particlesGroups_.front());
	}
	while (!particles_.empty()) {
		deleteParticle(particles_.front());
	}
}

void PhysicSimulator::deleteAndClearAll()
{
	deleteAllParticles();
	register_.clear();
	contactResolver_.clear();
}

void PhysicSimulator::updatePhysics(float elapsedTime)
{

	applyRegister(elapsedTime);
	applyCollisions(elapsedTime);
	applyMovements(elapsedTime);
	verifyDeletion();

}

void PhysicSimulator::draw()
{
	drawParticles();
	drawGroupParticles();
}



#pragma endregion

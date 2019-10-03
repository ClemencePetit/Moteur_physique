#include "Vector3D.h"
#ifndef PARTICLE_GROUP
#define PARTICLE_GROUP

#include "IParticle.h"
#include "Particle.h"
#include "ParticleForceRegister.h"

class ParticleGroup : public IParticle
{
private:

	std::vector<Particle*> particles_;
	ParticleForceRegister forcesRegister_; //Forces specific to that group
public:

	ParticleGroup() {}

	ParticleGroup(std::vector<Particle*> particles, ParticleForceRegister forcesRegister)
		: particles_(particles), forcesRegister_(forcesRegister)
	{

	}

	//Getter and Setter

	//Set all particles to the same Pos (TODO : Keep offset)
	void setPos(Vector3D pos) {

		std::vector<Particle*>::iterator it;
		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			(*it)->setPos(pos);
		}
	};

	//Set all particles to the same speed
	void setVit(Vector3D vit) {
		std::vector<Particle*>::iterator it;
		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			(*it)->setVit(vit);
		}
	};

	Vector3D* getPos() {
		//Return the pos of the first particle
		return (*particles_.begin())->getPos();
	};


	void Draw();

	void addRecurringForce(Particle* pa, ParticleForceGenerator* fg);
	void addParticle(Particle* pa);

	void applyForces(float elapsedTime);

	void addTo(list<Particle*> list);
};

#endif


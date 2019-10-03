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

	void addRandomOffsets();
public:

	ParticleGroup() {}

	ParticleGroup(std::vector<Particle*> particles, ParticleForceRegister forcesRegister)
		: particles_(particles), forcesRegister_(forcesRegister)
	{
		addRandomOffsets();
	}

	//Getter and Setter

	//Set central particle to new pos and keep the offset between them
	void setPos(Vector3D pos) {

		std::vector<Particle*>::iterator it;

		Vector3D initialFirstParticlePos = *getPos();

		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			Vector3D initialPos = *(*it)->getPos();
			Vector3D offset = initialFirstParticlePos - initialPos;

			(*it)->setPos(pos + offset);
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

	std::vector<Particle*> getParticles() {
		return particles_;
	}

	void Draw();

	void updateForces(float elapsedTime);

};

#endif


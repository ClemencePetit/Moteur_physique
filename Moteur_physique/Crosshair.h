
#ifndef CROSSHAIR
#define CROSSHAIR

#include "IParticle.h"
#include "ParticleFactory.h"

class Crosshair
{
private:


	ParticleFactory factory_;

	IParticle* selectedParticle_;
	Vector3D pos_;
	Vector3D aimDirection_;


	//Charge shot
	float baseVelocity_ = 50.f;
	float minShotPower_ = 0.5f;
	float maxShotPower_ = 2.f;
	float timeLoadMaxShot_ = 1.f;

	//changing values
	float currentShotPower_ = 0.f;
	float currentLoadTime_ = 0.f;

	//Interpolation linéaire entre entre A et B avec t dans [0,1]
	float lerp01(float a, float b, float t);

public:

	Crosshair() : Crosshair(Vector3D(0, 0, 10)) {
	}

	Crosshair(Vector3D pos) : pos_(pos) {
		changeParticle(factory_.getCurrentProjectile());
	}

	void changeParticle(IParticle* pa);
	void selectNextParticle();

	void loadShot(float elapsedTime);
	
	IParticle* fireParticle();

	void draw();

	void setDirection(Vector3D direction) {
		aimDirection_ = direction.normalized();
	}

	void setAim(Vector3D aim) {
		aim = aim.normalized();
		//TODO : Make it so it doesn't use Vit();
		Vector3D* pos = selectedParticle_->getPos();
		//change angle
		*pos = pos_ + aim * 5.f;

		//change speed
		selectedParticle_->setVit((*selectedParticle_->getPos() - pos_).normalized());
	}
};


#endif


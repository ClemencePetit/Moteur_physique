#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Particle.h"
#include "ParticleGroup.h"
#include "Vector3D.h"
#include "ParticleForceRegister.h"
#include "DragFG.h"
#include "GravityFG.h"
#include "SpringFG.h"
#include "BuoyancyFG.h"
#include "AnchoredSpringFG.h"
#include "BungeeSpringFG.h"
#include "WeakSpringFG.h"
#include "IParticle.h"
#include "ParticleFactory.h"

// Classe de gestion globale. Dessine la scène, gère les particules, upate la logique et appelle leur fonction pour les dessiner
class Game
{
private:

	//Registre
	ParticleForceRegister register_;

	IParticle* crosshair_; //particule servant à la visée (réticule)
	float distanceReticleFromOrigin_ = 10.f;
	float baseVelocity_ = 50.f;

	//load shot
	float minShotPower = 0.5f;
	float maxShotPower = 2.f;
	float currentShotPower = 0.f;

	float timeLoadMaxShot = 1.f;
	float currentLoadTime = 0.f;
	bool isLeftMouseButtonDown = false;

	list <Particle*> particules_; //liste des particules créées
	list <ParticleGroup*> particulesGroups_;

	ParticleFactory factory;

	//Constantes
	Vector3D g_ = Vector3D(0, 0, -9.8f);
	float k1 = 0.5f;
	float k2 = 1.2f;

	//time
	double elapsedTime;
	clock_t stopTime = 0;
	clock_t startTime;

	//dimensions de l'écran
	int screenWidth = 900;
	int screenHeight = 600;

	//reglages camera
	Vector3D posCamera_ = Vector3D(50.0f, -50.f, 5.f);
	Vector3D lookCamera_ = Vector3D(0.f, 100.f, 15.f);

	//mouse
	Vector3D mousePos = Vector3D();

	//pour voir dans la piscine
	bool seeInWater_ = true;

public:


	//Glut
	void initRendering();
	void drawLine(Vector3D a, Vector3D b);

	//particles
	void changeCrosshairWithParticle(IParticle* pa);

	void addParticle(IParticle* pa);
	void deleteParticle(Particle* pa);

	//part of hotfix
	void setupInstance();

	//utils
	float lerp01(float a, float b, float t);
	bool isInPool(Particle* p);

	//constructor/deconstructor
	Game();
	~Game();

	// fonctions reliées à Glut et ses callbacks
	void handleKeypress(unsigned char key, int x, int y);
	void handleResize(int w, int h);
	void handlePassiveMouseMotion(int x, int y);
	void handleMouseClick(int button, int state, int x, int y);

	void drawGround();
	void drawPool();
	void drawParticles();
	void drawScene();

	void handleRegister();
	void updateAndDelete();
	void update(int value);

	//start the game and write the instructions

	void instructions();
	void execute(int argc, char** argv);
	
};

//hotfix because Glut doesn't like encapsulated call to Reshape/DisplayFunc ect..
static Game* j_CurrentInstance;

extern "C"
static void drawSceneCallback() {
	j_CurrentInstance->drawScene();
}
static void handleResizeCallback(int w, int h) {
	j_CurrentInstance->handleResize(w, h);
}

static void handlePassiveMouseMotionCallback(int x, int y) {
	j_CurrentInstance->handlePassiveMouseMotion(x, y);
}

static void handleMouseClickCallback(int button, int state, int x, int y) {
	j_CurrentInstance->handleMouseClick(button, state, x, y);
}

static void handleKeypressCallback(unsigned char key, int x, int y) {
	j_CurrentInstance->handleKeypress(key, x, y);
}

static void updateCallback(int value) {
	j_CurrentInstance->update(value);
}

#endif
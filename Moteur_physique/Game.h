#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Particle.h"
#include "Vector3D.h"

// Classe de gestion globale. Dessine la scène, gère les particules, upate la logique et appelle leur fonction pour les dessiner
class Game
{
private:

	Particle* crosshair_;//particule servant à la visée (réticule)
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
	int indexCurrentParticle_; //indice du type de projectile actuellement choisi
	float g_ = 9.8;
	double elapsedTime;
	clock_t stopTime=0;
	clock_t startTime;
	float t_ = 0.033; //intervalle entre deux frames (fixé ici)

	//dimensions de l'écran
	int screenWidth = 900;
	int screenHeight = 600;

	//reglages camera
	Vector3D posCamera_ = Vector3D(50.0f, -50.f, 5.f);
	Vector3D lookCamera_ = Vector3D(0.f, 100.f, 15.f);

	

public:


	//Glut
	void initRendering();
	void drawLine(Vector3D a, Vector3D b);

	//particles
	void changeCrosshairWithParticle(Particle* pa);
	Particle* getCurrentParticle();
	void addParticle(Particle* pa);
	void deleteParticle(Particle* pa);

	//part of hotfix
	void setupInstance();

	float lerp01(float a, float b, float t);

public:

	//constructor/deconstructor
	Game();
	~Game();

	// fonctions reliées à Glut et ses callbacks
	void handleKeypress(unsigned char key, int x, int y);
	void handleResize(int w, int h);
	void handlePassiveMouseMotion(int x, int y);
	void handleMouseClick(int button, int state, int x, int y);
	void drawScene();
	void update(int value);

	//start the game
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
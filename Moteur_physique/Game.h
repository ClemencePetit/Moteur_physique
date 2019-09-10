#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Particle.h"

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
	float t_ = 0.033; //intervalle entre deux frames (fixé ici)

		//reglages camera
		int posx_=50;
		int posy_=-50;
		int posz_=5;
		int lookx_=0;
		int looky_=100;
		int lookz_=15;

	public:
	//dimensions de l'écran
	int screenWidth = 900;
	int screenHeight = 600;


	//part of hotfix
	void setupInstance();

	//Glut
	void initRendering();
	void drawLine(Vector3D a, Vector3D b);

	//particles
	void updateReticleWithParticle(Particle* pa);
	Particle* getCurrentParticle();
	void addParticle(Particle* pa);
	void deleteParticle(Particle* pa);

	float lerp01(float a, float b, float t);

	//update logic

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
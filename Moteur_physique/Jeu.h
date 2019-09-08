#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Particule.h"

class Jeu
{
private:

	Particule* reticule_;
	int indexCurrentParticle_;
	float distanceReticleFromOrigin_ = 10.f;
	float baseVelocity_ = 50.f;


	list <Particule*> particules_;
	float g_ = 9.8;
	float t_ = 0.033;
	time_t currentTime_ = time(NULL);

	int screenWidth = 600;
	int screenHeight = 600;

public:

	Jeu();
	~Jeu();

	//part of hotfix
	void setupInstance();

	//glut
	void handleKeypress(unsigned char key, int x, int y);
	void initRendering();
	void handleResize(int w, int h);
	void drawScene();
	void handlePassiveMouseMotion(int x, int y);
	void handleMouseClick(int button, int state, int x, int y);

	//particles
	void updateReticleWithParticle(Particule* pa);
	Particule* getCurrentParticle();
	void addParticle(Particule* pa);
	void deleteParticle(Particule* pa);

	//update logic
	void update(int value);


	void execute(int argc, char** argv);
	
};

//hotfix because Glut doesn't like encapsulated call to Reshape/DisplayFunc ect..
static Jeu* j_CurrentInstance;

extern "C"
static void drawSceneCallback() {
	j_CurrentInstance->drawScene();
}
static void handleResizeCallback(int w, int h) {
	j_CurrentInstance->handleResize(w, h);
}
static void handleKeypressCallback(unsigned char key, int x, int y) {
	j_CurrentInstance->handleKeypress(key, x, y);
}

static void handlePassiveMouseMotionCallback(int x, int y) {
	j_CurrentInstance->handlePassiveMouseMotion(x, y);
}

static void handleMouseClickCallback(int button, int state, int x, int y) {
	j_CurrentInstance->handleMouseClick(button, state, x, y);
}

static void updateCallback(int value) {
	j_CurrentInstance->update(value);
}
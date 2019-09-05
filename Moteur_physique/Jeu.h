#pragma once

#include "Particule.h"
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Jeu
{
private:

	Particule* currentPart_ = NULL;
	float g_ = 9.8;
	float t_ = 0.033;
	time_t currentTime_ = time(NULL);

public:

	Jeu();
	~Jeu();

	//part of hotfix
	void setupInstance();

	void handleKeypress(unsigned char key, int x, int y);
	void initRendering();
	void handleResize(int w, int h);
	void drawScene();
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

static void updateCallback(int value) {
	j_CurrentInstance->update(value);
}
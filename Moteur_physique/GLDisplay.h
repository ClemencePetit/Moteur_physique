#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>   
#include "Shape.h"

class GLDisplay
{
public:

	int startGlut(int argc, char** argv);
	void AddRect3D(Vecteur3D position, float width, float height, float prof);
	void AddSphere(Vecteur3D position, float rayon);

	//part of hotfix
	void renderScene();
	void changeSize(int w, int h);
	void keyPressEvent(unsigned char key, int x, int y);

private:
	//part of hotfix
	void setupInstance();

	list <Shape*> shapes_;
	float distance_;
	float phi_;
	float teta_;


};


//hotfix because Glut doesn't like encapsulated call to Reshape/DisplayFunc ect..
static GLDisplay* g_CurrentInstance;

extern "C"
static void renderSceneCallback() {
	g_CurrentInstance->renderScene();
}
static void changeSizeCallback(int w, int h) {
	g_CurrentInstance->changeSize(w, h);
}
static void keyPressCallback(unsigned char key, int x, int y) {
	g_CurrentInstance->keyPressEvent(key, x, y);
}


#endif


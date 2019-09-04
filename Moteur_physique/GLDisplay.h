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
	void AddCube(Vecteur3D position, float width);

	//part of hotfix
	void renderScene();
	void changeSize(int w, int h);
	void keyPressEvent(unsigned char key, int x, int y);

private:
	//part of hotfix
	void setupInstance();

	list <Shape*> shapes;

	void DrawCube(GLfloat x, GLfloat y, GLfloat width);

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


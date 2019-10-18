
#ifndef GLUT_UTILS
#define GLUT_UTILS

#include "Vector3D.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class GlutUtils
{

public:

	static void drawLine(Vector3D a, Vector3D b, Vector3D color);
	static void drawSphere(Vector3D pos, float radius, Vector3D color);
	static void drawRectangle(Vector3D pos, float w, float h, float p, Vector3D color);
};

#endif


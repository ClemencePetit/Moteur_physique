#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"
#include "GLDisplay.h"
#include <stdlib.h>     
#include <time.h>



int main(int argc, char** argv) {

	GLDisplay gl;

	Vecteur3D a(30, 40, 0);
	Vecteur3D b(10, 20, 0);
	Vecteur3D c(15, 40, 0);

	gl.AddRect3D(a, 6,6,6);
	gl.AddRect3D(b, 3,3,3);
	gl.AddRect3D(c, 4,4,4);

	gl.startGlut(argc, argv);

	return 1;
}




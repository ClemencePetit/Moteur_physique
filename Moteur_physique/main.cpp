#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>     
#include <time.h>

#include "Jeu.h"

int main(int argc, char** argv) {

	Jeu jeu;
	jeu.execute(argc, argv);

	return 0;
}
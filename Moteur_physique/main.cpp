#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"
#include "GLDisplay.h"
#include "Jeu.h"
#include <stdlib.h>     
#include <time.h>



int main(int argc, char** argv) {

	/*
	GLDisplay gl;

	Vecteur3D a(0, 1, 0);
	Vecteur3D b(10, 0, 0);
	Vecteur3D c(15, 40, 0);

	a.afficher();
	b.afficher();
	c.afficher();

	cout << "norme a : " << a.magnitude() << endl;
	cout << "norme b : " << b.magnitude() << endl;
	cout << "norme c : " << c.magnitude() << endl;

	a.normalized().afficher();
	b.normalized().afficher();
	c.normalized().afficher();

	gl.AddRect3D(a, 6,6,6);
	gl.AddRect3D(b, 3,3,3);
	gl.AddRect3D(c, 4,4,4);

	gl.startGlut(argc, argv);
	*/

	Jeu jeu;
	jeu.execute(argc, argv);

	return 0;
}




#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"
#include <stdlib.h>     
#include <time.h>


int type_part;
int pos_y;
int pos_x;

const unsigned int WIN_WIDTH = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM = 50.0f;

/*const unsigned int WIN_WIDTH = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM = 50.0f;*/

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glColor3f(1, 0, 0);
	// Debut de l'affichage
	glTranslatef(-80, -40, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 2);
	glVertex2f(0, 0);
	glVertex2f(2, 0);
	glVertex2f(2, 2);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 1, 0);

	glTranslatef(-80 + pos_x, -40 + pos_y, 0);
	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, type_part, 10, 40);
	gluDeleteQuadric(quadrique);

	glPopMatrix();
	glFlush();
}

void Resize(int width, int height) {
	glViewport(0, 0, width, height);

	// Definition de la matrice de projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

	// Definition de la matrice de modele
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyPressEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		glRotatef(5, 0, 0, 1);
		break;
	case 't':
		glRotatef(5, 0, 0, -1);
		break;

		// Cas par defaut
	default:
	{

		return;
	}
	}
	MyDisplay();
	glFlush();

}


int main(int argc, char** argv) {

	// Test de la classe Vecteur3D
	Vecteur3D x(1, 2, 3);
	Vecteur3D y(4, 5, 6);
	Vecteur3D z(7, 8, 9);
	cout << "On a 3 vecteurs:" << endl;
	x.afficher();
	y.afficher();
	z.afficher();
	cout << endl << "Addition de x et y:" << endl;
	x.addition(y).afficher();
	cout << endl << "Multiplication scalaire de x par 5:" << endl;
	x.multScalaire(5).afficher();
	cout << endl << "Produit des composantes de x et y:" << endl;
	x.prodComposantes(y).afficher();
	cout << endl << "Produit scalaire de x par y:" << endl;
	cout << x.prodScalaire(y) << endl;
	cout << endl << "Produit vectoriel de x par y:" << endl;
	x.prodVectoriel(y).afficher();
	cout << endl << "Produit mixte de x, y et z:" << endl;
	cout << x.prodMixte(y, z) << endl;

	//Valeurs arbitraires pour la position et la taille (le type) de la particule :
	pos_x = 5;
	pos_y = 2;
	type_part = 1;

	// Test de la partie graphisme
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);	
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIN_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WIN_HEIGHT) / 2);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(keyPressEvent);
	glutMainLoop();

	return 0;
}



#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vecteur3D.h"

void MyDisplay() {                      
	glClear(GL_COLOR_BUFFER_BIT);       
	glViewport(0, 0, 300, 300);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);                
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
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

	// Test de la partie graphisme
	glutInit(&argc, argv);               
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);         
	glutMainLoop();

	return 0;
}
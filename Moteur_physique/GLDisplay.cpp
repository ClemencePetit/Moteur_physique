
#include "GLDisplay.h"

#include <stdlib.h>  


const unsigned int WIN_WIDTH = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM = 50.0f;

	//part of hotfix
	void GLDisplay::setupInstance() {
		::g_CurrentInstance = this;
		::glutDisplayFunc(::renderSceneCallback);
		::glutReshapeFunc(::changeSizeCallback);
		::glutKeyboardFunc(::keyPressCallback);
	}


	void GLDisplay::DrawCube(GLfloat x, GLfloat y, GLfloat width) {

		glPushMatrix();
		glColor3f(1, 0, 0);
		// Debut de l'affichage
		glTranslatef(x, y, 0);

		glBegin(GL_QUADS);
		glVertex2f(0, width);
		glVertex2f(0, 0);
		glVertex2f(width, 0);
		glVertex2f(width, width);
		glEnd();
		glPopMatrix();

	}

	void GLDisplay::AddCube(Vecteur3D position, float width) {
		Shape* cube = new Rect(position, width, width);
		shapes.push_back(cube);
	}


	void GLDisplay::renderScene(void) {

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();

		gluLookAt(0.0f, 0.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

		//iterator
		std::list<Shape*>::iterator it;
		// Make iterate point to begining and incerement it one by one till it reaches the end of list.
		for (it = shapes.begin(); it != shapes.end(); it++)
		{
			(*it)->Draw();
		}

		glutSwapBuffers();
	}

	void GLDisplay::changeSize(int width, int height) {
		glViewport(0, 0, width, height);

		// Definition de la matrice de projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

		// Definition de la matrice de modele
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	void GLDisplay::keyPressEvent(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'r':
			AddCube(Vecteur3D(0, 0, 0), 5);
			break;
		case 't':
			AddCube(Vecteur3D(-10, -20, 0), 2);
			break;

			// Cas par defaut
		default:
		{

			return;
		}
		}
		renderScene();
		glFlush();

	}

	int GLDisplay::startGlut(int argc, char** argv) {

		// init GLUT and create window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

		glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIN_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WIN_HEIGHT) / 2);

		glutCreateWindow("Lighthouse3D- GLUT Tutorial");

		// register callbacks
		GLDisplay::setupInstance();

		// enter GLUT event processing cycle
		glutMainLoop();

		return 1;
	}

	void changeSize(int w, int h) { }





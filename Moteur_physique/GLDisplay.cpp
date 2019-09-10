
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




	void GLDisplay::AddRect3D(Vecteur3D position, float width, float height, float depth) {
		Shape* cube = new Rect3D(&position, width, height, depth);
		shapes_.push_back(cube);
	}

	void GLDisplay::AddSphere(Vecteur3D position, float radius) {
		Shape* sphere = new Sphere(&position, radius);
		shapes_.push_back(sphere);
	}


	void GLDisplay::renderScene(void) {

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();

		gluLookAt(distance_*sin(phi_)*sin(teta_), distance_*cos(phi_), distance_*sin(phi_)*cos(teta_), 0, 0, 0, 0, 0, 1);

		//iterator
		std::list<Shape*>::iterator it;
		// Make iterate point to begining and incerement it one by one till it reaches the end of list.
		for (it = shapes_.begin(); it != shapes_.end(); it++)
		{
			(*it)->Draw();
		}

		glutSwapBuffers();
	}

	void GLDisplay::changeSize(int width, int height) {
		glViewport(0, 0, width, height);

		// Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

		// Model Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	void GLDisplay::keyPressEvent(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'r':
			AddRect3D(Vecteur3D(0, 0, 0), 5,5,2);
			break;
		case 't':
			AddRect3D(Vecteur3D(-10, -20, 0), 2,3,4);
			break;

			// Default case
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
		glEnable(GL_DEPTH_TEST);
		// register callbacks
		GLDisplay::setupInstance();
		distance_ = 10;
		phi_ = 1.359;
		teta_ = -0.979;
		// enter GLUT event processing cycle
		glutMainLoop();

		return 1;
	}

	void changeSize(int w, int h) { }





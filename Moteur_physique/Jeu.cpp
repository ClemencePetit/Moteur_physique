#include "Jeu.h"

Jeu::Jeu()
{
}


Jeu::~Jeu()
{
}

void Jeu::handleKeypress(unsigned char key, int x, int y)
{
	Particule* pa;
	switch (key)
	{
	case 'a':
		//delete(currentPart_);
		//currentPart_ = new Particule(g_, Vecteur3D(0, 0, 0), Vecteur3D(0, 50, 50), 100.0, 0.5, 0.0, 1.0, 0.0)
		pa = new Particule(g_, Vecteur3D(0, 0, 0), Vecteur3D(0, 50, 50), 100.0, 0.5, 0.0, 1.0, 0.0);
		pa->setShape(new Sphere(&pa->getPos(), 2));
		addParticle(pa);
		break;
	case 'r':/*
		delete(currentPart_);
		currentPart_ = new Particule(g_, Vecteur3D(0, 0, 0), Vecteur3D(0, 50, 50), 5.0, 0.5, 0.0, 1.0, 0.0);*/
		pa = new Particule(g_, Vecteur3D(0, 0, 0), Vecteur3D(0, 50, 50), 5.0, 0.5, 0.0, 1.0, 0.0);
		pa->setShape(new Sphere(&pa->getPos(), 2));
		addParticle(pa);
		break;
	case 'd':
		deleteParticle(particules_.front()); //delete first elm
	}
}
void Jeu::initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7, 0.7, 0.7, 1);
}

void Jeu::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void Jeu::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::list<Particule*>::iterator it;
	//redraw all particules
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->getShape()->Draw();
		}
	}

	/*glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 50, 0, 0, 50, 0, 0, 0, 1);

	if (currentPart_ != NULL) {
		glPushMatrix();
		glColor3f(currentPart_->getR(), currentPart_->getV(), currentPart_->getB());
		glTranslatef(currentPart_->getPos().x, currentPart_->getPos().y, currentPart_->getPos().z);
		GLUquadric* quadrique = gluNewQuadric();
		gluQuadricDrawStyle(quadrique, GLU_FILL);
		gluSphere(quadrique, 2, 20, 20);
		gluDeleteQuadric(quadrique);
		glPopMatrix();
	}*/

	glutSwapBuffers();
}


void Jeu::addParticle(Particule* pa) {

	cout << "new particle" << endl;
	particules_.push_back(pa);
}

void Jeu::deleteParticle(Particule* pa) {
	particules_.remove(pa);
}

void Jeu::update(int value)
{
	//currentTime_ = time(NULL);

	//update physics for each particles

	std::list<Particule*>::iterator it;
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL) {
			Particule* pa = *it;
			pa->integrer(t_);
			pa->getPos().afficher();

			if (pa->getPos().z < 0) {
				deleteParticle(pa);
			}
		}
	}

	/*if (currentPart_ != NULL) {
		currentPart_->integrer(t_);
		currentPart_->getPos().afficher();
		if (currentPart_->getPos().z < 0) {
			delete(currentPart_);
		}
	} */
	//t_ = time(NULL) - currentTime_;

	glutPostRedisplay();
	glutTimerFunc(1000 * t_, updateCallback, 0);
}



void Jeu::execute(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Moteur Physique");
	initRendering();
	Jeu::setupInstance();
	glutTimerFunc(1000 * t_, updateCallback, 0);
	glutMainLoop();
}

//part of hotfix
void Jeu::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}
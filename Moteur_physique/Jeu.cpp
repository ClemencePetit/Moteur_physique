#include "Jeu.h"

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
	while (!particules_.empty()) {
		deleteParticle(particules_.front());
	}
}

void Jeu::handleKeypress(unsigned char key, int x, int y)
{
	Particule* pa;
	switch (key)
	{
	case 'a':

		pa = new Particule(g_, new Vecteur3D(0, 0, 0), Vecteur3D(0, 50, 50), 5000.0, 0.5, 1.0f, 0.0f, 0.0f);
		pa->setShape(new Sphere(pa->getPos(), pa->getR(), pa->getV(), pa->getB(), 2));
		addParticle(pa);

		break;

	case 'r':

		pa = new Particule(g_, new Vecteur3D(0, 0, 0), Vecteur3D(0, 20, 20), 5.0, 0.95, 0.0f, 1.0f, 0.0f);
		pa->setShape(new Sphere(pa->getPos(), pa->getR(), pa->getV(), pa->getB(), 2));
		addParticle(pa);

		break;

	case 'd':

		if (!particules_.empty()) {
			deleteParticle(particules_.front()); //delete first elem
		}

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
	glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 50, 0, 0, 50, 0, 0, 0, 1);
	
	//redraw all particules
	std::list<Particule*>::iterator it;
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->getShape()->Draw();
		}
	}

	glutSwapBuffers();
}


void Jeu::addParticle(Particule* pa) {

	cout << "new particle" << endl;
	particules_.push_back(pa);
}

void Jeu::deleteParticle(Particule* pa) {

	particules_.remove(pa);
	delete(pa);
}

void Jeu::update(int value)
{
	//currentTime_ = time(NULL);

	//update physics for each particles
	std::list<Particule*>::iterator it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {

			(*it)->integrer(t_);
			(*it)->getPos()->afficher();

			if ((*it)->getPos()->z < 0) {
				deleteParticle(*(it++));
			}
			else {
				it++;
			}
		}
	}
	
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
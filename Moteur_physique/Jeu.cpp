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
	Vecteur3D pos = *reticule_->getPos();
	switch (key)
	{
	case 'a':

		addParticle(getProjectile1(g_));

		break;

	case 'z':

		addParticle(getProjectile2(g_));

		break;

	case 'e':

		addParticle(getProjectile3(g_));

		break;

	case 'r':

		addParticle(getProjectile4(g_));

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

	screenWidth = w;
	screenHeight = h;
}

void Jeu::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 100, 60, 
				0, 100, 60,
				0, 0, 1);
	
	//redraw all particules
	std::list<Particule*>::iterator it;
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->getShape()->Draw();
		}
	}

	reticule_->getShape()->Draw();

	//Draw power line
	float lineLenght = lerp01(1.f, 3.f, currentShotPower / maxShotPower);
	drawLine((*reticule_->getPos()), (*reticule_->getPos()) * lineLenght);

	glutSwapBuffers();
}


void Jeu::drawLine(Vecteur3D a, Vecteur3D b) {

	glPushMatrix();

	glColor3f(1, 0, 0);

	glBegin(GL_LINES);
	glVertex3f(2.f, a.y, a.z);
	glVertex3f(2.f, b.y, b.z);
	glEnd();

	glPopMatrix();
}

void Jeu::handlePassiveMouseMotion(int x, int y) {

	//move reticle toward mouse

	Vecteur3D mouseDirection2D = Vecteur3D(0, x, screenHeight - y);
	//mouseDirection2D.afficher();

	Vecteur3D normalizedDirection = mouseDirection2D.normalized();

	Vecteur3D* pos = reticule_->getPos();
	*pos = normalizedDirection * 5.f;

	//drawScene();
}

void Jeu::handleMouseClick(int button, int state, int x, int y) {

	Particule* pa = NULL;

	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {

				pa = getCurrentParticle();
				cout << "Tir! (Power =" << currentShotPower << ")" <<endl;
				pa->setPos(*reticule_->getPos());
				pa->setVit(reticule_->getPos()->normalized() * baseVelocity_ * currentShotPower);
				addParticle(pa);

				//reset charge values
				currentShotPower = minShotPower;
				currentLoadTime = 0.f;

				isLeftMouseButtonDown = false;
			}
			else if (state == GLUT_DOWN) {

				isLeftMouseButtonDown = true;
				//load shot
			}
		break;

		case GLUT_RIGHT_BUTTON:

			if (state == GLUT_DOWN) {

				cout << "Changement de Particule!" << endl;

				indexCurrentParticle_++;
				indexCurrentParticle_ %= 4; //4 = nb type de projectiles

				updateReticleWithParticle(getCurrentParticle());
				drawScene();
			}

		break;
	}
}

Particule* Jeu::getCurrentParticle() {

	Vecteur3D pos = *reticule_->getPos();
	switch (indexCurrentParticle_) {
		case 0:
			return getProjectile1(g_);
		break;
		case 1:
			return getProjectile2(g_);
			break;
		case 2:
			return getProjectile3(g_);
			break;
		case 3:
			return getProjectile4(g_);
			break;
	}

	cout << "Erreur : Index trop grand. Renvoyé particule par défaut" << endl;
	return getProjectile1(g_);
}

void Jeu::updateReticleWithParticle(Particule* pa) {

	Vecteur3D tempPos = *reticule_->getPos();

	delete(reticule_);
	reticule_ = pa;

	//no movement
	pa->setG(Vecteur3D());
	pa->setVit(Vecteur3D());
	pa->setPos(tempPos);

}

void Jeu::addParticle(Particule* pa) {

	cout << "new particle" << endl;
	particules_.push_back(pa);
}

void Jeu::deleteParticle(Particule* pa) {

	particules_.remove(pa);
	delete(pa);
}

float Jeu::lerp01(float a, float b, float t) {

	return a + t * (b - a);
}
void Jeu::update(int value)
{
	//currentTime_ = time(NULL);

	//update physics for each particles
	std::list<Particule*>::iterator it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {

			(*it)->integrer(t_);
			//(*it)->getPos()->afficher();

			if ((*it)->getPos()->z < 0) {
				deleteParticle(*(it++));
			}
			else {
				it++;
			}
		}
	}

	//load shot
	if (isLeftMouseButtonDown) {

		//current power
		currentShotPower = lerp01(minShotPower, maxShotPower, currentLoadTime / timeLoadMaxShot);

		currentLoadTime += t_;

		if (currentLoadTime >= timeLoadMaxShot) {
			currentLoadTime = 0.f;
		}
	}
	
	//t_ = time(NULL) - currentTime_;

	glutPostRedisplay();
	glutTimerFunc(1000 * t_, updateCallback, 0);
}



void Jeu::execute(int argc, char** argv)
{
	reticule_ = new Particule(0.f, &Vecteur3D(), Vecteur3D(), 0.f, 0.f);
	reticule_->setShape(new Sphere(reticule_->getPos(), 0.f, 1.f, 0.f, 2));

	updateReticleWithParticle(getProjectile1(0.f));

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

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
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
}
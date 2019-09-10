#include "Jeu.h"

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
	//suppression de toutes les particules
	while (!particules_.empty()) {
		deleteParticle(particules_.front());
	}
}


void Jeu::initRendering()//initialisation de l'affichage
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
}

void Jeu::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);

	screenWidth = w;
	screenHeight = h;
}

void Jeu::drawScene()
{
	//mise a zéro de l'affichage
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(50, -50, 5, 0, 100, 15, 0, 0, 1);

	//dessin du sol
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);
	glVertex3f(-200, -100, 0);
	glVertex3f(200, -100, 0);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(200, 400, 0);
	glVertex3f(-200, 400, 0);

	glEnd();
	
	//redraw all particules
	std::list<Particule*>::iterator it;
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->getShape()->Draw();
		}
	}

	crosshair_->getShape()->Draw();

	//Draw power line
	float lineLenght = lerp01(1.f, 3.f, currentShotPower / maxShotPower);
	drawLine((*crosshair_->getPos()), (*crosshair_->getPos()) * lineLenght);

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

	Vecteur3D normalizedDirection = mouseDirection2D.normalized();

	Vecteur3D* pos = crosshair_->getPos();
	*pos = normalizedDirection * 5.f;
}

void Jeu::handleMouseClick(int button, int state, int x, int y) {

	Particule* pa = NULL;

	switch (button) {
		//gestion du tir/chargement du tir
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {

				pa = getCurrentParticle();
				pa->setPos(*crosshair_->getPos());
				pa->setVit(crosshair_->getPos()->normalized() * baseVelocity_ * currentShotPower);
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

		//gestion du changement de la particule
		case GLUT_RIGHT_BUTTON:

			if (state == GLUT_DOWN) {


				indexCurrentParticle_++;
				indexCurrentParticle_ %= 4; //4 = nb projectile types

				updateReticleWithParticle(getCurrentParticle());
				drawScene();
			}

		break;
	}
}

Particule* Jeu::getCurrentParticle() {

	Vecteur3D pos = *crosshair_->getPos();
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

	return getProjectile1(g_);
}

//changement de la particule servant à la visée
void Jeu::updateReticleWithParticle(Particule* pa) {

	Vecteur3D tempPos = *crosshair_->getPos();

	delete(crosshair_);
	crosshair_ = pa;

	//no movement
	pa->setG(Vecteur3D());
	pa->setVit(Vecteur3D());
	pa->setPos(tempPos);

}

void Jeu::addParticle(Particule* pa) {
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
	//update physics for each particles
	std::list<Particule*>::iterator it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {

			(*it)->integrer(t_);

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

	glutPostRedisplay();
	glutTimerFunc(1000 * t_, updateCallback, 0);
}


//démarrage du jeu
void Jeu::execute(int argc, char** argv)
{
	crosshair_ = new Particule(0.f, &Vecteur3D(), Vecteur3D(), 0.f, 0.f);
	crosshair_->setShape(new Sphere(crosshair_->getPos(), 0.f, 1.f, 0.f, 2));

	updateReticleWithParticle(getProjectile1(0.f));

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Physics Engine");
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
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
}
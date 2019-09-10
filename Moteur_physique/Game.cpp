#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	while (!particules_.empty()) {
		deleteParticle(particules_.front());
	}
}

void Game::handleKeypress(unsigned char key, int x, int y)
{
	Vector3D pos = *crosshair_->getPos();
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
void Game::initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7, 0.7, 0.7, 1);
}

void Game::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

	screenWidth = w;
	screenHeight = h;
}

void Game::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7, 0.7, 0.7, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 100, 60, 
				0, 100, 60,
				0, 0, 1);
	
	//redraw all particules
	std::list<Particle*>::iterator it;
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


void Game::drawLine(Vector3D a, Vector3D b) {

	glPushMatrix();

	glColor3f(1, 0, 0);

	glBegin(GL_LINES);
	glVertex3f(2.f, a.y, a.z);
	glVertex3f(2.f, b.y, b.z);
	glEnd();

	glPopMatrix();
}

void Game::handlePassiveMouseMotion(int x, int y) {

	//move reticle toward mouse

	Vector3D mouseDirection2D = Vector3D(0, x, screenHeight - y);
	//mouseDirection2D.afficher();

	Vector3D normalizedDirection = mouseDirection2D.normalized();

	Vector3D* pos = crosshair_->getPos();
	*pos = normalizedDirection * 5.f;

	//drawScene();
}

void Game::handleMouseClick(int button, int state, int x, int y) {

	Particle* pa = NULL;

	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {

				pa = getCurrentParticle();
				cout << "Tir! (Power =" << currentShotPower << ")" <<endl;
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

		case GLUT_RIGHT_BUTTON:

			if (state == GLUT_DOWN) {

				cout << "Changement de Particule!" << endl;

				indexCurrentParticle_++;
				indexCurrentParticle_ %= 4; //4 = projectile type

				updateReticleWithParticle(getCurrentParticle());
				drawScene();
			}

		break;
	}
}

Particle* Game::getCurrentParticle() {

	Vector3D pos = *crosshair_->getPos();
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

	cout << "Error : Index out of range. Default particle selected." << endl;
	return getProjectile1(g_);
}

void Game::updateReticleWithParticle(Particle* pa) {

	Vector3D tempPos = *crosshair_->getPos();

	delete(crosshair_);
	crosshair_ = pa;

	//no movement
	pa->setG(Vector3D());
	pa->setVit(Vector3D());
	pa->setPos(tempPos);

}

void Game::addParticle(Particle* pa) {

	cout << "new particle" << endl;
	particules_.push_back(pa);
}

void Game::deleteParticle(Particle* pa) {

	particules_.remove(pa);
	delete(pa);
}

float Game::lerp01(float a, float b, float t) {

	return a + t * (b - a);
}
void Game::update(int value)
{
	//currentTime_ = time(NULL);

	//update physics for each particles
	std::list<Particle*>::iterator it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {

			(*it)->integrer(t_);
			//(*it)->getPos()->display();

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



void Game::execute(int argc, char** argv)
{
	crosshair_ = new Particle(0.f, &Vector3D(), Vector3D(), 0.f, 0.f);
	crosshair_->setShape(new Sphere(crosshair_->getPos(), 0.f, 1.f, 0.f, 2));

	updateReticleWithParticle(getProjectile1(0.f));

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Physics Engine");
	initRendering();
	Game::setupInstance();
	glutTimerFunc(1000 * t_, updateCallback, 0);
	glutMainLoop();
}

//part of hotfix
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
}
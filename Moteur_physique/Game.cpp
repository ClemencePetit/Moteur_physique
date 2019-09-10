#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	//suppression de toutes les particules
	while (!particules_.empty()) {
		deleteParticle(particules_.front());
	}
}

#pragma region Public Methods : Glut Callbacks


void Game::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);

	screenWidth = w;
	screenHeight = h;
}

void Game::handlePassiveMouseMotion(int x, int y) {

	//move reticle toward mouse

	Vector3D mouseDirection2D = Vector3D(0, x, screenHeight - y);

	Vector3D normalizedDirection = mouseDirection2D.normalized();

	Vector3D* pos = crosshair_->getPos();
	*pos = normalizedDirection * 5.f;
}

void Game::handleMouseClick(int button, int state, int x, int y) {

	Particle* pa = NULL;

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

void Game::drawScene()
{
	//mise a zéro de l'affichage
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx_, posy_, posz_, lookx_, looky_, lookz_, 0, 0, 1);

	//dessin du sol
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);
	glVertex3f(-200, -100, 0);
	glVertex3f(200, -100, 0);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(200, 400, 0);
	glVertex3f(-200, 400, 0);

	glEnd();

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

// Boucle d'update maintenant à jour les particules. 
void Game::update(int value)
{
	//update physics for each particles
	std::list<Particle*>::iterator it = particules_.begin();
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

	//Charge le tir
	if (isLeftMouseButtonDown) {

		//Puissance actuelle en fonction du temps de charge
		currentShotPower = lerp01(minShotPower, maxShotPower, currentLoadTime / timeLoadMaxShot);

		currentLoadTime += t_;

		//Si puissance max atteinte, retour à 0.
		if (currentLoadTime >= timeLoadMaxShot) {
			currentLoadTime = 0.f;
		}
	}


	glutPostRedisplay();
	glutTimerFunc(1000 * t_, updateCallback, 0);
}

#pragma endregion


//Trace une ligne entre a et b.
void Game::drawLine(Vector3D a, Vector3D b) {

	glPushMatrix();

	glColor3f(1, 0, 0);

	glBegin(GL_LINES);
	glVertex3f(2.f, a.y, a.z);
	glVertex3f(2.f, b.y, b.z);
	glEnd();

	glPopMatrix();
}
//part of hotfix
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
}


void Game::initRendering()//initialisation de l'affichage
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
}

#pragma region Gestion Particules

//Retourne un exemplaire du type de projectile actuellement sélectionné.
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
	return getProjectile1(g_);
}

//Change le type de particule utilisé par le réticule de visée
void Game::updateReticleWithParticle(Particle* pa) {

	Vector3D tempPos = *crosshair_->getPos();

	delete(crosshair_);
	crosshair_ = pa;

	//no movement
	pa->setG(Vector3D());
	pa->setVit(Vector3D());
	pa->setPos(tempPos);

}

//Ajoute la particule à la simulation
void Game::addParticle(Particle* pa) {
	particules_.push_back(pa);
}

//Supprime la particule de la simulation
void Game::deleteParticle(Particle* pa) {

	particules_.remove(pa);
	delete(pa);
}
#pragma endregion

//Interpolation linéaire entre entre A et B avec t dans [0,1]
float Game::lerp01(float a, float b, float t) {

	return a + t * (b - a);
}

void Game::handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':

		if (posx_ == 50)
		{
			posx_ = 200;
			posy_ = 100;
			posz_ = 10;
			lookx_ = -200;
			looky_ = 100;
			lookz_ = 10;
		}
		else
		{
			posx_ = 50;
			posy_ = -50;
			posz_ = 5;
			lookx_ = 0;
			looky_ = 100;
			lookz_ = 15;
		}

		break;

	default:
		break;

	}
}

//démarrage du jeu
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
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}
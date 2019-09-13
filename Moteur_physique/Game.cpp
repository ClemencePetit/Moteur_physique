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

#pragma region Public Methods 

#pragma region Glut Callbacks

void Game::handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':

		if (posCamera_.x == 50.f)
		{
			posCamera_ = Vector3D(200.0f, 100.f, 40.f);
			lookCamera_ = Vector3D(-200.f, 100.f, 40.f);
		}
		else
		{

			posCamera_ = Vector3D(50.0f, -50.f, 5.f);
			lookCamera_ = Vector3D(0.f, 100.f, 15.f);
		}

		break;

	default:
		break;

	}
}

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

				changeCrosshairWithParticle(getCurrentParticle());
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
	gluLookAt(posCamera_.x, posCamera_.y, posCamera_.z, 
		lookCamera_.x, lookCamera_.y, lookCamera_.z, 
		0, 0, 1);

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

#pragma endregion

// Boucle d'update maintenant à jour les particules et d'autres valeurs. 
void Game::update(int value)
{
	startTime = stopTime;
	stopTime = clock();
	elapsedTime= (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
	elapsedTime = elapsedTime / 1000;
	//update physics for each particles
	std::list<Particle*>::iterator it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {
			(*it)->integrer(elapsedTime);
			cout <<elapsedTime << endl;
			//(*it)->integrer(t_);
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

		currentLoadTime += elapsedTime;

		//Si puissance max atteinte, retour à 0.
		if (currentLoadTime >= timeLoadMaxShot) {
			currentLoadTime = 0.f;
		}
	}


	glutPostRedisplay();
	glutTimerFunc(1000 * elapsedTime, updateCallback, 0);
}

//démarrage du jeu
void Game::execute(int argc, char** argv)
{
	crosshair_ = new Particle(0.f, &Vector3D(), Vector3D(), 0.f, 0.f);
	crosshair_->setShape(new Sphere(crosshair_->getPos(), 0.f, 1.f, 0.f, 2));

	changeCrosshairWithParticle(getBasicBall(0.f));

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Physics Engine");
	initRendering();
	Game::setupInstance();
	glutTimerFunc(1000 * elapsedTime, updateCallback, 0);
	glutMainLoop();
}

#pragma endregion


#pragma region Private  Methods 


#pragma region Glut

void Game::initRendering()//initialisation de l'affichage
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
}

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

#pragma endregion

#pragma region Gestion Particules

//Retourne un exemplaire du type de projectile actuellement sélectionné.
Particle* Game::getCurrentParticle() {

	Vector3D pos = *crosshair_->getPos();
	switch (indexCurrentParticle_) {
		case 0:
			return getBasicBall(g_);
		break;
		case 1:
			return getCannonBall(g_);
			break;
		case 2:
			return getLaser(g_);
			break;
		case 3:
			return getSnowflake(g_);
			break;
	}
	return getBasicBall(g_);
}

//Change le type de particule utilisé par le réticule de visée
void Game::changeCrosshairWithParticle(Particle* pa) {

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

//part of hotfix
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}


#pragma endregion
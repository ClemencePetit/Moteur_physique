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
	while (!particulesGroups_.empty()) {
		deleteParticleGroup(particulesGroups_.front());
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
		else if (posCamera_.x == 500.0f)
		{
			posCamera_ = Vector3D(50.0f, -50.f, 5.f);
			lookCamera_ = Vector3D(0.f, 100.f, 15.f);
		}
		else if (posCamera_.x == 200.f)
		{
			posCamera_ = Vector3D(500.0f, 100.f, 0.f);
			lookCamera_ = Vector3D(0.f, 100.f, 0.f);
		}
		break;

	case 'v':
		seeInWater_ = !seeInWater_;
		break;

	case 'o':
		addParticle(factory_.getTestWater());
		break;

	case 'd':
		while (!particules_.empty()) {
			deleteParticle(particules_.front());
		}
		while (!particulesGroups_.empty()) {
			deleteParticleGroup(particulesGroups_.front());
		}
		break;

	//ESCAPE key
	case 27:
		exit(0);
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

	Vector3D mouseDirection2D = Vector3D(0.0f, (float)x, (float)(screenHeight - y));
	
	mousePos = mouseDirection2D; //he he he

	Vector3D normalizedDirection = mouseDirection2D.normalized();

	Vector3D* pos = crosshair_->getPos();
	*pos = normalizedDirection * 5.f;
}

void Game::handleMouseClick(int button, int state, int x, int y) {

	IParticle* pa = NULL;

	switch (button) {
		//gestion du tir/chargement du tir
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {

				//TIREZ!

				pa = factory_.getCurrentProjectile();
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

				changeCrosshairWithParticle(factory_.nextProjectile());
				drawScene();
			}

		break;
	}
}

void Game::drawGround() {

	//dessin du sol
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.47f, 0.f);
	//derriere
	glVertex3f(-200, -100, -5);
	glVertex3f(-200, 100, -5);
	glVertex3f(-200, 100, 0);
	glVertex3f(-200, -100, 0);
	//devant
	glVertex3f(200, -100, -5);
	glVertex3f(200, 100, -5);
	glVertex3f(200, 100, 0);
	glVertex3f(200, -100, 0);
	//gauche
	glVertex3f(200, -100, -5);
	glVertex3f(200, -100, 0);
	glVertex3f(-200, -100, 0);
	glVertex3f(-200, -100, -5);
	//droite
	glVertex3f(200, 100, -5);
	glVertex3f(200, 100, 0);
	glVertex3f(-200, 100, 0);
	glVertex3f(-200, 100, -5);
	//haut
	glVertex3f(-200, -100, 0);
	glVertex3f(200, -100, 0);
	glVertex3f(200, 100, 0);
	glVertex3f(-200, 100, 0);
	//bas
	glVertex3f(-200, -100, -5);
	glVertex3f(200, -100, -5);
	glVertex3f(200, 100, -5);
	glVertex3f(-200, 100, -5);
	glEnd();
}

void Game::drawPool() {

	//dessin de la piscine
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.86f, 1.f);
	//derriere
	glVertex3f(-200, 100, -50);
	glVertex3f(-200, 300, -50);
	glVertex3f(-200, 300, 0);
	glVertex3f(-200, 100, 0);
	if (!seeInWater_) {
		//devant
		glVertex3f(200, 100, -50);
		glVertex3f(200, 300, -50);
		glVertex3f(200, 300, 0);
		glVertex3f(200, 100, 0);
		//haut
		glVertex3f(-200, 100, 0);
		glVertex3f(-200, 300, 0);
		glVertex3f(200, 300, 0);
		glVertex3f(200, 100, 0);
	}
	//bas
	glVertex3f(-200, 100, -50);
	glVertex3f(-200, 300, -50);
	glVertex3f(200, 300, -50);
	glVertex3f(200, 100, -50);
	//gauche
	glVertex3f(200, 100, -50);
	glVertex3f(-200, 100, -50);
	glVertex3f(-200, 100, 0);
	glVertex3f(200, 100, 0);
	//droite
	glVertex3f(200, 300, -50);
	glVertex3f(-200, 300, -50);
	glVertex3f(-200, 300, 0);
	glVertex3f(200, 300, 0);
	glEnd();
}

void Game::drawParticles() {
	//redraw all particules
	std::list<Particle*>::iterator it;
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if (*it != NULL && (*it)->getShape() != NULL) {
			(*it)->draw();
		}
	}
}

void Game::drawGroupParticles() {
	//redraw all link between grouped particles
	std::list<ParticleGroup*>::iterator it;
	for (it = particulesGroups_.begin(); it != particulesGroups_.end(); it++)
	{
		if (*it != NULL) {
			(*it)->DrawLinks();
		}
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
	
	drawGround();
	drawPool();
	drawParticles();
	drawGroupParticles();
	crosshair_->draw();

	//Draw power line
	float lineLenght = lerp01(1.f, 3.f, currentShotPower / maxShotPower);
	Shape::drawLine((*crosshair_->getPos()), (*crosshair_->getPos()) * lineLenght);

	glutSwapBuffers();
}

#pragma endregion

// Boucle d'update maintenant à jour les particules et d'autres valeurs.

void Game::handleRegister() {

	std::list<Particle*>::iterator it;
	std::list<ParticleGroup*>::iterator ite;

	//Register Particules
	for (it = particules_.begin(); it != particules_.end(); it++)
	{
		if ((*it)->getPos()->z <= 2 && !isInPool(*it)) {
			//register_.add(*it, new WeakSpringFG(0.1f, 0.7f));
		}
		else {
			register_.add(*it, new GravityFG(g_));
			register_.add(*it, new DragFG(k1, k2));
			if (isInPool(*it)) {
				register_.add(*it, new BuoyancyFG());
			}
		}
	}
	register_.updateForces(elapsedTime);
	register_.clear();

	//Register Group Particules
	for (ite = particulesGroups_.begin(); ite != particulesGroups_.end(); ite++)
	{
		(*ite)->updateForces(elapsedTime);
	}

}

void Game::handleCollisions() {

	int nbCollisions = 0;
	nbCollisions = testCollisions();
	contactResolver_.setIter(2 * nbCollisions);

	//.sortByAscendingVelocities();

	while (contactResolver_.limitNotReached()) {
		contactResolver_.resolveContacts(elapsedTime);
		testCollisions();
	}

	contactResolver_.limitReached();
}

int Game::testCollisions() {
	
	int iter = 0;
	
	float restit;
	float dPene;
	Vector3D n;

	std::list<Particle*>::iterator itA;
	std::list<Particle*>::iterator itB;

	for (itA = particules_.begin(); itA != particules_.end(); itA++) {
		//Collisions entre particules
		for (itB = next(itA, 1); itB != particules_.end(); itB++) {

			float distAB = (*itA)->getPos()->distanceWith(*(*itB)->getPos());

			if (distAB < 4) {
				restit = 0.95f;
				dPene = 4 - distAB;
				n = *(*itB)->getPos() - *(*itA)->getPos();
				contactResolver_.addContact(new ParticleContact(*itA, *itB, restit, dPene, n));
				iter += 1;
			}
		}


		float z = (*itA)->getPos()->z;
		//Collisions avec le sol
		if (z < 2 && !isInPool(*itA)) {
			restit = 0.50;
			dPene = 2 - z;
			n = Vector3D(0, 0, -1);
			contactResolver_.addContact(new ParticleContact(*itA, NULL, restit, dPene, n));
			iter += 1;
		}
		//Collisions avec le fond de la piscine
		else if (z < -48 && isInPool(*itA)) {
			restit = 0.50;
			dPene = -48 - z;
			n = Vector3D(0, 0, -1);
			contactResolver_.addContact(new ParticleContact(*itA, NULL, restit, dPene, n));
			iter += 1;
		}
	}
	
	return iter;
}

void Game::updateAndDelete() {

	std::list<Particle*>::iterator it;
	std::list<ParticleGroup*>::iterator ite;

	//update physics for each particles
	it = particules_.begin();
	while (it != particules_.end()) {
		if (*it != NULL) {
			(*it)->integrer(elapsedTime);
			if ((*it)->getPos()->z < -100) {
				int indexTemp = (*it)->getIndex();
				//delete blop
				ite = particulesGroups_.begin();
				while (ite != particulesGroups_.end())
				{
					if ((*ite)->hasIndex(indexTemp)) {
						deleteParticleGroup(*ite++);
					}
					else {
						ite++;
					}
				}
				//
				deleteParticle(*it++);
			}
			else {
				it++;
			}
		}
	}
}

void Game::update(int value)
{
	//fps
	startTime = stopTime;
	stopTime = clock();
	elapsedTime = ((float)(stopTime - startTime)) / (CLOCKS_PER_SEC);

	//elapsedTime = std::fmaxf(elapsedTime, 0.000001f);

	handleRegister();
	handleCollisions();
	updateAndDelete();

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
	glutTimerFunc((unsigned int)elapsedTime * 1000, updateCallback, 0);
}

//liste d'instructions
void Game::instructions() {
	cout << "##############################################" << endl;
	cout << "# Bienvenue dans le test du moteur physique! #" << endl;
	cout << "##############################################" << endl << endl;
	cout << "Les differentes touches sont:" << endl << endl;
	cout << "Clic gauche pour tirer (il faut rester appuye pour augmenter la puissance)." << endl;
	cout << "Clic droit pour changer de type de projectile." << endl;
	cout << "Touche S pour changer la camera (3 cameras sont disponibles)." << endl;
	cout << "Touche V pour voir dans la piscine." << endl;
	cout << "Touche O pour faire apparaitre une particule directement dans la piscine." << endl;
	cout << "Touche D pour supprimer les particules." << endl;
	cout << "Touche ESCAPE pour quitter le test." << endl;
}

//démarrage du jeu
void Game::execute(int argc, char** argv)
{
	instructions();

	crosshair_ = new Particle(&Vector3D(), Vector3D(), 0.f, -1);

	changeCrosshairWithParticle(factory_.getBasicBall());

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Physics Engine");
	initRendering();
	Game::setupInstance();
	glutTimerFunc((unsigned int)elapsedTime, updateCallback, 0);
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


#pragma endregion

#pragma region Gestion Particules

//Change le type de particule utilisé par le réticule de visée
void Game::changeCrosshairWithParticle(IParticle* pa) {

	Vector3D tempPos = *crosshair_->getPos();

	delete(crosshair_);
	crosshair_ = pa;

	//no movement
	pa->setVit(Vector3D());
	pa->setPos(tempPos);

}

//Ajoute la particule à la simulation
void Game::addParticle(IParticle* pa) {

	if (Particle* ptrPq = dynamic_cast<Particle*>(pa)) {
		particules_.push_back(ptrPq);
	}
	else if (ParticleGroup* ptrPg = dynamic_cast<ParticleGroup*>(pa)) {

		for (auto const& pa : ptrPg->getParticles()) {
			particules_.push_back(pa);
		}

		particulesGroups_.push_back(ptrPg);
	}
}

//Supprime la particule de la simulation
void Game::deleteParticle(Particle* pa) {
	particules_.remove(pa);
	delete(pa);
}

void Game::deleteParticleGroup(ParticleGroup* paG) {
	particulesGroups_.remove(paG);
	delete(paG);
}

#pragma endregion

//Interpolation linéaire entre entre A et B avec t dans [0,1]
float Game::lerp01(float a, float b, float t) {

	return a + t * (b - a);
}

bool Game::isInPool(Particle* p) {
	return (p->getPos()->x > -200
		&& p->getPos()->x < 200
		&& p->getPos()->y > 100
		&& p->getPos()->y < 300
		&& p->getPos()->z > -50
		&& p->getPos()->z < 5);
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
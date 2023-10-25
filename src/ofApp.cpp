#include "ofApp.h"
#include "Forces/ParticleForceRegistry.h"
#include "Collisions/CollisionHandler.h"
#include "Forces/ParticleDeplacement.cpp"
#include "Forces/ParticleImpulse.cpp"
#include "cmath"

//--------------------------------------------------------------
void ofApp::setup() {
	// Tests
	Tests::ExecuteTests();

	// Set command text
	commandText = "Bouger le blob avec les fleches directionnelles de droite et de gauche!\nSauter avec la fleche du haut!\n\'s\' pour \'separer\' le blob! (maintenir en pour separer avec un grand nombre de particules)\n\'p\' pour faire apparaitre une particule!";

	// Setup lists
	primitives = std::list<std::pair<of3dPrimitive*, int*>>(); // display primitive on each draw()

	// Setup cam and basic primitives
	const float floorWidth = ofGetScreenWidth() * 100;
	const float floorHeight = 5;
	floor = ofBoxPrimitive(floorWidth, floorHeight, 0);
	floor.setPosition(Vector3D(0, -10).v3());

	// Colors & Text

	// Setup colors
	colors[0] = Vector3D(0, 0, 0);
	colors[1] = Vector3D(255, 255, 255);
	colors[2] = Vector3D(125, 125, 125);

	// Setup cam variables
	cameraPosition = Vector3D(0, 0, 500);
	// Pythagoras to get displayed width with fov and z of camera 	
	float fovRad = cam.getFov() * PI / 180;
	viewWidth = tan(fovRad / 2) * 2 * cameraPosition.z();
	viewHeight = viewWidth / cam.getAspectRatio();

	// Setup Physics
	forceRegistry = new ParticleForceRegistry();
	collisionHandler = new CollisionHandler();

	gravity = new ParticleGravity(Vector3D(0, -40));

	// add floor
	generateFloor(getLayout());

	// setup blob
	Particle* blobCore = new Particle(10, Vector3D(0, 40), Vector3D(), .01);
	blob = Blob(blobCore);

	int i = 0;
	int* colorMode;
	for (Particle* particle : blob.m_particles) {
		colorMode = new int(1);
		if (i == 0) {
			colorMode = new int(0);
			i++;
		}

		primitives.push_back(std::pair<of3dPrimitive*, int*>(particle, colorMode));
		particles.push_back(particle);
	}

	blobCollisionHandler = new BlobCollisionHandler(&blob);
}

//--------------------------------------------------------------
void ofApp::update() {
	fps = ofGetFrameRate();

	float duration = fps == 0 ? 0 : 1/fps;

	updateForces();
	Vector3D deltaXY = blob.getCore()->getPosition();
	//Update particles
	for (Particle* particle : particles) {
		particle->Update();
	}

	blobCollisionHandler->handleCollision(particles, forceRegistry, collisionHandler);
	collisionHandler->handleCollision(particles, duration, forceRegistry);

	deltaXY = blob.getCore()->getPosition() - deltaXY;
	Vector3D deltaPosCamBlob = Vector3D(cam.getPosition()) - blob.getCore()->getPosition();
	if (abs(deltaPosCamBlob.x()) >= viewWidth / 3) {
		cameraPosition += Vector3D(deltaXY.x());
	}
	
	if (abs(deltaPosCamBlob.y()) >= viewHeight / 4) {
		cameraPosition += Vector3D(0, deltaXY.y());
	}


	cam.setPosition(cameraPosition.v3());

}

//--------------------------------------------------------------
void ofApp::draw() {
	// begin camera job
	cam.begin();

	// display texts on screen
	drawText();

	// display primitives with correct color
	int* colorMode;
	for (std::pair<of3dPrimitive*, int*> primitive : primitives)
	{
		colorMode = primitive.second;
		ofSetColor(colors[(*colorMode)].x(), colors[(*colorMode)].y(), colors[(*colorMode)].z());

		// display primitive
		primitive.first->draw();

	}

	// end camera job
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// Default direction +x
	float deplacementNorm = 150;

	// move on arrow key press
	switch (key)
	{
	case 57358: // stride right
		break;
	case 57356: // stride left
	{
		deplacementNorm *= -1;
		break;
	}
	case 57357: // jump
	{
		blob.getCore()->addVelocity(Vector3D(0, 50));
		return;
	}
	case 's': // split blob
	{
		blob.split();
		return;
	}
	case 'p': // spawn particle
	{
		Particle* spawnedParticle = new Particle(10, blob.getCore()->getPosition() + Vector3D(40, 40), Vector3D(), .1);
		particles.push_back(spawnedParticle);
		primitives.push_back(std::pair<Particle*, int*>(spawnedParticle, new int(1)));
		return;
	}
	default:
		return;
	}

	ParticleDeplacement* movementX = new ParticleDeplacement(deplacementNorm);
	forceRegistry->add(blob.getCore(), movementX);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::drawText() {
	// Command Text
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commandText), -viewWidth / 2, viewHeight / 2);

	// Informative HUD 
	movingHud = "Framerate : " + to_string(fps) + " fps\n" + "Nb Particules du Blob : " + to_string(blob.m_particles.size()) + "\nCoordonees du blob: " + blob.getCore()->getPosition().toString();
	float camX, camY;
	camX = Vector3D(cam.getPosition()).x();
	camY = Vector3D(cam.getPosition()).y();
	ofSetColor(	255, 125, 125);
	ofDrawBitmapString(ofToString(movingHud), -viewWidth / 2 - 50 + camX, viewHeight / 2 + 50 + camY);
}

// ------------------------------------
void ofApp::updateForces() {
	float duration = ofGetFrameRate() == 0. ? 0. : 1 / ofGetFrameRate();

	blob.linkParticles(forceRegistry, collisionHandler);


	for (Particle* particle : particles)
	{
		forceRegistry->add(particle, gravity);
	}


	forceRegistry->updateForces(duration);
}

//--------------------------------------------------------------
void ofApp::generateFloor(std::list<std::pair<int*, Vector3D*>> layout) {

	Particle* floorParticle;
	int* floorMode = new int(2);

	for (std::pair<int*, Vector3D*> particlePair : layout) {
		floorParticle = new Particle((*particlePair.first), (*particlePair.second), Vector3D(), 0.);
		primitives.push_back(std::pair<of3dPrimitive*, int*>(floorParticle, floorMode));
		particles.push_back(floorParticle);
	}
}

std::list<std::pair<int*, Vector3D*>> ofApp::getLayout() {
	return std::list<std::pair<int*, Vector3D*>> (
		{
			std::pair<int*, Vector3D*>(new int(1000), new Vector3D(-2000, 0)),
			std::pair<int*, Vector3D*>(new int(1000), new Vector3D(-2000, 1000)),
			std::pair<int*, Vector3D*>(new int(300), new Vector3D(-1500, -350)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(-1400, -170)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(-1200, -150)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(-1000, -250)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(-850, -250)),
			std::pair<int*, Vector3D*>(new int(300), new Vector3D(-500, -250)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(-150, -250)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(0, -250)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(200, -150)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(400, -170)),
			std::pair<int*, Vector3D*>(new int(300), new Vector3D(500, -350)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(600, -170)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(800, -150)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(1000, -250)),
			std::pair<int*, Vector3D*>(new int(200), new Vector3D(1150, -250)),
			std::pair<int*, Vector3D*>(new int(300), new Vector3D(1500, -250)),
			std::pair<int*, Vector3D*>(new int(1000), new Vector3D(2000, 0)),
			std::pair<int*, Vector3D*>(new int(1000), new Vector3D(2000, 1000)),
		}
	);
}
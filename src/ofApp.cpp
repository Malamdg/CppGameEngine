#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<of3dPrimitive*>();

	sphere.setRadius(10);
	position = Vector3D();
	sphere.setPosition(position.v3());
	speed = Vector3D(1, 1);

	primitives.push_back(&sphere);

	// Center cam and set origin at the bottom left corner
	cam.move(Vector3D(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 1000).v3());


	std::cout << "Change de mode de tire en appuyant sur 'a', 'z', 'e', 'r', et 't' !" << std::endl;

	//Tests
	//TestsVector3D();
}

//--------------------------------------------------------------
void ofApp::update(){
	//Update Sphere
	position += speed;
	sphere.setPosition(position.v3());
	
	//Update particles
	for (Particle* particle : particles)
	{
		particle->Update();
		/*std::cout << "particle position : ( " 
			+ to_string(particle->getPosition().x) + ", "
			+ to_string(particle->getPosition().y) + ", "
			+ to_string(particle->getPosition().z) + " )"
			<< std::endl;*/
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	for (of3dPrimitive* primitive : primitives)
	{
		primitive->draw();
	}
	for (Particle* particle : particles)
	{
		int r = particle->getColor()[0];
		int g = particle->getColor()[1];
		int b = particle->getColor()[2];
		ofSetColor(r, g, b);
		particle->draw();
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'a':
	{
		mode = 0; break;
	}
	case 'z': 
	{
		mode = 1; break;
	}
	case 'e': 
	{
		mode = 2; break;
	}
	case 'r': 
	{
		mode = 3; break;
	}
	case 't': 
	{
		mode = 4; break;
	}
	default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	switch(button)
	{
		case 0 : 
		{
			Vector3D speedParticle;
			Vector3D colorParticle;
			switch (mode)
			{
			case 0 :
			{
				colorParticle = Vector3D(0, 255, 0);
				speedParticle = Vector3D(50, 50, 0);
				break;
			}
			case 1 :
			{
				colorParticle = Vector3D(255, 0, 0);
				speedParticle = Vector3D(100, 50, 0);
				break;
			}
			case 2 :
			{
				colorParticle = Vector3D(0, 0, 255);
				speedParticle = Vector3D(50, 100, 0);
				break;
			}
			case 3 :
			{
				colorParticle = Vector3D(125, 125, 125);
				speedParticle = Vector3D(100, 100, 0);
				break;
			}
			case 4 : 
			{
				int r = rand() % 256;
				int g = rand() % 256;
				int b = rand() % 256;
				colorParticle = Vector3D(r, g, b);
				speedParticle = Vector3D(r, g, 0);
				break;
			}
			default: break;
			}
			Particle* p = new Particle(10, Vector3D(), speedParticle, 10, Vector3D(0, -9.8, 0));
			p->setColor(colorParticle);
			particles.push_back(p);
			break;
		}
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::TestsVector3D()
{
	std::cout << std::endl << "===============================Tests===============================" << std::endl << std::endl;

	std::cout << std::endl << "-----------------Constructeur / Accesseurs / Mutateurs------------------" << std::endl << std::endl;
	Vector3D vecTest1 = Vector3D();
	std::cout << "Création Vector3D nul : " + vecTest1.toString() << std::endl;
	vecTest1[0] = 5;
	vecTest1[1] = 6;
	vecTest1[2] = -5;
	std::cout << "Modification du Vector3D nul en un Vector3D = (5, 6, -5) avec les mutateurs : " + vecTest1.toString() << std::endl;
	std::cout
		<< "Print du Vector3D avec accesseurs : ( "
		+ to_string(vecTest1[0]) + ", " + to_string(vecTest1[1]) + " )"
		<< std::endl;
	Vector3D vecTest2 = Vector3D(7, -4, -2.6);
	std::cout << "Création second Vector3D (7, -4, -2.6) : " + vecTest2.toString() << std::endl;

	std::cout << std::endl << "-----------------Additions / Soustractions------------------" << std::endl << std::endl;

	std::cout << "Addition des deux Vecor3D (attendu (12, 2, -7.6)) : " + (vecTest1 + vecTest2).toString() << std::endl;
	std::cout << "Soutraction des deux Vector3D (attendu (-2, 10, -2.4)) : " + (vecTest1 - vecTest2).toString() << std::endl;

	std::cout << std::endl << "-----------------Produits Scalaires------------------" << std::endl << std::endl;

	std::cout << "Produit scalaire des deux Vector3D (attendu 24) : " + to_string(vecTest1 * vecTest2) << std::endl;
	std::cout << "Produit scalaire avec un Vector3D nul (attendu 0) : " + to_string(vecTest1 * Vector3D()) << std::endl;

	std::cout << std::endl << "-----------------Normalisations------------------" << std::endl << std::endl;

	std::cout << "Norme du premier Vector3D (attendu sqrt(86)) : " + to_string(vecTest1.Norm()) << std::endl;
	std::cout << "Norme carrée du premier Vector3D (attendu 86) : " + to_string(vecTest1.Norm2()) << std::endl;
	vecTest1.Normalize();
	std::cout << "Normalisation de ce Vector3D (attendu (.539, .647, -.539) : " + vecTest1.toString() << std::endl;
	vecTest1 = Vector3D(5, 6, -5);

	std::cout << std::endl << "-----------------Produits Vectoriels------------------" << std::endl << std::endl;

	std::cout << "Produit Vectoriel des deux Vector3D (attendu ( -35.6, -22, -62)): " + (vecTest1 ^ vecTest2).toString() << std::endl;
}
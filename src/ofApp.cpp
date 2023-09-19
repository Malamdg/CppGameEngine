#include "ofApp.h"
#include "Tests.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<of3dPrimitive>();

	sphere.setRadius(50);
	position = Vector3D();
	sphere.setPosition(position.v3());
	speed = Vector3D(1, 1);

	primitives.push_back(sphere);

	Tests::ExecuteTests();

	//Tests
	/*std::cout << std::endl << "===============================Tests===============================" << std::endl << std::endl;

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

	std::cout << "Produit Vectoriel des deux Vector3D (attendu ( -35.6, -22, -62)): " + (vecTest1^vecTest2).toString() << std::endl;
	*/
}

//--------------------------------------------------------------
void ofApp::update(){
	position += speed;
	sphere.setPosition(position.v3());
}

//--------------------------------------------------------------
void ofApp::draw(){
	sphere.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for(of3dPrimitive primitive : primitives)
	{
		primitive.draw();
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

#include "ofApp.h"
#include <direct.h>
#include <stdio.h>





ofApp::ofApp(){

}

ofApp::~ofApp()
{
	//delete this->playerGroup;
}

//--------------------------------------------------------------
void ofApp::setup(){

	//"SETTINGS"
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	ofSetBackgroundColor(0, 0, 0);
	ofEnableDepthTest();
	ofDisableArbTex();
	//ofDisableAlphaBlending().


	char cCurrentPath[FILENAME_MAX];

	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cerr << "whoops, _getcwd fucked up :x" << std::endl;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	string cwd(cCurrentPath);

	string boulderTexturePath(cwd + "\\resource\\textures\\boulder.jpg");
	std::cout << boulderTexturePath << std::endl;
	boulderImage.loadImage(boulderTexturePath);

	//printf("The current working directory is %s", cCurrentPath);
	//std::cout << "The current working directory is " << cwd << std::endl;

	/*testwall.setHeight(80);
	testwall.setWidth(200);
	testwall.setDepth(20);
	testwall.setPosition(0, 40, -200);*/

	//this->grid = this->grid.buildTileGridHard(53, 34);
	//this->grid.printGridToConsole();
	this->tileGrid = tileGrid::setUpGrid(53, 34, 40);
	this->tileGrid->setWallHeight(50);
	this->tileGrid->buildLab();
	this->tileGrid->printGridToConsole();

	
	/*ground.setPosition(0, 0, 0);
	ground.setHeight(34*tilesize);
	ground.setWidth(53*tilesize);
	ground.rotate(90, 1, 0, 0);*/


	//cout << "Player starting postion: x:" <<		this->tileGrid->getTileAt(1, 1)->getCoordinateX() << " y:" <<		this->tileGrid->getTileAt(1, 1)->getCoordinateY() << endl;

	float playerStartX = this->tileGrid->getTileAt(1, 1)->getCoordinateX();
	float playerStartY = this->tileGrid->getTileAt(1, 1)->getCoordinateY();
	float playerSize = 20;


	playerPosition = ofVec3f(playerStartX, playerSize/2, -playerStartY);
	playerBall.setPosition(playerPosition);

	
	playerBall.setRadius(playerSize / 2);

	
	



	//playerBoundingBox.setPosition(playerPosition); // + ofVec3f(0, 0, -playerSize / 2)
	//playerBoundingBox.setPosition(0,0,0); // + ofVec3f(0, 0, -playerSize / 2)
	playerBoundingBox.setWidth(playerSize);
	playerBoundingBox.setHeight(playerSize);
	playerBoundingBox.setDepth(playerSize);
	playerBoundingBox.setParent(playerBall);

	camera.setPosition(0, 60, 60);
	camera.setParent(playerBall);
	//ofVec3f positionZero(0, 0, 0);
	cameraFocus = this->getCameraFocus();
	camera.lookAt(cameraFocus);

	mousePosX = ofGetWindowWidth() / 2;

	moveCamera();

}

//--------------------------------------------------------------
void ofApp::update(){

	if (!paused) {

	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofColor ground_color(255, 255, 255); //white

	ofColor wall_color(0, 255, 0); //green

	ofColor ball_color(0, 0, 255); //blue

	ofColor wireframe_color(255, 0, 0); //red

	camera.begin();

	this->tileGrid->draw();

	boulderImage.getTexture().bind();
	playerBall.draw();

	ofSetColor(wireframe_color);
	playerBoundingBox.drawWireframe();
	ofSetColor(ground_color);

	camera.end();

	this->drawFPS();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case 'w': {
		//move forward == -z
		ofVec3f ballPos = playerBall.getPosition();
		ballPos.z = ballPos.z - 1 * ballSpeed;
		playerBall.setPosition(ballPos);
		cameraFocus = this->getCameraFocus();
		//playerBall.rotate()
		break;
	}
	case 'a': {
		//move left == -x
		ofVec3f ballPos = playerBall.getPosition();
		ballPos.x = ballPos.x - 1 * ballSpeed;
		playerBall.setPosition(ballPos);
		cameraFocus = this->getCameraFocus();
		//playerBall.rotate()
		break;
	}
	case 's': {
		//move back == +z
		ofVec3f ballPos = playerBall.getPosition();
		ballPos.z = ballPos.z + 1 * ballSpeed;
		playerBall.setPosition(ballPos);
		cameraFocus = this->getCameraFocus();
		//playerBall.rotate()
		break;
	}
	case 'd': {
		//move right == +x
		ofVec3f ballPos = playerBall.getPosition();
		ballPos.x = ballPos.x + 1 * ballSpeed;
		playerBall.setPosition(ballPos);
		cameraFocus = this->getCameraFocus();
		//playerBall.rotate()
		break;
	}
	case 'p': {
		paused = !paused;
		break;
	}
	default: {
		//nothing

	}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (!paused) {
		/*
		Gedanke: Hier ist vermutlich die Stelle, an der man Mouse Sensitivity implementiert.
		Man berechnet den Unterschied zwischen alten und neuen Koordinaten und multipliziert diesen dann mit der Sens.
		H�here Sens = Schnellere Kamera.
		
		Nat�rlich w�rde dabei noch Feinschliff fehlen.
		*/
		mousePosX = x;
		mousePosY = y;

		moveCamera();
	}
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


/**************************************************************/
/**************CUSTOM METHODS**********/
/**************************************************************/

void ofApp::drawFPS() {

	if (this->fpsfont.isLoaded() == false) {
		//if (this->fpsfont.load(".\\resource\\fonts\\IMMORTAL.ttf", 10) == false) {
		if (this->fpsfont.load("C:\\Users\\Andreas\\Documents\\Visual Studio 2015\\Projects\\CGE Test Projekt\\CGE Test Projekt\\bin\\resource\\fonts\\IMMORTAL.ttf", 10) == false) {
			return;
		}
	}

	char fpsStr[255];
	sprintf(fpsStr, "fps: %f", ofGetFrameRate());
	ofColor fps_color(255, 0, 0);
	this->fpsfont.drawString(fpsStr, 20, 20);
}

void ofApp::printLabConsole(){

}

void ofApp::moveCamera(){
	//Diese Vorgehensweise ist vermutlich nicht sonderlich effizient, aber sie funktioniert

	int windowW = ofGetWindowWidth();
	int windowH = ofGetWindowHeight();
	double pixelPerDegreeX = windowW / (double)360; //PASST
	double pixelPerDegreeY = windowH / (double)180;

	cameraAngleX = mousePosX / pixelPerDegreeX; //PASST
	cameraAngleY = mousePosY / pixelPerDegreeY;

	//int roundedCameraAngle = (int)cameraAngle;
	float radiansOfDegreesX = cameraAngleX * 0.0174533;
	float radiansOfDegreesY = cameraAngleY * 0.0174533;

	double sinResult = sin(radiansOfDegreesX); //<- these functions expect radians and not degrees, i had to learn this the hard way
	double cosResult = cos(radiansOfDegreesX);

	//cotinue here for possible Y position changes, for now left alone

	float camPosX = sinResult * cameraOffsetHori *-1;
	//float camPosY = camera.getPosition().y;
	float camPosY = playerBall.getPosition().y + cameraOffsetVerti;
	float camPosZ = cosResult * cameraOffsetHori *-1;


	//cout << "camPosX: " << camPosX /*<< " camPosY: " << camPosY */<< " camPosZ: " << camPosZ << "--- worked with: sinResult: " << sinResult << " cosResult: "<< cosResult << " and a cameraAngle of: " << cameraAngleX << endl;

	camera.setPosition(camPosX, camPosY, camPosZ);
	camera.lookAt(cameraFocus);
}

ofVec3f ofApp::getCameraFocus() {

	ofVec3f cameraFocus = playerBall.getPosition();
	cameraFocus.y += cameraOffsetVerti;

	return cameraFocus;
}



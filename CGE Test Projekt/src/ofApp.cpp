#include "ofApp.h"
#include <direct.h>
#include <stdio.h>

ofApp::ofApp(){

}

ofApp::~ofApp()
{

}

void ofApp::setup(){

	/*
	 * Alle noetigen openGL/openframeworks Einstellungen
	 */
	ofSetFrameRate(60);			//FPS festlegen
	ofSetVerticalSync(false);	//VerticalSync deaktiviert
	ofBackground(0);			//Kein Hintergrund
	ofSetGlobalAmbientColor(ofColor(10.0f, 10.0f, 10.0f));	//Global Ambient Color ist ein dunkles grau
	ofEnableDepthTest();		//DepthTest (z-Buffer) aktivieren
	ofDisableArbTex();			//Erlaubt Textur-Features wie zB. mipmap
	ofEnableLighting();			//Licht aktivieren
	glShadeModel(GL_SMOOTH);	//Jedes Pixel Fragment hat eine eigene Farbberechnung 

	/*
	 * Ball-Textur laden
	 */
	char cCurrentPath[FILENAME_MAX];
	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cerr << "whoops, _getcwd fucked up :x" << std::endl;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	string cwd(cCurrentPath);
	string boulderTexturePath(cwd + "\\resource\\textures\\boulder.jpg");
	boulderImage.loadImage(boulderTexturePath);

	/*
	 * Grid erstellen
	 */
	this->tileGrid = tileGrid::setUpGrid(53, 34, 40);
	this->tileGrid->setWallHeight(50);
	this->tileGrid->buildLab();
	this->tileGrid->addLights();
	this->tileGrid->printGridToConsole();

	/*
	 * Ball inkl. Licht und Kamera erstellen
	 */
	float playerStartX = this->tileGrid->getTileAt(1, 2)->getCoordinateX();
	float playerStartY = this->tileGrid->getTileAt(1, 2)->getCoordinateY();

	playerPosition = ofVec3f(playerStartX, playerSize / 2, -playerStartY);

	playerLight.setPosition(ofVec3f(playerStartX, playerSize * 4, -playerStartY));	//Ueber dem Ball
	playerLight.setDiffuseColor(ofColor(255.0f, 255.0f, 255.0f));					//Weißes Licht
	playerLight.setSpecularColor(ofColor(255.0f, 255.0f, 255.0f));
	playerLight.setOrientation(ofVec3f(-90.0, 0.0, 0.0));							//Licht strahlt von oben nach unten
	playerLight.setSpotlight();
	playerLight.setSpotConcentration(0.5f);

	playerBoundingBox.setWidth(playerSize);
	playerBoundingBox.setHeight(playerSize);
	playerBoundingBox.setDepth(playerSize);
	playerBoundingBox.setPosition(playerPosition);

	playerBall.setRadius(playerSize / 2);

	movePlayerBall();
	camera.setParent(playerBoundingBox);
	cameraFocus = this->getCameraFocus();
	camera.lookAt(cameraFocus);
	mousePosX = ofGetWindowWidth() / 2;
	moveCamera();

}

void ofApp::update(){

	if (!paused) {

	}
}

void ofApp::draw(){

	ofVec3f playerPos = playerBoundingBox.getPosition();

	playerPos.y = playerSize*4;
	playerLight.setPosition(playerPos);

	camera.begin();

	playerLight.enable();

	this->tileGrid->draw();

	boulderImage.getTexture().bind();
	playerBall.draw();

	playerLight.disable();
	camera.end();

	this->drawFPS();
}

void ofApp::keyPressed(int key){

	if (!paused) {
		switch (key) {
		case 'w': {
			//Bewegung nach Norden == -z
			ofVec3f ballPos = playerBoundingBox.getPosition();
			ballPos.z = ballPos.z - 1 * ballSpeed;

			ofVec3f wallPos = ballPos;
			wallPos.z -= playerSize / 2;

			/*
			 * Collision Detection
			 */
			tile* t = this->tileGrid->getTileAtVector(wallPos);				//Tile, das betreten wird
			if (t != NULL && !t->getWalled()) {								//Check ob dieses Tile eine Mauer hat
				if (this->tileGrid->checkSides(wallPos, playerSize / 2, 0)) {	//Check ob der Ball andere Tiles mit Mauern beruehren wuerde
					this->tileGrid->spawnLight(t, playerSize);				//Licht aktivieren wenn noetig
					playerBoundingBox.setPosition(ballPos);
					movePlayerBall();
					cameraFocus = this->getCameraFocus();
				}
			}

			playerBall.rotate(-7.5, 1, 0, 0);
			break;
		}
		case 'a': {
			//Bewegung nach Westen == -x
			ofVec3f ballPos = playerBoundingBox.getPosition();
			ballPos.x = ballPos.x - 1 * ballSpeed;

			ofVec3f wallPos = ballPos;
			wallPos.x -= playerSize / 2;

			/*
			 * Collision Detection
			 */
			tile* t = this->tileGrid->getTileAtVector(wallPos);
			if (t != NULL && !t->getWalled()) {
				if (this->tileGrid->checkSides(wallPos, 0, playerSize / 2)) {
					this->tileGrid->spawnLight(t, playerSize);
					playerBoundingBox.setPosition(ballPos);
					movePlayerBall();
					cameraFocus = this->getCameraFocus();
				}
			}

			playerBall.rotate(7.5, 0, 0, 1);
			break;
		}
		case 's': {
			//Bewegung nach Sueden == +z
			ofVec3f ballPos = playerBoundingBox.getPosition();
			ballPos.z = ballPos.z + 1 * ballSpeed;

			ofVec3f wallPos = ballPos;
			wallPos.z += playerSize / 2;

			/*
			 * Collision Detection
			 */
			tile* t = this->tileGrid->getTileAtVector(wallPos);
			if (t != NULL && !t->getWalled()) {
				if (this->tileGrid->checkSides(wallPos, playerSize / 2, 0)) {
					this->tileGrid->spawnLight(t, playerSize);
					playerBoundingBox.setPosition(ballPos);
					movePlayerBall();
					cameraFocus = this->getCameraFocus();
				}
			}

			playerBall.rotate(7.5, 1, 0, 0);
			break;
		}
		case 'd': {
			//Bewegung nach Osten == +x
			ofVec3f ballPos = playerBoundingBox.getPosition();
			ballPos.x = ballPos.x + 1 * ballSpeed;

			ofVec3f wallPos = ballPos;
			wallPos.x += playerSize / 2;

			/*
			 * Collision Detection
			 */
			tile* t = this->tileGrid->getTileAtVector(wallPos);
			if (t != NULL && !t->getWalled()) {
				if (this->tileGrid->checkSides(wallPos, 0, playerSize / 2)) {
					this->tileGrid->spawnLight(t, playerSize);
					playerBoundingBox.setPosition(ballPos);
					movePlayerBall();
					cameraFocus = this->getCameraFocus();
				}
			}

			playerBall.rotate(-7.5, 0, 0, 1);
			break;
		}
		default: {
		}
		}
	}
	if (key == 'p') {
		paused = !paused;
	}
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){
	if (!paused) {
		/*
		Gedanke: Hier ist vermutlich die Stelle, an der man Mouse Sensitivity implementiert.
		Man berechnet den Unterschied zwischen alten und neuen Koordinaten und multipliziert diesen dann mit der Sens.
		Höhere Sens = Schnellere Kamera.
		
		Natürlich wuerde dabei noch Feinschliff fehlen.
		*/
		mousePosX = x;
		mousePosY = y;

		moveCamera();
	}
}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawFPS() {
	if (this->fpsfont.isLoaded() == false) {
		if (this->fpsfont.load("..\\resource\\fonts\\Immortal.ttf", 10) == false) {
			return;
		}
	}

	char fpsStr[255];
	sprintf(fpsStr, "fps: %f", ofGetFrameRate());
	ofColor fps_color(255, 0, 0);
	this->fpsfont.drawString(fpsStr, 20, 20);
}

void ofApp::moveCamera(){
	/*
	 * Kamera-Winkel & -Position anhand von Mausposition berechnen
	 */
	int windowW = ofGetWindowWidth();
	int windowH = ofGetWindowHeight();
	double pixelPerDegreeX = windowW / (double)360; 
	double pixelPerDegreeY = windowH / (double)180;
	cameraAngleX = mousePosX / pixelPerDegreeX; 
	cameraAngleY = mousePosY / pixelPerDegreeY;
	float radiansOfDegreesX = cameraAngleX * 0.0174533;
	float radiansOfDegreesY = cameraAngleY * 0.0174533;
	double sinResult = sin(radiansOfDegreesX); //Die folgenden Funktionen arbeiten mit Radianten, nicht mit Grad
	double cosResult = cos(radiansOfDegreesX);

	/*
	 * Kameraposition berechnet
	 */
	float camPosX = sinResult * cameraOffsetHori *-1;
	float camPosY = playerBall.getPosition().y + cameraOffsetVerti;
	float camPosZ = cosResult * cameraOffsetHori *-1;

	camera.setPosition(camPosX, camPosY, camPosZ);
	camera.lookAt(cameraFocus);		//Kamera soll den Ball ansehen
}

ofVec3f ofApp::getCameraFocus() {
	ofVec3f cameraFocus = playerBoundingBox.getPosition();
	cameraFocus.y += cameraOffsetVerti;

	return cameraFocus;
}

void ofApp::movePlayerBall() {
	playerBall.setPosition(playerBoundingBox.getPosition());
}
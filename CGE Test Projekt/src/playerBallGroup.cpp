#include "playerBallGroup.h"

playerBallGroup::playerBallGroup() {

}

playerBallGroup::playerBallGroup(float px, float py, float pz, float radius = 40) {
	//Self
	ofVec3f ballPosition(px, py, pz);
	this->setPosition(ballPosition);
	//Ball
	this->playerBall.setParent(*this);
	this->ballRadius = radius;
	this->playerBall.setRadius(this->ballRadius);
	
	//this->playerBall...... texture things

	/*//Camera
	this->playerCamera.setParent(*this);
	ofVec3f cameraOffset(0, 30, 30);
	ofVec3f cameraPosition = ballPosition - cameraOffset;
	//this->playerCamera.rotate(-30, 1, 0, 0);
	//this->playerCamera.setPosition(cameraPosition);
	this->playerCamera.setPosition(0,0,400);
	this->playerCamera.lookAt(this->playerBall);

	//Bounding Box
	ofBoxPrimitive tempBox(this->ballRadius, this->ballRadius, this->ballRadius);
	this->boundingBox = tempBox;
	this->boundingBox.setParent(*this);
	this->boundingBox.setPosition(ballPosition);*/

}

//TODO: overload constructor with vector instead of 3 points

ofCamera& playerBallGroup::getPlayerCamera() {
	return this->playerCamera;
}

ofBoxPrimitive& playerBallGroup::getBoundingBox() {
	return this->boundingBox;
}

void playerBallGroup::beginCamera() {
	this->playerCamera.begin();
}

void playerBallGroup::endCamera() {
	this->playerCamera.end();
}

void playerBallGroup::draw() {
	ofColor ball_color(255, 0, 0);
	this->playerBall.draw();
	this->boundingBox.drawWireframe();
	/*if(debug){
		this->boundingBox.drawWireframe();
	}*/
	
}
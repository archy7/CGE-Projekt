#pragma once

#include "ofMain.h"

class playerBallGroup : public ofNode{

private:
	float ballRadius;
	//Constructor
	playerBallGroup();

	//visual
	ofSpherePrimitive playerBall;
	//camera
	ofCamera playerCamera;
	//collision
	ofBoxPrimitive boundingBox;
public:
	//Constructor
	playerBallGroup(float px, float py, float pz, float ballRadius);
	//Members
	ofCamera& getPlayerCamera();
	ofBoxPrimitive& getBoundingBox();
	//Camera
	void beginCamera();
	void endCamera();
	//GFX
	void draw();
};
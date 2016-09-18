#pragma once

#include "ofMain.h"
#include "tileGrid.h"

class wall {

private:
	int startX = -1;
	int startY = -1;
	int endX = -1;
	int endY = -1;

public:
	wall(int startX, int startY, int endX, int endY);
	~wall();

	ofVec3f getPosition(float tilesize);
	int getWallLength();
	bool isWallHoricontal();
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
};
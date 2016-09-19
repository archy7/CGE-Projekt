#include "wall.h"

wall::wall(int startX, int startY, int endX, int endY){
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}

wall::~wall(){

}

ofVec3f wall::getPosition(float tilesize)
{
	float posX = (float)(this->startX + this->endX) / 2;
	float posY = (float)(this->startY + this->endY) / 2;

	ofVec3f wallPosition = ofVec3f(posX, 0, -posY);
	wallPosition *= tilesize;
	//x+tilesize/2, z-tilesize/2 damit die Mauer im Zentrum des Tiles steht
	wallPosition += ofVec3f(tilesize / 2, 0, -tilesize / 2);
	return wallPosition;
}

int wall::getWallLength(){

	float length = -1;
	float result = -1;
	length = (endX - startX + 1);
	result = length;
	length = (endY - startY + 1);

	if (length > result)
		result = length;
	
	return result;
}

bool wall::isWallHoricontal(){
	return startY == endY ? true : false;
}

int wall::getStartX() {
	return startX;
}

int wall::getEndX() {
	return endX;
}

int wall::getStartY() {
	return startY;
}

int wall::getEndY() {
	return endY;
}
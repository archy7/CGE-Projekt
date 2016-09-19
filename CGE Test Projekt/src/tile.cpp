#include "tile.h"

tile::tile(){

}

tile::tile(int posX, int posY, float tilesize, bool walled=false, int lightStatus=-1){
	this->gridPosX = posX;
	this->gridPosY = posY;
	this->tilesize = tilesize;
	this->walled = walled;
	this->lightStatus = lightStatus;

	this->positionAt(this->gridPosX, this->gridPosY);
}

void tile::positionAt(int posX, int posY){
	this->gridPosX = posX;
	this->gridPosY = posY;

	this->positionX = this->gridPosX * this->tilesize + this->tilesize / 2;
	this->positionY = this->gridPosY * this->tilesize + this->tilesize / 2;
}

bool tile::getWalled(){

	return this->walled;
}

void tile::setWalled(bool wall){
	this->walled = wall;
}

int tile::getLightStatus() {
	return this->lightStatus;
}

void tile::setLightStatus(int status) {
	this->lightStatus = status;
}

int tile::getGridPosX()
{
	return this->gridPosX;
}

int tile::getGridPosY()
{
	return this->gridPosY;
}

float tile::getCoordinateX()
{
	float getCoordinateX = this->gridPosX * tilesize + tilesize / 2;
	return getCoordinateX;
}

float tile::getCoordinateY()
{
	float getCoordinateY = this->gridPosY * tilesize + tilesize / 2;
	return getCoordinateY;
}

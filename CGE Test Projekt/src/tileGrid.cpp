#include "tileGrid.h"

#include <iostream>
#include <direct.h>

tileGrid::tileGrid(){

}

tileGrid::~tileGrid() {

	/*for (int y = 0; y < this->gridSizeY; ++y) {
		if (this->grid[y] != nullptr) {
			delete[] this->grid[y];
		}
	}

	delete[] this->grid;*/
}

/*
*	The game grid represents a grid on a purely positive coordinate system as human beings would see it,
*	with (0|0) being in the lower left corner.
*
*	2-dimensional grids in C have their (0|0) in the upper left corner and are to be read like lines in a book.
*	In order to make use of this class easy, this private Method is needed. Users of this class should be able to access tiles
*	by their grid coordinates, with (0|0) being in the lower left corner.
*
*	This comment is working with the assumption that users iterate over a C array similarly to this way, by first acessing all 
*	Y-Coordinates of their respective X-Coordinates.
*
*	for (int x = 0; x < gridSizeX; ++x) {
*		for (int y = 0; y < gridSizeY; ++y) {
*			grid[x][y] = .... //do something with it;
*		}
*	}
*		
*	
*
int tileGrid::flipXfromGridToC(int gridPosX)
{
	float median = this->gridSizeX / (float)2;

	float flipDistance = median - gridPosX;

	int cX = gridPosX + median * 2;

	return cX;
}*/

tileGrid* tileGrid::setUpGrid(int gridSizeX, int gridSizeY, float tilesize)
{
	tileGrid* returnGrid = new tileGrid();
	
	returnGrid->gridSizeX = gridSizeY; //swap these 2 values
	returnGrid->gridSizeY = gridSizeX;
	returnGrid->tilesize = tilesize;

	returnGrid->setupGround();

	returnGrid->allocateMemory();

	returnGrid->loadTextures();

	return returnGrid;
}

void tileGrid::allocateMemory() {

	this->grid = new tile**[this->gridSizeX];

	for (int x = 0; x < this->gridSizeX; ++x) {
		this->grid[x] = new tile*[this->gridSizeY];
		for (int y = 0; y < this->gridSizeY; ++y) {
			
			int gridPosX = y;
			int gridPosY = this->gridSizeX-x-1;

			this->grid[x][y] = new tile(gridPosX, gridPosY, this->tilesize, false, 0);
		}
	}

	//test
	/*std::cout << "grid x: " << this->getTileAt(0,0)->getGridPosX() << " grid y: " << this->getTileAt(0, 0)->getGridPosY()  << std::endl;
	std::cout << "grid x: " << this->getTileAt(0, 33)->getGridPosX() << " grid y: " << this->getTileAt(0, 33)->getGridPosY() << std::endl;
	std::cout << "grid x: " << this->getTileAt(52, 0)->getGridPosX() << " grid y: " << this->getTileAt(52, 0)->getGridPosY() << std::endl;
	std::cout << "grid x: " << this->getTileAt(52, 33)->getGridPosX() << " grid y: " << this->getTileAt(52, 33)->getGridPosY() << std::endl;*/
}

void tileGrid::setupGround(){

	//black magic kind of
	ofVec3f groundPosition(0,0,0);
	this->ground.setPosition(groundPosition);
	this->ground.setHeight(1);
	this->ground.setWidth(this->gridSizeY * tilesize);
	this->ground.setDepth(this->gridSizeY * tilesize);
	this->ground.move(this->gridSizeY*this->tilesize / 2, 0, -this->gridSizeX*this->tilesize / 2);
}

void tileGrid::setupWalls(){

	for (auto& wally : this->wallVec) {
		if (wally.getWallLength() > 1) {
			if (wally.isWallHoricontal()) {
				int newstart = wally.getStartX();
				int newend = wally.getStartX() + 1;
				while (newend <= wally.getEndX()) {
					wall* temp = new wall(newstart, wally.getStartY(), newend, wally.getEndY());

					ofVec3f wallPosition = temp->getPosition(tilesize);
					ofBoxPrimitive newVisualWall;
					newVisualWall.setPosition(wallPosition);

					newVisualWall.setDepth(tilesize);
					newVisualWall.setHeight(wallHeight);
					newVisualWall.setWidth(tilesize*temp->getWallLength());
					newVisualWall.move(0, wallHeight / 2, 0);

					this->visibleWallVec.push_back(newVisualWall);

					delete temp;
					if (newend == wally.getEndX())
						break;
					newstart += 2;
					newend = newstart + 1;
					if (newend == wally.getEndX() + 1) {
						newstart = wally.getEndX() - 1;
						newend = wally.getEndX();
					}
				}
			}
			else {
				int newstart = wally.getStartY();
				int newend = wally.getStartY() + 1;
				while (newend <= wally.getEndY()) {
					wall* temp = new wall(wally.getStartX(), newstart, wally.getEndX(), newend);

					ofVec3f wallPosition = temp->getPosition(tilesize);
					ofBoxPrimitive newVisualWall;
					newVisualWall.setPosition(wallPosition);

					newVisualWall.setDepth(tilesize*temp->getWallLength());
					newVisualWall.setHeight(wallHeight);
					newVisualWall.setWidth(tilesize);
					newVisualWall.move(0, wallHeight / 2, 0);

					this->visibleWallVec.push_back(newVisualWall);

					delete temp;

					if (newend == wally.getEndY())
						break;
					newstart+=2;
					newend = newstart + 1;
					if (newend == wally.getEndY() + 1) {
						newstart = wally.getEndY() - 1;
						newend = wally.getEndY();
					}
				}
			}
		}
		else {
			ofVec3f wallPosition = wally.getPosition(tilesize);
			ofBoxPrimitive newVisualWall;
			newVisualWall.setPosition(wallPosition);

			newVisualWall.setDepth(tilesize*wally.getWallLength());
			newVisualWall.setHeight(wallHeight);
			newVisualWall.setWidth(tilesize);
			newVisualWall.move(0, wallHeight / 2, 0);

			this->visibleWallVec.push_back(newVisualWall);
		}
	}
}

void tileGrid::loadTextures(){
	char cCurrentPath[FILENAME_MAX];

	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cerr << "whoops, _getcwd fucked up :x" << std::endl;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	string cwd(cCurrentPath);

	string groundTexturePath(cwd + "\\resource\\textures\\ground.jpg");
	string wallTexturePath(cwd + "\\resource\\textures\\brickwall.jpg");

	this->groundImage.loadImage(groundTexturePath);
	this->wallImage.loadImage(wallTexturePath);
	this->wallImage.getTextureReference().setTextureMinMagFilter(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MIN_FILTER);
	this->wallImage.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);
	//this->wallImage.resize(240, 240);


}

void tileGrid::buildLab(){
	//HARDCODE

	this->buildWallAt(0, 0, 0, 3);
	this->buildWallAt(0, 4, 0, 7);
	this->buildWallAt(0, 8, 0, 11);
	this->buildWallAt(1, 0, 3, 0);
	this->buildWallAt(3, 1, 3, 2);
	this->buildWallAt(4, 2, 5, 2);
	this->buildWallAt(1, 5, 6, 5);
	this->buildWallAt(3, 6, 3, 6);
	this->buildWallAt(1, 11, 2, 11);
	this->buildWallAt(3, 9, 3, 15);
	this->buildWallAt(2, 15, 2, 15);
	this->buildWallAt(1, 15, 1, 20);
	this->buildWallAt(2, 20, 6, 20);
	this->buildWallAt(6, 6, 6, 15);
	this->buildWallAt(7, 9, 19, 9);
	this->buildWallAt(9, 4, 9, 8);
	this->buildWallAt(6, 0, 6, 2);
	this->buildWallAt(7, 0, 15, 0);
	this->buildWallAt(15, 1, 15, 2);
	this->buildWallAt(12, 3, 15, 3);
	this->buildWallAt(12, 4, 12, 5);
	this->buildWallAt(12, 6, 19, 6);
	this->buildWallAt(19, 4, 19, 5);
	this->buildWallAt(19, 3, 28, 3);
	this->buildWallAt(15, 10, 15, 11);
	this->buildWallAt(19, 10, 19, 11);
	this->buildWallAt(15, 12, 21, 12);
	this->buildWallAt(21, 13, 21, 15);
	this->buildWallAt(22, 6, 25, 6);
	this->buildWallAt(22, 9, 25, 9);
	this->buildWallAt(22, 7, 22, 8);
	this->buildWallAt(25, 7, 25, 8);
	this->buildWallAt(7, 15, 12, 15);
	this->buildWallAt(12, 10, 12, 14);
	this->buildWallAt(6, 19, 6, 19);
	this->buildWallAt(6, 18, 14, 18);
	this->buildWallAt(15, 15, 18, 15);
	this->buildWallAt(15, 16, 15, 20);
	this->buildWallAt(18, 16, 18, 20);
	this->buildWallAt(9, 21, 18, 21);
	this->buildWallAt(9, 22, 9, 25);
	this->buildWallAt(6, 23, 6, 25);
	this->buildWallAt(7, 23, 8, 23);
	this->buildWallAt(7, 25, 8, 25);
	this->buildWallAt(3, 21, 3, 28);
	this->buildWallAt(4, 28, 7, 28);
	this->buildWallAt(8, 28, 8, 30);
	this->buildWallAt(8, 31, 30, 31);
	this->buildWallAt(28, 4, 28, 5);
//
	this->buildWallAt(28, 6, 34, 6);
	this->buildWallAt(34, 1, 34, 5);
	this->buildWallAt(34, 0, 52, 0);
	this->buildWallAt(52, 1, 52, 16);
	this->buildWallAt(51, 16, 51, 16);
	this->buildWallAt(50, 16, 50, 21);
	this->buildWallAt(51, 21, 51, 21);
	this->buildWallAt(52, 21, 52, 30);

	this->buildWallAt(49, 30, 51, 30);
	this->buildWallAt(37, 3, 49, 3);
	this->buildWallAt(49, 4, 49, 5);
	this->buildWallAt(44, 6, 49, 6);
	this->buildWallAt(37, 4, 37, 18);
	this->buildWallAt(38, 6, 41, 6);
	this->buildWallAt(38, 9, 41, 9);
	this->buildWallAt(41, 7, 41, 8);
	this->buildWallAt(33, 12, 36, 12);
	this->buildWallAt(33, 13, 33, 14);
	this->buildWallAt(33, 15, 46, 15);
	this->buildWallAt(44, 9, 44, 11);
	this->buildWallAt(40, 12, 49, 12);
	this->buildWallAt(47, 13, 47, 23);
	this->buildWallAt(40, 24, 49, 24);
	this->buildWallAt(28, 9, 34, 9);
	this->buildWallAt(28, 10, 28, 11);
	this->buildWallAt(24, 12, 30, 12);
	this->buildWallAt(30, 13, 30, 15);
	this->buildWallAt(24, 13, 24, 20);
	this->buildWallAt(27, 13, 27, 23);
	this->buildWallAt(25, 20, 26, 20);
	this->buildWallAt(41 ,16, 41, 18);
	this->buildWallAt(38, 18, 40, 18);
	this->buildWallAt(44, 18, 44, 20);
	this->buildWallAt(37, 21, 44, 21);
	this->buildWallAt(37, 22, 37, 22);
	this->buildWallAt(33, 23, 37, 23);
	this->buildWallAt(33, 33, 52, 33);
	this->buildWallAt(33, 24, 33, 32);
	this->buildWallAt(31, 25, 32, 25);
	this->buildWallAt(49, 25, 49, 26);
	this->buildWallAt(36, 27, 49, 27);
	this->buildWallAt(46, 28, 46, 32);
	this->buildWallAt(36, 28, 36, 29);
	this->buildWallAt(43, 28, 43, 29);
	this->buildWallAt(36, 30, 43, 30);
	this->buildWallAt(28, 18, 34, 18);
	this->buildWallAt(34, 19, 34, 19);
	this->buildWallAt(30, 20, 34, 20);
	this->buildWallAt(30, 21, 30, 30);
	this->buildWallAt(21, 18, 21, 26);
	this->buildWallAt(22, 23, 24, 23);
	this->buildWallAt(22, 26, 27, 26);
	this->buildWallAt(11, 28, 16, 28);
	this->buildWallAt(12, 24, 20, 24);
	this->buildWallAt(12, 25, 13, 25);
	this->buildWallAt(16, 25, 16, 27);
	this->buildWallAt(19, 25, 19, 27);
	this->buildWallAt(27, 27, 27, 27);
	this->buildWallAt(19, 28, 27, 28);


	this->setupWalls();
}

void tileGrid::addLights() {
	//8 lights max
	this->getTileAt(3, 4)->setLightStatus(1);
	this->getTileAt(9, 2)->setLightStatus(1);
	this->getTileAt(20, 8)->setLightStatus(1);
	this->getTileAt(26, 8)->setLightStatus(1);
	this->getTileAt(36, 8)->setLightStatus(1);
	this->getTileAt(50, 8)->setLightStatus(1);
}

tile* tileGrid::getTileAt(int gridPosX, int gridPosY){

	int cCoordinateY = gridPosX;
	int cCoordinateX = this->gridSizeX - gridPosY -1;

	tile* returntile = this->grid[cCoordinateX][cCoordinateY];

	return returntile;
}




/*void tileGrid::generateHardGrid(){
	this->grid = new tile*[this->gridSizeX];

	for (int x = 0; x < this->gridSizeX; ++x) {
		this->grid[x] = new tile[gridSizeY];
	}

	//BEWARE: HARD CODE to set up first test labyrinth.

	int x = 0; int y = 0;

	
}*/

bool tileGrid::coordinateOutOfBounds(int gridPosX, int gridPosY) {
	if (gridPosX < 0 || gridPosY < 0) {
		return true;
	}

	if (gridPosX >= this->gridSizeX || gridPosY >= this->gridSizeY) {
		return true;
	}

	return false;
}

void tileGrid::printGridToConsole(){

	for (int x = 0; x < this->gridSizeX; ++x) {
		for (int y = 0; y < this->gridSizeY; ++y) {
			//if (this->getTileAt(x, y).getWalled()) {
			if (this->grid[x][y]->getWalled()) {
				std::cout << "#@";
			}
			else {
				std::cout << "  ";
			}
			
		}
		std::cout << std::endl;
	}
}

void tileGrid::setWallHeight(float wallHeight){
	this->wallHeight = wallHeight;
}

float tileGrid::getWallHeight() {
	return this->wallHeight;
}

tile* tileGrid::getTileAtVector(ofVec3f position){
	int x = floor(position.x/tilesize);
	int y = floor(position.z*-1 / tilesize);

	//std::cout << x << '-' << y <<'\n';

	if (x <= gridSizeY-1 && y <= gridSizeX-1)
		return this->getTileAt(x, y);
	else
		return NULL;
}

void tileGrid::draw(){
	ofColor white(255, 255, 255); //white
	//ofColor wall_color(0, 255, 0); //green

	ofSetColor(white);
	this->groundImage.getTexture().bind();
	this->ground.draw();


	//ofSetColor(wall_color);
	this->wallImage.getTexture().bind();
	for (auto& wall : this->visibleWallVec) {
		wall.draw();
	}
}

void tileGrid::buildWallAt(int startX, int startY, int endX, int endY){

	/*if (startX != endX && startY != endY) {
		return;
	}*/

	/*if (coordinateOutOfBounds(startX, startY)) {
		std::cout << "start coordinates out of bounds: x:" << startX << " , y: " << startY << std::endl;
		return;
	}

	if (coordinateOutOfBounds(endX, endY)) {
		std::cout << "end coordinates out of bounds: x:" << endX << " , y: " << endY << std::endl;
		return;
	}*/

	int xmod = 0;
	int ymod = 0;

	if (startX <= endX)
		xmod = 1;
	else
		xmod = -1;

	if (startY <= endY)
		ymod = 1;
	else
		ymod = -1;

	for (int x = startX; x <= endX; x += xmod) {
		for (int y = startY; y <= endY; y += ymod) {
			this->getTileAt(x, y)->setWalled(true);
		}
	}

	wall newWall = wall(startX, startY, endX, endY);
	this->wallVec.push_back(newWall);
}

/*int tileGrid::cToEuklidX(int posX){

}

int tileGrid::cToEuklidY(int posY) {

}

int tileGrid::euklidToCX(int posX) {

}

int tileGrid::euklidToCY(int posY) {

}

int cCoordinateY = gridPosX;
int cCoordinateX = this->gridSizeX - gridPosY - 1;*/
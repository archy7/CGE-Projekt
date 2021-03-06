#pragma once

#include "ofMain.h"
#include "tile.h"
#include "wall.h"

class wall;

class tileGrid {
private:
	tile*** grid = nullptr;
	int gridSizeX = -1;
	int gridSizeY = -1;
	float tilesize = -1;
	float wallHeight = -1;

	std::vector<wall> wallVec;
	std::vector<ofBoxPrimitive> visibleWallVec;

	ofPlanePrimitive ground;

	void allocateMemory();
	void setupGround();
	void setupWalls();
	void loadTextures();

	ofImage groundImage;
	ofImage wallImage;
	
	//void generateHardGrid();
	//int flipXfromGridToC(int gridPosX);
	tileGrid();

public:
	~tileGrid();
	static tileGrid* setUpGrid(int gridSizeX, int gridSizeY, float tilesize);
	//tileGrid buildTileGrid(string filename);
	void buildLab();
	tile* getTileAt(int gridPosX, int gridPosY);
	void buildWallAt(int startX, int startY, int endX, int endY);
	bool coordinateOutOfBounds(int gridPosX, int gridPosY);
	void printGridToConsole();
	void setWallHeight(float wallHeight);
	float getWallHeight();

	void draw();
	/*static int cToEuklidX(int posX);
	static int cToEuklidY(int posY);
	static int euklidToCX(int posX);
	static int euklidToCY(int posY);*/
};
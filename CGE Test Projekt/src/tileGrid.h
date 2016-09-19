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
	std::vector<ofBoxPrimitive> groundVec;

	std::vector<ofLight>lights;
	float lighttilesX[7];
	float lighttilesY[7];

	ofBoxPrimitive ground;

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
	void addLights();
	tile* getTileAt(int gridPosX, int gridPosY);
	void buildWallAt(int startX, int startY, int endX, int endY);
	bool coordinateOutOfBounds(int gridPosX, int gridPosY);
	void printGridToConsole();
	void setWallHeight(float wallHeight);
	float getWallHeight();

	tile* getTileAtVector(ofVec3f position);
	bool checkSides(ofVec3f position, float x, float z);

	void draw();
	/*static int cToEuklidX(int posX);
	static int cToEuklidY(int posY);
	static int euklidToCX(int posX);
	static int euklidToCY(int posY);*/

	void spawnLight(tile* cur, float playerSize);
};
#pragma once

class tile {
private:
	int gridPosX = -1;
	int gridPosY = -1;
	float tilesize = -1;
	bool walled = false;

	float positionX = -1;
	float positionY = -1;

	
public:
	tile();
	tile(int posX, int posY, float tilesize, bool walled);
	void positionAt(int posX, int posY);
	bool getWalled();
	void setWalled(bool wall);
	int getGridPosX();
	int getGridPosY();
	float getCoordinateX();
	float getCoordinateY();
};
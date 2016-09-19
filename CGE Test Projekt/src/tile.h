#pragma once
/*
 * header-file fuer die Definition eines "Tiles" des Spielfeldes
 * Das gesamte Spielfeld besteht aus Tiles, welche entweder leer sind oder eine Mauer besitzen
 * Andreas BRICHTA, Markus KOLLER
 */
class tile {
private:
	int gridPosX = -1;		//X-Index des Tiles
	int gridPosY = -1;		//Y-Index des Tiles
	float tilesize = -1;	//Groesse des Tiles
	bool walled = false;	//Besitzt das Tile eine Mauer?
	int lightStatus = -1;	//Aktiviert das Tile Licht? -1=NIE, 0=Hat schon aktiviert, 1-x=Id des Lichts

	float positionX = -1;	//X-Koordinate des Tiles im Raum
	float positionY = -1;	//Y-Koordinate des Tiles im Raum

	
public:
	tile();																		//Default Konstruktor
	~tile();																	//Destruktor
	tile(int posX, int posY, float tilesize, bool walled, int lightStatus);		//Konstruktor
	void positionAt(int posX, int posY);										//Berechnet positionX und positionY aus tilesize und gridPosX/Y
	bool getWalled();															
	void setWalled(bool wall);
	int getLightStatus();
	void setLightStatus(int status);
	int getGridPosX();
	int getGridPosY();
	float getCoordinateX();
	float getCoordinateY();
};
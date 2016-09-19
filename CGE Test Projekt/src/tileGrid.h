#pragma once

#include "ofMain.h"
#include "tile.h"
#include "wall.h"

class wall;
/*
 * header-file fuer das eigentliche Spielfeld
 * Hier werden alle Spielfeldinteraktionen (Tiles, Mauern, Lichter) abgehandelt und die dafuer noetigen Objekte & Variablen gespeichert
 * Das Spielfeld selbst ist ein Raster, bestehend aus Tiles
 * Andreas BRICHTA, Markus KOLLER
 */
class tileGrid {
private:
	tile*** grid = nullptr;		//Raster aus Tiles
	int gridSizeX = -1;			//Groesse(Anzahl an Tiles) des Rasters in X-Richtung
	int gridSizeY = -1;			//Groesse(Anzahl an Tiles) des Raster in Y-Richtung
	float tilesize = -1;		//Groesse(Kantenlaenge) eines einzelnen Tiles
	float wallHeight = -1;		//Hoehe der Mauern

	std::vector<wall> wallVec;						//Vector mit den Mauern
	std::vector<ofBoxPrimitive> visibleWallVec;		//Vector mit den modellierten Mauern
	std::vector<ofBoxPrimitive> groundVec;			//Vector mit den modellierten Boden-Tiles

	std::vector<ofLight>lights;	//Vector mit den Lichtern die das Spielfeld ausleuchten
	float lighttilesX[7];		//X-Koordinaten dieser Lichter
	float lighttilesY[7];		//Y-Koordinaten dieser Lichter

	void allocateMemory();		//Reserviert Speicher fuer das Raster
	void setupGround();			//Erstellt den Boden
	void setupWalls();			//Erstellt die Waende
	void loadTextures();		//Laedt Texturen

	ofImage groundImage;		//Textur fuer die Boden-Tiles
	ofImage wallImage;			//Textur fuer die Waende

	tileGrid();					//Default Konstruktor

public:
	~tileGrid();																//Destruktor
	static tileGrid* setUpGrid(int gridSizeX, int gridSizeY, float tilesize);	//Konstruktor
	void buildLab();															//Definiert Mauern
	void addLights();															//Definiert Lichter die das Spielfeld ausleuchten
	tile* getTileAt(int gridPosX, int gridPosY);								//Gibt einen Tile-Pointer auf das Tile mit bestimmten X & Y Koordinaten zurueck
	void buildWallAt(int startX, int startY, int endX, int endY);				//Baut eine Mauer
	void generateHardGrid();													//DEPRECATED - Altes buildLab()
	bool coordinateOutOfBounds(int gridPosX, int gridPosY);						//DEPRECATED - Check ob X,Y-Koordinaten im Grid vorhanden sind					
	void printGridToConsole();													//Gibt das Spielfeld in 
	void setWallHeight(float wallHeight);							
	float getWallHeight();

	tile* getTileAtVector(ofVec3f position);									//getTileAt() mit Raumkoordinaten
	bool checkSides(ofVec3f position, float x, float z);						//Colissiondetection fuer Ecken

	void draw();																//draw()-Methode, die die Elemente des Spielfelds zeichnet (wird von ofApp.draw() aufgerufen)

	void spawnLight(tile* cur, float playerSize);								//Erstellt eine neue Lichtquelle wenn cur ein Licht triggert
};
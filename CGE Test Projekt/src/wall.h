#pragma once

#include "ofMain.h"
#include "tileGrid.h"

/*
 * header-file die Definition einer Mauer
 * Wird zum Bauen einer Mauer im Spielfeld benoetigt
 * Andreas BRICHTA, Markus KOLLER
 */
class wall {

private:
	int startX = -1;		//X-Wert des Mauerbeginns
	int startY = -1;		//Y-Wert des Mauerbeginns
	int endX = -1;			//X-Wert des Mauerendes
	int endY = -1;			//Y-Wert des Mauerendes

public:
	wall(int startX, int startY, int endX, int endY);	//Konstruktor
	~wall();											//Destruktor

	ofVec3f getPosition(float tilesize);				//Gibt die Position im Raum an
	int getWallLength();
	bool isWallHoricontal();							//Gibt an ob es sich um eine horizontale Mauer handelt
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
};
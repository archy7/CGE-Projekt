#pragma once

#include "ofMain.h"
#include "tile.h"
#include "tileGrid.h"

/*
 * header-file des eigentlichen Spiels
 * Zeichnet die Szene inkl. Kamera & Licht und intepretiert User-inputs
 * Bei dem Spiel handelt es sich um ein Labyrinth, das mit einem Ball durchquert wird. Das Labyrinth ist dunkel,
 * die einzige Lichtquelle ist der Ball. An bestimmten Punkten, am richtigen Pfad zum Ziel, wird das Labyrinth rot ausgeleuchtet.
 * Andreas BRICHTA, Markus KOLLER
 */
class ofApp : public ofBaseApp{

	private:
		ofTrueTypeFont fpsfont;	//Font fuer FPS-Anzeige

		void drawFPS();			//Funktion fuer FPS-Anzeige

		//GAME LOGIC
		float ballSpeed = 4.0f;			//Geschwindigkeit mit der sich der Ball bewegt
		bool paused = false;			//Gibt an ob das Spiel pausiert ist	
		float tilesize = 20;			//Groesse eines Tiles
		tileGrid* tileGrid = nullptr;	//tileGrid

		ofSpherePrimitive playerBall;	//Kugel, die den Ball darstellt
		ofImage boulderImage;			//Textur des Balls

		ofVec3f playerPosition;			//(Start-)Position des Balls
		
		ofBoxPrimitive playerBoundingBox;	//BoundingBox des Balls

		ofLight playerLight;			//Licht, das dem Ball folgt
		
		ofCamera camera;				//Kamera, die den Ball verfolgt
		ofVec3f cameraFocus;			//Punkt, den die Kamera ansieht

		double cameraAngleX = 180;		//Kamerawinkel
		double cameraAngleY = 90;		//Kamerawinkel
		int cameraOffsetHori = 30;		//Horizontaler Abstand der Kamera zum Ball
		int cameraOffsetVerti = 10;		//Vertikaler Abstand der Kamera zum Ball
		
		int mousePosX = 0;				//x-Wert der Mausposition im Fenster
		int mousePosY = 0;				//y-Wert der Mausposition im Fenster
		float camPosX = 0;				//x-Position der Kamera in 2D(tileGrid)
		float camPosY = 0;				//x-Position der Kamera in 2D(tileGrid)

		float playerSize = 20;			//Groesse des Balls
		
		ofVec3f getCameraFocus();		//Liefert die Position, die die Kamera ansehen soll
		void moveCamera();				//Bewegt die Kamera entsprechend der Mausbewegungen
		void movePlayerBall();			//Bewegt den Ball

	public:
		ofApp();										//Default-Konstruktor
		~ofApp();										//Destruktor

		void setup();									//Stellt Startbedingungen her
		void update();									//Wird mit jedem Frame aufgerufen
		void draw();									//Zeichnet ALLES

		void keyPressed(int key);						//Reagiert auf Tastatureingaben
		void keyReleased(int key);
		void mouseMoved(int x, int y );					//Reagiert auf Mausbewegungen
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
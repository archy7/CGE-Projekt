#pragma once

#include "ofMain.h"
#include "tile.h"
#include "tileGrid.h"



class ofApp : public ofBaseApp{

	private:
		
		//FRAMERATE	
		ofTrueTypeFont fpsfont;

		void drawFPS();

		//GAME LOGIC
		float ballSpeed = 1;
		bool paused = false;
		float tilesize = 20;
		tileGrid* tileGrid = nullptr;

		void printLabConsole();


		//playerBallGroup* playerGroup = nullptr;
		ofSpherePrimitive playerBall;
		ofImage boulderImage;
		//GLUquadricObj *quadric;

		ofVec3f playerPosition;
		
		ofBoxPrimitive playerBoundingBox;
		//ofBoxPrimitive testwall;

		//GFX
		//ofBoxPrimitive box;
		//ofPlanePrimitive ground;


		//CAMERA
		ofCamera camera;
		ofVec3f cameraFocus;

		double cameraAngleX = 180;
		double cameraAngleY = 90;
		int cameraOffsetHori = 60;
		int cameraOffsetVerti = 20;
		
		int mousePosX = 0;
		int mousePosY = 0;
		float camPosX = 0;
		float camPosY = 0;
		
		ofVec3f getCameraFocus();
		void moveCamera();
		

	public:
		ofApp();
		~ofApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};
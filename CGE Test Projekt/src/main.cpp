#include "ofMain.h"
#include "ofApp.h"

/*
 * main-Methode des Programms
 * setzt die Fenstergröße und startet das Spiel
 * Andreas BRICHTA, Markus KOLLER
 */
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

#include "ofMain.h"
#include "ofApp.h"

/*
 * main-Methode des Programms
 * Setzt die Fenstergröße und startet das Spiel
 * Andreas BRICHTA, Markus KOLLER
 */
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);
	ofRunApp(new ofApp());
}

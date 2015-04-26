#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "Pelo.h"
#include "creatureCreation.h"
#include "audioFeature.h"

class ofApp : public ofxiOSApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        ///Screen Stuff
        int touchposx = 1;
        int touchposy = 1;
        int screenHeight;
        int screenWidth;
    
        //input
        bool playerPress = false;
        creatureCreation creature;
        audioFeature audio;
    
        int cuantos;
        int hairs = 0;
        
        vector<float> z;
        vector<float> phi;
        vector<float> largos;
        vector<Pelo> lista;
        float radio;
        float tempRADIO;
        float rx;
        float ry;
        float rz;

};



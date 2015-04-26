#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class audioFeature : public ofBaseApp{
	
    public:
    void setup();
    void update();
    void draw();
    
    void stateChange();
    void touchInput(string touchInput);
    
    void setBrightness(int x);

    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
	
	int		bufferSize;
	int		sampleRate;
	
    
    /* stick you maximilian declarations below
     
     For information on how maximilian works, take a look at the example code at
     
     http://www.maximilian.strangeloop.co.uk
     
     under 'Tutorials'.
     
     
     */

	
	ofxMaxiOsc myOsc1;
	ofxMaxiSample sample1;
	double patch1,sample,outputs1[2];
	ofxMaxiMix channel1;
    
    int soundType = -1;
    //sound one
    int squareSine;
    int startPhase;
    int endPhase;
    int phaseFreq;
    ///sound 2
    int sine2hz;
    int sine2hz2;
    int sine2freq;
    //etc
    
private:
    
    ofImage bg;
    float creaturefreq;

    
};



// CURRENT TO DO:
// CREATE VARIANT AUDIO STATES 

#include "audioFeature.h"
#include "creatureCreation.h"
creatureCreation creatureData;
#include <iostream>


maxiOsc mySine,mySine2,mySine3; //angry tone

maxiOsc myCounter2,mySquarewave; //creature sound 5
int CurrentCount2;

maxiOsc Sine6,Sine7,Sine8; // creature sound 6
maxiOsc Sine9,Sine10,Sine11; // creature sound 7


maxiOsc myCounter,mySwitchableOsc;
int CurrentCount;
double myOscOutput,myFilteredOutput;
double myEnvelopeData[6] = {500,10,675,450,0,450};  //creature is stable and being fed
maxiEnvelope myEnvelope;
maxiFilter myFilter;
maxiOsc myOtherSine, myPhasor; // dying tone

float creaturefreq = ofRandom(1, 100);

//--------------------------------------------------------------
//--------------------------------------------------------------
void audioFeature::setup()
{
    sampleRate 	= 44100; /* Sampling Rate */
    /*
     8000  = 20-22 FPS @ 256, sounds okay
     16000  = 20 FPS @ 256, sounds too harsh
     32000 = 20 FPS @ 256, like a alarm
     44100 = 19-20 FPS stable @ 256, sounds strange
     48000 = 17-19 FPS stable @ 512, sounds good compared to others
     */
	bufferSize	= 256;
    /* 
     64  = 20 FPS @ 8000
     128 = 20 FPS @ 8000
     256 = 22-24 FPS @ 8000
     512 = 20-21 FPS stable @ 8000
     */
    
    //bg.loadImage("images/bgtest.png");
    //bg.resize(ofGetWidth(), ofGetHeight());
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
}

//--------------------------------------------------------------
//--------------------------------------------------------------
/*
void audioFeature::setBrightness(int x)
{
    // use system time to affect luminosity / brightnss >> tie of day correspond to saturation or luminosity
    // of image
    
   // ofGetSystemTime();
    //std::cout << ofGetSystemTime() << '\n';
    
    
    unsigned char * pix = bg.getPixels();
    
    for(int i = 0; i < bg.width * bg.height; i++)
        {
            if(pix[i] == 0)
            {
                while(pix[i]<x)
                {
                    pix[i] += 1;
                }
            }
        }
        bg.update();
}
*/
//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::update()
{

}

//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::draw(){
	
    /* You can use any of the data from audio received and audiorequested to draw stuff here.
	 Importantly, most people just use the input and output arrays defined above.
	 Clever people don't do this. This bit of code shows that by default, each signal is going to flip
	 between -1 and 1. You need to account for this somehow. Get the absolute value for example.
	 */
    
    //bg.draw(0,0);
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++){
        ///moods
        //creatureMood[x];
        //0=happy, 1=sad, 2=unhappy, 3= angry, 4=hungry, 5=seed (not used).
        
        if (playerInput[0] > playerInput[1]){// happy output
            outputs1[0]=Sine6.triangle(creaturefreq)*Sine8.phasor(creatureMood[0], 0.5, creatureMood[0])*Sine7.square(40); // creature Arnold
            outputs1[0] =Sine9.triangle(Sine10.phasor(growthRate,creatureMood[0],creatureColour[2]));
            
        }else if (playerInput[1] > playerInput[0]){// creature is sad
            outputs1[0]=Sine6.triangle(creaturefreq)*Sine8.phasor(creatureMood[6], creatureMood[2], 8.0)*Sine7.square(creatureMood[2]); // creature Arnold
            outputs1[0] =Sine9.triangle(Sine10.phasor(creatureMood[5],creatureColour[1],creatureColour[0]));
        
        }else if (creatureMood[4]+creatureMood[2] > creatureMood[0]+creatureMood[1]){// creature is angry
            outputs1[0]=Sine6.triangle(creaturefreq)*Sine8.phasor(creatureMood[3], 0.5, 8.0)*Sine7.square(40); // creature sound 6
            
        }else if (creatureMood[4]*10 > creatureMood[5]){// creature is hungry
            outputs1[0] =Sine9.triangle(Sine10.phasor(creatureMood[4],100,(creatureColour[1]+creatureColour[2])-creatureColour[0])); // creature sound 7
        }

        /*
        CurrentCount=myCounter.phasor(2, 1, 5);
        if (CurrentCount<5)
            myOscOutput=mySwitchableOsc.sinewave(CurrentCount*50);
        else if (CurrentCount>=5)
            myOscOutput=mySwitchableOsc.square(CurrentCount*25);
        
        if (CurrentCount == 1)
            myEnvelope.trigger(0,myEnvelopeData[0]);
        myFilteredOutput=myFilter.lores(myOscOutput,(myEnvelope.line(5,myEnvelopeData)),10);
        outputs1[0]=myFilteredOutput; // for when the creature is stable
        */
        
		output[i*nChannels    ] = outputs1[0];//left output
		output[i*nChannels + 1] = outputs1[0];//right output
		
	}
	
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::audioIn(float * input, int bufferSize, int nChannels)
{
	
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
        
        
    }
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::stateChange(){
    ///ARNOLD: Used to be keyDown or keyPressed
    
    /*
   if (key == 'g'){
        creatureState ++;
        cout << "`================" << endl;
        cout << "creatureState: " <<creatureState << endl;
       
        cout << "soundType: " <<soundType << endl;
        cout << "sine2hz: " <<sine2hz << endl;
        cout << "sine2hz2: " <<sine2hz2 << endl;
        cout << "sine2freq: " <<sine2freq << endl;
        cout << "squareSine: " <<squareSine << endl;
        cout << "startPhase: " <<startPhase << endl;
        cout << "endPhase: " <<endPhase << endl;
        cout << "phaseFreq: " <<phaseFreq << endl;
   
    }

    if(key == 'h'){
        creatureState --;
        cout << "`================" << endl;
        cout << "creatureState: " <<creatureState << endl;
        
         cout << "creatureState: " <<creatureState << endl;
         cout << "sine2hz: " <<sine2hz << endl;
         cout << "sine2hz2: " <<sine2hz2 << endl;
         cout << "sine2freq: " <<sine2freq << endl;
         cout << "squareSine: " <<squareSine << endl;
         cout << "startPhase: " <<startPhase << endl;
         cout << "endPhase: " <<endPhase << endl;
         cout << "phaseFreq: " <<phaseFreq << endl;
        
    
    }
    */
    ///moods
    //creatureMood[x];
    //0=happy, 1=sad, 2=unhappy, 3= angry, 4=hungry, 5=seed (not used).
    
    if (creatureMood[5]/playerInput[0] > creatureMood[5]/playerInput[1]){//happy

        }else if (creatureMood[5]/(playerInput[1]*2) > creatureMood[5]/playerInput[2]){// creature is dying
            squareSine = 350;
            startPhase = 4;
            endPhase = 6;
            phaseFreq = 400;
            
        }else if (creatureMood[5]/playerInput[1] > creatureMood[5]/playerInput[0]){// creature is angry
            sine2hz = 0.5;
            sine2hz2 = 24;
            sine2freq = 400;
            
        }else if (creatureMood[4]+creatureMood[2] > creatureMood[0]+creatureMood[1]){// creature is stable
            sine2hz = 1;
            sine2hz2 = 60;
            sine2freq = 80;
        }
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void audioFeature::touchInput(string touchInput){
    if(touchInput == "down"){
    if(creatureMood[0] > creatureMood[1]){
        sine2hz = 0;
        sine2hz2 = 0;
        sine2freq = 0;
        squareSine = 0;
        endPhase = 0;
        phaseFreq = 0;

    } else if(creatureMood[0] > creatureMood[1]){
        sine2hz = 0;
        sine2hz2 = 0;
        sine2freq = 0;
        
    } else if(creatureMood[1] > creatureMood[2]){
        sine2hz = 0;
        sine2hz2 = 0;
        squareSine = 0;
        startPhase = 0;
        endPhase = 0;
        
    } else if(creatureMood[2] > creatureMood[3]){
        sine2hz = 0;
        sine2hz2 = 0;
        sine2freq = 0;

    }else if(creatureMood[3] > creatureMood[4]){
        squareSine = 0;
        startPhase = 0;
        endPhase = 0;
        phaseFreq = 0;
    }
    }
}
//--------------------------------------------------------------
//--------------------------------------------------------------

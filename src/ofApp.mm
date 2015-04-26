#include "ofApp.h"
#include<iostream> //debug only

//--------------------------------------------------------------
void ofApp::setup(){
    audio.setup();
    ////////////////////////////////////////////////////////////
    //Screen setup
    ////////////////////////////////////////////////////////////
	ofSetOrientation(OF_ORIENTATION_90_RIGHT);//Set iOS to Orientation Landscape Right
	ofBackground(0,0,0);
    //ofxAccelerometer.setup();//turn on the accelerometer
    screenHeight = ofGetHeight();
    screenWidth = ofGetWidth();
    
    ////////////////////////////////////////////////////////////
    //creature setup
    ////////////////////////////////////////////////////////////
    creature.setupCreature();
    creature.loadGame();
    ////////////////////////////////////////////////////////////
    //Creature Hairs
    ////////////////////////////////////////////////////////////
    cuantos = 600; //hairs
    radio = ofGetHeight()/10;
    
    for(int i = 0; i < cuantos; i++){
        z.push_back(0.0);
        phi.push_back(0.0);
        largos.push_back(0.1);
        lista.push_back(Pelo(radio));
        
        //lista needs to be filled up with Pelos
    }
    //ofSetDepthTest(true);

}

//--------------------------------------------------------------
void ofApp::update(){
    ////////////////////////////////////////////////////////////
    //AUDIO
    ////////////////////////////////////////////////////////////
    audio.update();
    //audio.setBrightness(ofGetSystemTime());
    ////////////////////////////////////////////////////////////
    //MOOD CHANGE
    ////////////////////////////////////////////////////////////
    creature.moodOFcreature();
    creature.creatureMoodShift();
    ////////////////////////////////////////////////////////////
    //INPUT
    ////////////////////////////////////////////////////////////
    if(playerPress == true){
        //growthRate = growthRate*0.01;
        
        ///if player IS tapping the screen
        if(hold < holdMax){
            hold++;
        }
        if(happyUp == false){
            playerInput[1]++;//off
        }else{
            playerInput[0]++;//on
        }
        
        //COLOUR EFFECT ON TOUCH
        creature.colourShift();
    }
    
    if(playerPress == false){
        ///if player is NOT tapping the screen
        if (hold > 1){
            hold--;
        }
        
        if(hold < holdMax/2){
            ////////////////////////////////////////////////////////////
            //COLOUR EFFECT
            ////////////////////////////////////////////////////////////
            if(creatureColour[0]+creatureColour[1]+creatureColour[2] >= 88*2){
                creatureColour[0] -= ofRandom(0, 1);
                creatureColour[1] -= ofRandom(0, 1);
                creatureColour[2] -= ofRandom(0, 1);
            }
            if(creatureColour[0]+creatureColour[1]+creatureColour[2] > 0 &&
               creatureColour[0]+creatureColour[1]+creatureColour[2] < 144*3){
                creatureColour[0] += ofRandom(1, 5);
                creatureColour[1] += ofRandom(1, 5);
                creatureColour[2] += ofRandom(1, 5);
                
            }
        }
    
    }
    ////////////////////////////////////////////////////////////
    //EFFECTS
    ////////////////////////////////////////////////////////////
    /*
    //accelerometer
    ofVec3f accel = ofxAccelerometer.getForce();
    ofVec2f orientation = ofxAccelerometer.getOrientation()
     
    ////////////////////////////////////////////////////////////
    //Debug stuff
    ////////////////////////////////////////////////////////////
    
        cout << "==========" << endl;
        cout << "RED: " << creatureColour[0] << endl;
        cout << "BLUE: " << creatureColour[1] << endl;
        cout << "GREEN: " << creatureColour[2] << endl;
        //cout << "Radio: " << radio << endl;
        cout << "happyUp: " << happyUp << endl;
        cout << "FPS: " << ofGetFrameRate() << endl;
    */
    }

//--------------------------------------------------------------
void ofApp::exit(){
    cout << "==========" << endl;
    cout << "ofApp::exit" << endl;
    creature.saveGame();
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    touchposx = touch.x;
    touchposy = touch.y;
    playerPress = true;
    happyUp = FALSE;
    
    if(growth == false){
            //double tap to hurt, single tap to heal, hold to double last effect
            growthRate -= ofRandom(creatureMood[6]);
            audio.touchInput("down");
    }
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    touchposx = touch.x;
    touchposy = touch.y;
    happyUp = TRUE;
    
    if(growth == false){
            //double tap to hurt, single tap to heal, hold to double last effect
        growthRate += ofRandom(creatureMood[6]);
    }
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    playerPress = false;
    audio.touchInput("up");
    creature.creatureFinder(touchposx, touchposy);
    
    cout << "==========" << endl;
    cout << "ofApp::touchUp" << endl;
    creature.saveGame();

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ////////////////////////////////////////////////////////////
    //Audio draw
    ////////////////////////////////////////////////////////////
    audio.draw(); //not needed?
    ////////////////////////////////////////////////////////////
    //Creature draw
    ////////////////////////////////////////////////////////////
    ofTranslate(screenWidth/2, screenHeight/2);
    
    //float rxp = ((touchposx-(screenWidth/2))* 0.005);
    //float ryp = ((touchposy-(screenHeight/2))* 0.005);
    float rzp = atan2(touchposx, touchposy)* radio / 3.14159;
    
    //rx = (rx*0.9)+(rxp*0.1);
    //ry = (ry*0.9)+(ryp*0.1);
    rz = (rz*0.99)+(rzp*0.01);

    ofRotateY(ofRadToDeg(rz));
    ofRotateX(ofRadToDeg(rz));
    //ofRotateZ(ofRadToDeg(rz));
    
    hairLonger = true;
    ofSetColor(creatureColour[0], creatureColour[1], creatureColour[2]);
    for(int i = cuantos*0.5; i < cuantos; i++){
        lista[i].draw2(hold, radio+(growthRate*creatureMood[6]));
    }
    
    hairLonger = false; //first turn off hair longer
    ofSetColor(creatureColour[2], creatureColour[1], creatureColour[0]);///then set hair colour
    for(int i = 0; i < cuantos*0.5; i++){///loop and draw half of the hairs
        lista[i].draw((radio/2)+(growthRate*creatureMood[6]));
    }
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
}


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
    cuantos = 800; //hairs
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
    audio.setBrightness(ofGetSystemTime());
    ////////////////////////////////////////////////////////////
    //MOOD CHANGE
    ////////////////////////////////////////////////////////////
    creature.creatureMood(happyUp);
    ////////////////////////////////////////////////////////////
    //INPUT
    ////////////////////////////////////////////////////////////
    if(playerPress == true){
        ///if player IS tapping the screen
        if(hold < holdMax){
            hold++;
        }
        if(growth == false){
            if(happyUp == false){
                totalTouches -= (growthRate/hold)*0.02;
            }
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
            if(creatureColour[0]+creatureColour[1]+creatureColour[2] >= 88*3 &&
               creatureColour[0]+creatureColour[1]+creatureColour[2] <= 144*3){
                creatureColour[0] += ofRandom(0, 3);
                creatureColour[1] += ofRandom(0, 3);
                creatureColour[2] += ofRandom(0, 3);
                
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
     */
    ////////////////////////////////////////////////////////////
    //GROWTH EFFECT
    ////////////////////////////////////////////////////////////
    if(totalTouches > growthRate && radio < ofGetHeight()/4.5){
        growthRate++;
        tempRADIO = radio;
        growth = true;
    }
    
    if(growth == true){
    playerPress = false;
            if(radio < tempRADIO+(ofGetHeight()/holdMax)){
                radio++;
                growth = false;
            }///makes creature bigger
        
            if(happyUp == true){//if the creature is happy last action?
                totalTouches -= totalTouches*0.015;
                if(totalTouches < growthRate*0.9){
                    growth = false;
                }
            }
    }
     
    ////////////////////////////////////////////////////////////
    //Debug stuff
    ////////////////////////////////////////////////////////////
        /*
        cout << "==========" << endl;
        cout << "RED: " << creatureColour[0] << endl;
        cout << "BLUE: " << creatureColour[1] << endl;
        cout << "GREEN: " << creatureColour[2] << endl;
        cout << "Total Touches: " << totalTouches << endl;
        cout << "Radio: " << radio << endl;
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
        totalTouches -= ofRandom((growthRate/hold)*0.02);
        audio.playerInput("down");
    }
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    touchposx = touch.x;
    touchposy = touch.y;
    happyUp = TRUE;
    
    if(growth == false){
        //double tap to hurt, single tap to heal, hold to double last effect
        totalTouches += ofRandom((growthRate/hold)*0.02);
    }
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    playerPress = false;
    audio.playerInput("up");
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
    

    hairLonger = false; //first turn off hair longer
    ofSetColor(creatureColour[1], creatureColour[0], creatureColour[2]);///then set hair colour
    for(int i = 0; i < cuantos*0.5; i++){///loop and draw half of the hairs
        lista[i].draw(radio/2+((creatureMoodMeter*totalTouches)*0.003));
    }
    
    hairLonger = true;
    ofSetColor(creatureColour[0], creatureColour[2], creatureColour[1]);
    for(int i = cuantos*0.5; i < cuantos; i++){
        lista[i].draw2(hold, radio-(totalTouches*0.007));
    }
    
    /*
    ///debug for flipGrowth
    //IF TRUE, GREEN
    if(happyUp == TRUE){
        ofFill();
        ofSetColor(0, 255, 0);
        ofDrawSphere(0, 0, 10);
    }else{
        // IF FALSE, RED
        ofSetColor(255, 0, 0);
        ofDrawSphere(0, 0, 10);
    }
     */
    
    

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


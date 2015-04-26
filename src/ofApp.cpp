#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cuantos = 4000;
    radio = ofGetHeight()/3;
    
    for(int i = 0; i < 4000; i++){
        
        z.push_back(0.0);
        phi.push_back(0.0);
        largos.push_back(0.0);
        lista.push_back(Pelo(radio));
        
        //lista needs to be filled up with Pelos
    }

    ofSetDepthTest(true);
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    cout << mouseX << endl;
    
    float rxp = ((mouseX-(ofGetWidth()/2))*0.005);
    float ryp = ((mouseY-(ofGetHeight()/2))*0.005);
    
    
    cout << rxp << endl;
    
    rx = (rx*0.9)+(rxp*0.1);
    ry = (ry*0.9)+(ryp*0.1);
    
    ofRotateY(ofRadToDeg(rx));
    ofRotateX(ofRadToDeg(ry));
    
    
    ofFill();
    ofSetColor(0);
    ofDrawSphere(0, 0, radio);
    ofNoFill();
    ofSetColor(255);
    for(int i = 0; i < cuantos; i++){
        lista[i].draw();
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
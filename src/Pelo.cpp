//
//  Pelo.cpp
//  emptyExample
//
//  Created by Simon on 11/02/2015.
//
//

#include "Pelo.h"
#include "creatureCreation.h"
creatureCreation creatureStuff;

Pelo::Pelo(float t_radio){
    radio = t_radio;
    z = ofRandom(-radio, radio);
    phi = ofRandom(TWO_PI);
    largo = ofRandom(0.284, 1.992);
    theta = asin(z/radio);

}

void Pelo::draw(int newRadio){
    float off = (ofNoise(ofGetSystemTimeMicros() * 0.0002, sin(phi))-0.4) * 0.7;
    float offb = (ofNoise(ofGetElapsedTimeMillis() * 0.0003, sin(z) * 0.04)-0.2) * creatureMoodMeter*0.33;
    
    float thetaff = theta+off;
    float phff = phi+offb;
    float x = newRadio * cos(theta) * cos(phi);
    float y = newRadio * cos(theta) * sin(phi);
    float z = newRadio * sin(theta);
    
    //float msx= screenX(x, y, z);
    //float msy= screenY(x, y, z);
    
    float xo = newRadio * cos(thetaff) * cos(phff);
    float yo = newRadio * cos(thetaff) * sin(phff);
    float zo = newRadio * sin(thetaff);
  
    float xb = xo * (largo+totalTouches);
    float yb = yo * (largo+totalTouches);
    float zb = zo * (largo*totalTouches);

    ofLine(x,y,z, xb,yb,zb);
}
void Pelo::draw2(int numTouches, int newRadio){
    float off = (ofNoise((creatureStuff.creatureLocation[1]/ofGetElapsedTimeMillis()) * 0.0002, sin(phi))-0.5) * creatureMoodMeter*0.006;
    float offb = (ofNoise((creatureStuff.creatureLocation[0]/ofGetSystemTimeMicros()) * 0.0003, sin(z) * 0.04)-0.2) * 0.3;
    
    float thetaff = theta+off;
    float phff = phi+offb;
    
    float x = newRadio * cos(theta) * cos(phi);
    float y = newRadio * cos(theta) * sin(phi);
    float z = newRadio * sin(phff);
    
    float xo = newRadio * cos(thetaff) * cos(phff);
    float yo = newRadio * cos(thetaff) * sin(phff);
    float zo = newRadio * sin(thetaff);
    
    float xb = xo * creatureMoodMeter/totalTouches;
    float yb = yo * creatureMoodMeter/totalTouches;
    float zb = zo * totalTouches/3;
    
    if(hairLonger == true){
        /*
         xb = xo * (largo*(sin(x)/numTouches));
         yb = yo * (largo+(sin(y)/numTouches));
         zb = zo * (largo-(sin(z)/numTouches));
         */
        if(hold <= holdMax*0.49){
            xb = xo * (largo-(numTouches*0.07));
            yb = yo * (largo*(numTouches*0.07));
            zb = zo * (largo-(numTouches*0.07));
        }
        if(hold >= holdMax*0.51){
            xb = xo * (largo*(numTouches*0.014));
            yb = yo * (largo+(numTouches*0.014));
            zb = zo * (largo*(numTouches*0.014));
        }
    }
    ofLine(x,y,z, xb,yb,zb);
}
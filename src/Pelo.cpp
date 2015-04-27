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
    if(playerInput[2] == 0){//game has no inputs
        largo = ofRandom(0.184, 1.992);
    }else{
        largo = ofRandom(creatureMood[6]/playerInput[2], 1.992);
        largo = ofRandom(largo);
        //updates largo
    }
    cout << "largo= " << largo<< endl;
    theta = asin(z/radio);

}

void Pelo::draw(int newRadio){

    
    float off = (ofNoise(creatureMood[0] + 0.0002, sin(phi))-0.4) * 0.7;
    float offb = (ofNoise(creatureMood[5] + 0.0003, sin(z) * 0.04)-0.2) * (creatureMood[1]*0.33);
    
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
  
    float xb = xo * (creatureMood[0]+largo);
    float yb = yo * (creatureMood[0]+largo);
    float zb = zo * (creatureMood[1]+largo);

    ofLine(x,y,z, xb,yb,zb);
}
void Pelo::draw2(int tween, int newRadio){
    float off = (ofNoise(creatureMood[1] + 0.0002, sin(phi))-0.5) * (creatureMood[1]*0.006);
    float offb = (ofNoise(creatureMood[2] + 0.0003, sin(z) * 0.04)-0.2) * 0.3;
    
    float thetaff = theta+off;
    float phff = phi+offb;
    
    float x = newRadio * cos(theta) * cos(phi);
    float y = newRadio * cos(theta) * sin(phi);
    float z = newRadio * sin(theta);
    
    float xo = newRadio * cos(thetaff) * cos(phff);
    float yo = newRadio * cos(thetaff) * sin(phff);
    float zo = newRadio * sin(phi);
    
    float xb = xo * largo;
    float yb = yo * largo;
    float zb = zo * largo;
    //0=happy, 1=sad, 2=unhappy, 3= angry, 4=hungry, 5=seed, 6=superseed.

    if(hairLonger == true){
        
         xb = xo * (largo*(sin(x)/tween));
         yb = yo * (largo+(sin(y)/tween));
         zb = zo * (largo-(sin(z)/tween));
         /*
        if(tween < holdMax/2){
            xb = xo * (largo-(playerInput[2]*0.07));
            yb = yo * (largo*(playerInput[2]*0.07));
            zb = zo * (largo-(playerInput[2]*0.07));
        }else{
            xb = xo * (largo*(playerInput[2]*0.014));
            yb = yo * (largo+(playerInput[2]*0.014));
            zb = zo * (largo*(playerInput[2]*0.014));
        }
          */
    }
    
    ofLine(x,y,z, xb,yb,zb);
    //ofTriangle(x,y,z, xb,yb,zb);
    //ofTriangle(x, y, z, xb, yb, zb, x+xb, y+yb, z+zb);
}
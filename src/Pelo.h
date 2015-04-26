//
//  Pelo.h
//  emptyExample
//
//  Created by Simon on 11/02/2015.
//
//

#ifndef __emptyExample__Pelo__
#define __emptyExample__Pelo__

#include "ofMain.h"

class Pelo {

    public:

    Pelo(float t_radio); //this is the constructor
    void draw(int newRadio);
    void draw2(int numTouches, int newRadio);
    private:
    float z;
    float phi;
    float largo;
    float theta;
    float radio;
    
};

#endif /* defined(__emptyExample__Pelo__) */

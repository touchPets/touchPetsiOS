//
//  creatureCreation.h
//  TouchPets
//
//  Created by Arnoldas Sabaliauskas on 05/03/2015.
//
//

#ifndef __TouchPets__creatureCreation__
#define __TouchPets__creatureCreation__
#pragma once

#include "ofMain.h"
#include "Settings.h"

//= need to be saved

extern int creatureColour[4];
extern bool happyUp;
extern float growthRate;
extern float totalTouches;
extern float creatureMoodMeter;

extern float hold;
extern int holdMax;
extern bool growth;
extern bool hairLonger;

class creatureCreation{
    public:
    creatureCreation();
    void colourShift();
    void setupCreature();
    void saveGame();
    void loadGame();
    bool loadCreature = false;
    void creatureMood(bool playerAction);

    int mode;
    double hairyness;
    double noisyness;
    double ridges;
    double wobbliness;
    double tunefulness;
    void creatureFinder(int x, int y);
    int creatureLocation[3];
    
    double currentTime[3];
    int currentDate[3];
    
    int touchAvLength;

    private:
    void refresh();
    bool updated = false;
    
    double lastTime[3];
    int lastDate[3];
    
};


#endif /* defined(__TouchPets__creatureCreation__) */

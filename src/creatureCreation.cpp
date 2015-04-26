//
//  creatureCreation.cpp
//  TouchPets
//
//  Created by Arnoldas Sabaliauskas on 05/03/2015.
//
//

#include "creatureCreation.h"
#include<iostream> //debug only

    float totalTouches = 0.0;
    int creatureColour[4];
    float growthRate = 1.0;
    float creatureMoodMeter = 0.0;

    bool happyUp = 0;
    bool hairLonger = false;
    float hold = 1.00;
    int holdMax = 35;
    bool growth = false;

creatureCreation::creatureCreation(){
    ////////////////////////////////////////////////////////////
    //SETUP/CLASS MAIN
    ////////////////////////////////////////////////////////////
        cout << "==========" << endl;
        cout << "creatureCreation::creatureCreation" << endl;
        cout << "==========" << endl;
    ///updates time and date
    currentDate[0] = ofGetDay();
    currentDate[1] = ofGetMonth();
    currentDate[2] = ofGetYear();
        cout << "current.date=SET" << endl;
    currentTime[0] = ofGetHours();
    currentTime[1] = ofGetMinutes();
    currentTime[2] = ofGetSeconds();
        cout << "current.date=SET" << endl;
        cout << "0 == false || 1 == true" <<endl;
        cout << "ccreatureCreation::creatureCreation.updated=" << updated << endl;
    
    if(updated == false){
        refresh();
    }
    cout << "0 == false || 1 == true" <<endl;
    cout << "creatureCreation::creatureCreation.updated=" << updated << endl;
}

//// GROWTH STATE CHANGES BASED ON TWO FACTORS; TIME AND INPUT AMOUNT.
// - -
// 1 PERIOD IS EQUAL TO 24 HOURS
// - -
// AFTER ONE PERIOD (A PERIOD HERE ACTING AS A TRIGGER OF A BOOLEAN RATHER THAN A LOG OF SPECIFICALLY HOW MUCH TIME HAS PASSED), INFORMATION ABOUT
// TOTAL INTERACTIONS (AVERAGE OF HOW MANY "HURT" TOUCHES / HOW MANY "HEAL" TOUCHES) INFLUENCES A CHANGE IN THE CREATURE
// - -
// UPON NEXT OPENING OF APP AFTER PERIOD, PLAYER IS GREETED BY AN "EVOLUTION" ANIMATION DEPICTING CHANGE OF STATE


void creatureCreation::loadGame(){
    cout << "==========" << endl;
    cout << "creatureCreation::loadGame" << endl;
    cout << "==========" << endl;
    cout << "default::creatureRed=" << creatureColour[0]<< endl;
    cout << "default::creatureBlue=" << creatureColour[1]<<endl;
    cout << "default::creatureBlue=" << creatureColour[1]<<endl;
    cout << "default::growthRate=" << growthRate<<endl;
    cout << "default::totalTouches=" << totalTouches<<endl;
    cout << "default::creatureMoodMeter=" << creatureMoodMeter<<endl;
    cout << "==========" << endl;
    //main creature needs/functions/data
    creatureColour[0]   = Settings::getInt("creatureRed");      cout << "getting::creatureRed=" << creatureColour[0]<< endl;
    creatureColour[1]   = Settings::getInt("creatureBlue");     cout << "getting::creatureBlue=" << creatureColour[1]<<endl;
    creatureColour[2]   = Settings::getInt("creatureGreen");    cout << "getting::creatureGreen=" << creatureColour[2]<<endl;
    growthRate          = Settings::getFloat("growthRate");     cout << "getting::growthRate=" << growthRate<<endl;
    totalTouches        = Settings::getFloat("totalTouches");   cout << "getting::totalTouches=" << totalTouches<<endl;
    creatureMoodMeter   = Settings::getFloat("creatureMoodMeter");   cout << "getting::creatureMoodMeter=" << creatureMoodMeter<<endl;
    /*
    //debugging
    cout << "==========" << endl;
    cout << "creatureCreation::loadGame.debugging" << endl;
    cout << "==========" << endl;
    float testing;
    testing   = Settings::getInt("creatureRed");      cout << "getting::creatureRed=" << testing<< endl;
    testing   = Settings::getInt("creatureBlue");     cout << "getting::creatureBlue=" << testing<<endl;
    testing   = Settings::getInt("creatureGreen");    cout << "getting::creatureGreen=" << testing<<endl;
    testing   = Settings::getFloat("growthRate");     cout << "getting::growthRate=" << testing<<endl;
    testing   = Settings::getFloat("totalTouches");   cout << "getting::totalTouches=" << testing<<endl;
    testing   = Settings::getFloat("creatureMoodMeter");   cout << "getting::creatureMoodMeter=" << testing<<endl;

     */
    
}
void creatureCreation::setupCreature(){
    cout << "==========" << endl;
    cout << "creatureCreation::setupGame" << endl;
    cout << "==========" << endl;
    loadCreature = Settings::getBool("loadCreature");          cout << "getting::loadGame=" << loadCreature<<endl;
    cout << "0 == false || 1 == true" <<endl;
    //checks for a saved game
    
    if(loadCreature == false){
        cout << "creatureCreation::settingCreature" << endl;
        //main creature needs/functions/data
        Settings::setInt(255, "creatureRed");      cout << "setting::creatureRed=" << 255<< endl;
        Settings::setInt(255, "creatureBlue");     cout << "setting::creatureBlue=" << 255<<endl;
        Settings::setInt(255, "creatureGreen");    cout << "setting::creatureGreen=" << 255<<endl;
        Settings::setFloat(growthRate, "growthRate");            cout << "setting::growthRate=" << growthRate<<endl;
        Settings::setFloat(totalTouches, "totalTouches");        cout << "setting::totalTouches=" << totalTouches<<endl;
        Settings::setFloat(creatureMoodMeter, "creatureMoodMeter");   cout << "setting::creatureMoodMeter=" << creatureMoodMeter<<endl;

        //game setup hidden data/not usable by player
        Settings::setBool(true, "loadCreature");                 cout << "setting::loadCreature=true" <<endl;
        //skips creature creation on game launch
    }else{
        cout << "creatureCreation::skipped" << endl;
    }
    
}
void creatureCreation::saveGame(){
    cout << "creatureCreation::savingGame" << endl;
    cout << "==========" << endl;
    //main creature needs/functions/data
    Settings::setInt(creatureColour[0], "creatureRed");
    //cout << "setting::creatureRed=" << creatureColour[0]<< endl;
    Settings::setInt(creatureColour[1], "creatureBlue");
    //cout << "setting::creatureBlue=" << creatureColour[1]<<endl;
    Settings::setInt(creatureColour[2], "creatureGreen");
    //cout << "setting::creatureGreen=" << creatureColour[2]<<endl;
    Settings::setFloat(growthRate, "growthRate");
    //cout << "setting::growthRate=" << growthRate<<endl;
    Settings::setFloat(totalTouches, "totalTouches");
    //cout << "setting::totalTouches=" << totalTouches<<endl;
    Settings::setFloat(creatureMoodMeter, "creatureMoodMeter");
    //cout << "setting::creatureMoodMeter=" << creatureMoodMeter<<endl;

}



void creatureCreation::refresh(){
    ////////////////////////////////////////////////////////////
    //UPDATE X
    ////////////////////////////////////////////////////////////
    cout << "==========" << endl;
    cout << "creatureCreation::refresh" << endl;
    cout << "==========" << endl;
        lastDate[0] = currentDate[0];
        lastDate[1] = currentDate[1];
        lastDate[2] = currentDate[2];
            cout << "refresh.date=TRUE" << endl;
        lastTime[0] = currentTime[0];
        lastTime[1] = currentTime[1];
        lastTime[2] = currentTime[2];
            cout << "refresh.time=TRUE" << endl;
    updated = true;
}


void creatureCreation::colourShift(){
    ////////////////////////////////////////////////////////////
    //COLOUR EFFECT
    ////////////////////////////////////////////////////////////
    if(creatureColour[0] < 244 && ofGetSeconds() > 31){
        creatureColour[0] += ofRandom(1, 2);
    }
    if(creatureColour[1] < 244 && ofGetSeconds() < 29){
        creatureColour[1] += ofRandom(1, 2);
    }
    if(creatureColour[2] < 244 && ofGetSeconds() % 2){
        creatureColour[2] += ofRandom(1, 2);
    }
}

void creatureCreation::creatureMood(bool playerAction){
    //changes the mood based on action
    if(playerAction == 0){//false
        if(creatureMoodMeter > -100){
            creatureMoodMeter-= ofRandom(1);
        }
    }else if(playerAction == 1){//true
        if(creatureMoodMeter < 100){
            creatureMoodMeter+= ofRandom(1);
        }
    }
}

void creatureCreation::creatureFinder(int x, int y){
    creatureLocation[0] = x;
    creatureLocation[1] = y;
}

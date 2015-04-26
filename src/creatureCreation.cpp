//
//  creatureCreation.cpp
//  TouchPets
//
//  Created by Arnoldas Sabaliauskas on 05/03/2015.
//
//

#include "creatureCreation.h"
#include<iostream> //debug only

    int creatureColour[4];
    float growthRate = 0.0;
    float creatureMood[7];
    int playerInput[3];

    bool happyUp = 0;
    bool hairLonger = false;
    float hold = 1.00;
    int holdMax = 35;
    bool growth = false;

creatureCreation::creatureCreation(){
    ////////////////////////////////////////////////////////////
    //SETUP/CLASS MAIN
    ////////////////////////////////////////////////////////////

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
    cout << "default::creatureMood(seed)=" << creatureMood[5]<<endl;
    cout << "default::creatureMood(Superseed)=" << creatureMood[6]<<endl;
    
    playerInput[0]   = 0;
    playerInput[1]   = 0;
    playerInput[2]   = Settings::getInt("allInput");
    
    cout << "updating::inputs..." << playerInput[2] <<endl;
    
    ////////////////////////////
    moodOFcreature();
    ////////////////////////////
    
    cout << "==========" << endl;
    //main creature needs/functions/data
    creatureColour[0]   = Settings::getInt("creatureRed");
    creatureColour[1]   = Settings::getInt("creatureBlue");
    creatureColour[2]   = Settings::getInt("creatureGreen");
    growthRate          = Settings::getFloat("growthRate");
    creatureMood[5]   = Settings::getFloat("creatureMood(SUPERseed)");//makes seed to superseed
    
    cout << "loading::creatureRed=" << creatureColour[0]<< endl;
    cout << "loading::creatureBlue=" << creatureColour[1]<<endl;
    cout << "loading::creatureGreen=" << creatureColour[2]<<endl;
    cout << "loading::growthRate=" << growthRate<<endl;
    cout << "loading::playerInput=" << playerInput[0] <<endl;
    cout << "loading::creatureMood(seed)=" << creatureMood[5]<<endl;
    cout << "checking::creatureMood(Superseed)=" << creatureMood[6]<<endl;

    
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
void creatureCreation::saveGame(){
    cout << "creatureCreation::savingGame" << endl;
    cout << "==========" << endl;
    //main creature needs/functions/data
    
    Settings::setInt(creatureColour[0], "creatureRed");
    Settings::setInt(creatureColour[1], "creatureBlue");
    Settings::setInt(creatureColour[2], "creatureGreen");
    Settings::setFloat(growthRate, "growthRate");
    Settings::setFloat(creatureMood[6], "creatureMood(SUPERseed)");
    Settings::setInt(playerInput[2], "allInput");
    
    //debugging
    //cout << "saving::creatureRed=" << creatureColour[0]<< endl;
    //cout << "saving::creatureBlue=" << creatureColour[1]<<endl;
    //cout << "saving::creatureGreen=" << creatureColour[2]<<endl;
    //cout << "saving::growthRate=" << growthRate<<endl;
    cout << "saving::creatureMood(Superseed)=" << creatureMood[6]<<endl;
    cout << "saving::allInput=" << playerInput[2] <<endl;
    
}
void creatureCreation::setupCreature(){
    cout << "==========" << endl;
    cout << "creatureCreation::setupGame" << endl;
    cout << "==========" << endl;
    loadCreature = Settings::getBool("loadCreature");          cout << "getting::loadGame=" << loadCreature<<endl;
    cout << "0 == false || 1 == true" <<endl;
    //checks for a saved game
    
    if(loadCreature == false){
        ///set to false or true for testing
        
        cout << "creatureCreation::settingCreature" << endl;
        //main creature needs/functions/data
        Settings::setInt(254, "creatureRed");
        Settings::setInt(254, "creatureBlue");
        Settings::setInt(254, "creatureGreen");
        Settings::setFloat(growthRate+1, "growthRate");
        Settings::setInt(0, "allInput");
        Settings::setBool(true, "loadCreature");//boot flag
        
        //debugging
        //cout << "setting::creatureRed=" << creatureColour[0]<< endl;
        //cout << "setting::creatureBlue=" << creatureColour[1]<<endl;
        //cout << "setting::creatureGreen=" << creatureColour[2]<<endl;
        //cout << "setting::growthRate=" << growthRate<<endl;
        //cout << "setting::creatureMood(seed)=" << creatureMood[5]<<endl;
        cout << "setting::allInput= 0" <<endl;
        cout << "setting::loadCreature= true" <<endl;

    }else{
        cout << "creatureCreation::skipped" << endl;
    }
    
}
void creatureCreation::inputsUpdate(bool allInputs){
    playerInput[0] = playerInput[2]/2;//should divide by time away
    playerInput[1] = playerInput[2]/2;
    updateInputs = true;

}

void creatureCreation::moodOFcreature(){
    if(playerInput[2] == 0){
        playerInput[2] = playerInput[0] + playerInput[1];//adds all inputs
    }else{
        if(updateInputs == false){
            cout << "creatureCreation::inputsUpdate=" << updateInputs<<endl;
            inputsUpdate(updateInputs);
        }
        playerInput[2] = playerInput[0] + playerInput[1];//adds all inputs
    }
    
    if(playerInput[2] == 0|| creatureMood[5] == 0){//first boot event
        cout << "creatureCreation::SeedUpdateBoot or ERROR" << endl;
        cout << "==========" << endl;
        creatureMood[5] = ofRandomf();//picks a random number
        creatureMood[6] = creatureMood[5];//sets superseed to seed
        creatureMood[6] = creatureMood[6]*2;
        creatureMood[6] = (creatureMood[5]+creatureMood[6])//seed+superseed(seed*2)
        * (creatureMood[6]*0.1);//times superseed 10%
        
        cout << "SEED::boot=" << creatureMood[5] <<endl;
        cout << "SUPERSEED::boot=" << creatureMood[6] <<endl;

    }
    ////////////////////////////////////////////////////////////
    //GROWTH EFFECT USING SEEDS
    ////////////////////////////////////////////////////////////
    if(ofGetSeconds() == 30 && playerInput[2] > 0//if a time has passed and player tapped on screen
       && moodDone == false){//if mood can be changed
        cout << "==========" << endl;
        cout << "TIMELY SEED UPDATE" << endl;
        
            creatureMood[5] = ofRandom(playerInput[2]*0.01);//updates via all player input
            creatureMood[6] = creatureMood[5];//sets superseed to seed
            creatureMood[6] = ofRandom(creatureMood[6]*2);
            creatureMood[6] = creatureMood[5]/(creatureMood[6]+playerInput[2]);
    
        cout << "newSEED= " << creatureMood[5] <<endl;
        cout << "newSUPERSEED= " << creatureMood[6] <<endl;
    }
}
void creatureCreation::creatureMoodShift(){
    //0=happy, 1=sad, 2=unhappy, 3= angry, 4=hungry, 5=seed, 6=superseed.
    ////////////////////////////////////////////////////////////
    //MOOD CREATION
    ////////////////////////////////////////////////////////////
    if(playerInput[2] > 0 && moodDone == false){//game started and testing
        
        if(ofGetSeconds() == 15 ||
           ofGetSeconds() == 30||
           ofGetSeconds() == 45){
            //updates every 3 times per min
            
            cout << "==========" << endl;
            cout << "MOOD UPDATED at " << ofGetSeconds()<<endl;

            if(playerInput[0] > playerInput[1]){//on more than off
                //happy=
                creatureMood[0] = ofRandom(playerInput[0]*0.01);///happy change = green
                if(creatureColour[1] < 255 && creatureColour[1] > ofRandom(100, 155)){
                    creatureColour[1] = ofRandom(200, 255); //green
                }
            }
            
            if(playerInput[1] > playerInput[0]){//off more than on
                //sad=
                creatureMood[1] = ofRandom(playerInput[1]*0.01);///sad change
                if(creatureColour[2] < 255 && creatureColour[2] > ofRandom(100, 155)){
                    creatureColour[2] = ofRandom(200, 255); //blue
                }
            }
            
            //hunger=
            creatureMood[4]= ofRandom(creatureMood[6]/(creatureMood[0]+creatureMood[1]));
            //unhappy=
            creatureMood[2]= ofRandom(creatureMood[6]/playerInput[1]);

            
            if(creatureMood[4]+creatureMood[2] > //hungry+unhappy
               creatureMood[0]+creatureMood[1]){ //happy+sad
                //angry=
                creatureMood[3] = ofRandom(playerInput[2]*0.01);///angry change = red
                if(creatureColour[0] < 255 && creatureColour[0] > ofRandom(100, 155)){
                    creatureColour[0] = ofRandom(200, 255); //red
                }
            }
            
             cout << "Happy: " << creatureMood[0] <<endl;
             cout << "Sad: " << creatureMood[1] <<endl;
             cout << "Unhappy: " << creatureMood[2] <<endl;
             cout << "Angry: " << creatureMood[3] <<endl;
             cout << "Hungry: " << creatureMood[4] <<endl;
             cout << "==========" << endl;
             cout << "INPUTS" << endl;
             cout << "On: " << playerInput[0] <<endl;
             cout << "Off: " << playerInput[1] <<endl;
             cout << "All: " << playerInput[2] <<endl;
            cout << "==========" << endl;
            cout << "newSEED= " << creatureMood[5] <<endl;
            cout << "newSUPERSEED= " << creatureMood[6] <<endl;
            
            moodDone = true;
        }
        /*else if(playerInput[0] < playerInput[2]/2 || playerInput[1] < playerInput[2]/2){//from all
         creatureMood[2] = creatureMood[0]+creatureMood[1];
         cout << "All Want:" << playerInput[2] << endl;
         
         }
         */
        
    }
    ////////////////////////////////////////////////////////////
    //MOOD OFF
    ////////////////////////////////////////////////////////////
    if(ofGetSeconds() != 15 &&
       ofGetSeconds() != 30 &&
       ofGetSeconds() != 45){//resets
        moodDone = false;
    }
    
}
void creatureCreation::colourShift(){
    ////////////////////////////////////////////////////////////
    //COLOUR EFFECT
    ////////////////////////////////////////////////////////////
    if(creatureColour[0] < 254 && creatureColour[0] > 101 &&
       ofGetSeconds() > 31){
        creatureColour[0] += ofRandomf();
    }
    if(creatureColour[1] < 254 && creatureColour[1] > 101 &&
       ofGetSeconds() < 29){
        creatureColour[1] += ofRandomf();
    }
    if(creatureColour[2] < 254 && creatureColour[2] > 101 &&
       ofGetSeconds() % 2){
        creatureColour[2] += ofRandomf();
    }
}
void creatureCreation::creatureFinder(int x, int y){
    creatureLocation[0] = x;
    creatureLocation[1] = y;
}

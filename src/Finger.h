//
//  Finger.h
//  Raybreak
//
//  Created by Julian Adenauer on 23.11.15.
//
//

#ifndef Finger_h
#define Finger_h

#include <stdio.h>
#include "ofMain.h"

class Finger {
    
private:
    ofPoint position;
    ofVec2f direction;
    float angleMean = 0;
    float angleDeviation = 0;
    bool active = false;
    long lastUpdate = 0;
    long lastTriggered = 0;
    
    // display stuff
    ofVec2f ellipse_red = ofVec2f(0,3);
    ofVec2f ellipse_green;
    ofVec2f ellipse_blue;
    int r_red, r_green, r_blue;
    float speed_red, speed_green, speed_blue;

public:
    Finger();
    void update(ofPoint pos);
    ofPoint getPosition(){return position;}
    ofVec2f getDirection(){return direction;}
    bool isActive(){return active;}
    void deactivate(){active = false;}
    void draw();
    void triggered(){lastTriggered = ofGetElapsedTimeMillis();}
    long getTimeSinceLastTriggered(){return ofGetElapsedTimeMillis() - lastTriggered;}

};

#endif /* Finger_h */

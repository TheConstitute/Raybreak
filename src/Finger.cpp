//
//  Finger.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 23.11.15.
//
//

#include "Finger.h"

Finger::Finger(){
    ellipse_green = ellipse_red.getRotated(120);
    ellipse_blue = ellipse_red.getRotated(240);
    
    r_red = (int) ofRandom(8, 12);
    r_green = (int) ofRandom(8,12);
    r_blue = (int) ofRandom(8,12);
    
    speed_red = ofRandom(2.0, 4.0);
    speed_green = ofRandom(2.0, 4.0);
    speed_blue = ofRandom(2.0, 4.0);
}

void Finger::update(ofPoint pos){
    lastUpdate = ofGetElapsedTimeMillis();
    active = true;
    ofVec2f dir = pos - position;
    direction = dir;
    position = pos;
}

void Finger::draw(){
    if(active){
        ofPushStyle();
        ofSetCircleResolution(16);
        ofSetColor(255, 0, 0);
        ofDrawCircle(position + ( ellipse_red + (5*ellipse_red * sin(ellipse_red.angleRad(ofVec2f(1,0))))), r_red);
        ellipse_red.rotate(speed_red);
        ofSetColor(0, 255, 0);
        ofDrawCircle(position + ( ellipse_green + (5* ellipse_green * sin(ellipse_green.angleRad(ofVec2f(1,0))))), r_green);
        ellipse_green.rotate(speed_green);
        ofSetColor(0, 0, 255);
        ofDrawCircle(position + ( ellipse_blue + (5*ellipse_blue * sin(ellipse_blue.angleRad(ofVec2f(1,0))))), r_blue);
        ellipse_blue.rotate(speed_blue);
        ofPopStyle();
    }
    
}
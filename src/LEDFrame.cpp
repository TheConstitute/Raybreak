//
//  LEDFrame.cpp
//  gFrame
//
//  Created by Robert Albert on 17.08.15.
//
//

#include "LEDFrame.h"

//--------------------------------------------------------------
void LEDFrame::setup() {
    
    //setup parameters
    parameters.setName("dmx settings");
    parameters.add(enabled.set("DMX on", true));
    parameters.add(upper_pulsing_limit.set("upper PL",0,0,1));
    parameters.add(lower_pulsing_limit.set("lower PL", 0,0,1));
    parameters.add(brightness.set("LED brightness",1.0,0.0,1));
    parameters.add(pulsing_time.set("LED pulsing time",2000,500,5000));
    
    dmx.connect(0);
    
    setColor(255, 255, 255);
    update();
    
    pulsing = true;
    pulsing_time = 2000; //in milliseconds
    level = 0.0;
    upper_pulsing_limit = 0.6;
    lower_pulsing_limit = 0.05;
}

//--------------------------------------------------------------
void LEDFrame::setup(string device) {
    
    //setup parameters
    parameters.setName("dmx settings");
    parameters.add(enabled.set("DMX on", true));
    parameters.add(upper_pulsing_limit.set("upper PL",0,0,1));
    parameters.add(lower_pulsing_limit.set("lower PL", 0,0,1));
    parameters.add(brightness.set("LED brightness",1.0,0.0,1));
    parameters.add(pulsing_time.set("LED pulsing time",2000,500,5000));
    
    dmx.connect(device);
    
    setColor(255, 255, 255);
    update();
    
    pulsing = true;
    pulsing_time = 2000; //in milliseconds
    level = 0.0;
    upper_pulsing_limit = 0.6;
    lower_pulsing_limit = 0.05;
}


//--------------------------------------------------------------
void LEDFrame::disconnect() {
    setColor(ofColor::black);
    update();
    dmx.disconnect();
}

//--------------------------------------------------------------
void LEDFrame::startPulsing() {
    pulsing = true;
}

//--------------------------------------------------------------
void LEDFrame::stopPulsing() {
    pulsing = false;
    level = 1.0;
}

//--------------------------------------------------------------
void LEDFrame::updateLevel() {
    
    if(ofGetElapsedTimef() - last_points_time > 3){
        if(level<lower_pulsing_limit)
            pulsing_speed = fabs(pulsing_speed);
        else if (level > upper_pulsing_limit)
            pulsing_speed = - fabs(pulsing_speed);
        
        level+=pulsing_speed;
    }
    else {
        level = upper_pulsing_limit;
    }
    
//    ofLog() << ofGetElapsedTimef() - last_points_time << " " << level;
    
    //create triangle wave for pulsing led lights
//    int time = abs(((int)ofGetElapsedTimeMillis() % (pulsing_time*2)) - pulsing_time);
    
    //check how long no point has been added
//    if (ofGetElapsedTimeMillis() - last_points_time > 500 && !pulsing)
//    {
//        level -= 0.01;
//        float new_level = ofMap(time, 0, pulsing_time, lower_pulsing_limit, upper_pulsing_limit);
//        if (level - new_level < 0)
//            startPulsing();
//    }
//    if (pulsing) {
//        //int time = abs(((int)ofGetElapsedTimeMillis() % (LED_pulsing_time*2)) - LED_pulsing_time);
//        level = ofMap(time, 0, pulsing_time, lower_pulsing_limit, upper_pulsing_limit);
//    }
    
}

//--------------------------------------------------------------
void LEDFrame::setColor(ofColor _color) {
    ired = _color.r;
    igreen = _color.g;
    iblue = _color.b;
}

//--------------------------------------------------------------
void LEDFrame::setColor(int r, int g, int b) {
    ired = r;
    igreen = g;
    iblue = b;
}

//--------------------------------------------------------------
void LEDFrame::update() {
    dmx.setLevel(2, (int)((float) ired * level * brightness));
    dmx.setLevel(3, (int)((float) igreen * level * brightness));
    dmx.setLevel(4, (int)((float) iblue * level * brightness));
    dmx.setLevel(5, 0);
    dmx.update();
}

//
//  LightParticle.h
//  emptyExample
//
//  Created by Julian Adenauer on 12.11.15.
//
//

#ifndef LightParticle_h
#define LightParticle_h

#include <stdio.h>
#include "ofMain.h"

class LightParticle {
    
private:
    float wavelength;
    ofPoint position;
    ofVec2f direction;
    ofColor color;
    float refraction_index;
    
    ofColor waveLengthToRGB(double Wavelength);
    
    vector<ofPolyline> turnedNormals;
    vector<ofPolyline> newDirections;
    
public:
    void init(ofPoint position, ofVec2f direction, float refractionIndex, float frequency);
    void setDirection(ofVec2f direction);
    ofVec2f getDirection();
    void setFrequency(float frequency);
    void setSpeed(float speed);
    void hitBorder(ofVec2f normal, float indexNewMedium);
    float getRefractionIndex();
    ofVec2f getPosition();
    void update();
    void draw();
    
};

#endif /* LightParticle_h */

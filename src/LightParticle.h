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
    static int last_id;
    
    const int particle_id;
    float wavelength;
    ofPoint position;
    ofVec2f direction;
    ofColor color;
    float refraction_index;
    
    struct Punkt {
        ofPoint position;
        long timestamp;
        float alpha;
        Punkt(ofPoint p){ position = p; timestamp = ofGetElapsedTimeMillis(); alpha = 255; }
    };
    
    vector<Punkt> points;
    
    long lastIntersection;
    long creationTime;
    float diameter = 10;
    
    bool splitted = false;

    ofColor waveLengthToRGB(double Wavelength);
    
    bool outsideView = false;
    bool fadedOut = false;
    
public:
    LightParticle();
    LightParticle(ofPoint position, ofVec2f direction, float refractionIndex, float frequency);
    LightParticle(const LightParticle& lp);
    bool operator==(const LightParticle &p);
    LightParticle& operator=(const LightParticle &p);
    
    void setDirection(ofVec2f direction);
    ofVec2f getDirection();
    void setWavelength(float wavelength);
    float getWavelength();
    int getId() const;
    
    ofColor getColor();
    void setSpeed(float speed);
    bool hitBorder(ofVec2f normal, float indexNewMedium);
    float getRefractionIndex();
    //ofPolyline getPath();
    ofVec2f getPosition();
    void setPosition(ofPoint position);
    void update();
    void draw();
    
};

#endif /* LightParticle_h */

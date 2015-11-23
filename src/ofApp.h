#pragma once

#include "ofMain.h"
#include "ray.h"
#include "LightParticle.h"
#include "ParticleRay.h"
#include "PrismRayCollider.h"
#include "Prism.h"
#include "ofxTuio.h"
#include "Finger.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    
    ofParameter<float> triggerTimeout = 400;
    ofParameter<float> triggerSpeed = 20;
    
private:
    vector<ParticleRay> rays;
    PrismRayCollider* collider;
    
    bool mouse_pressed = false;
    Prism* prism;
    ofPoint mouse_press_pos;

    vector<float> colors;

    ofxTuioClient   tuioClient;
        
    Finger finger[20];
    
    ofxPanel gui;
    
    bool drawGui = false;
    
};

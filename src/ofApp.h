#pragma once

#include "ofMain.h"
#include "LightParticle.h"
#include "ParticleRay.h"
#include "PrismRayCollider.h"
#include "Prism.h"
#include "ofxTuio.h"
#include "Finger.h"
#include "ofxGui.h"
#include "LEDFrame.h"
#include "ofxSyphon.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void windowResized(int w, int h);
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    void exit();
    
    ofParameter<float> triggerTimeout;
    ofParameter<float> triggerSpeed;
    ofParameter<float> spread;
    ofParameter<float> spreadSpeed = 0.1;
    ofParameter<float> particleSpeed = 10.0;
    ofxButton fullscreen;
    int spreadSpeed_sign = 1;

    
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
    
    ofImage spreadCircle;
    
    ofTrueTypeFont  tstar;
    
    //LEDFrame and lighting
    LEDFrame ledFrame;
    
    // syphon
    ofxSyphonServer syphonMainOut;
    
    void fullscreenPressed();
};

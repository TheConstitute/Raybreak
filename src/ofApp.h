#pragma once

#include "ofMain.h"
#include "ray.h"
#include "LightParticle.h"
#include "ParticleRay.h"
#include "PrismRayCollider.h"
#include "Prism.h"
#include "ofxTuio.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
  
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    
private:
    vector<ParticleRay> rays;
    PrismRayCollider* collider;

    bool additive_colors = true;
    bool mouse_pressed = false;
    int lightcolor = 400;
    bool rainbowlight = true;
    int light_increment = 10;
    Prism* prism;
    ofPoint mouse_press_pos;

    vector<float> colors;

    ofxTuioClient   tuioClient;
    
    struct Finger {
        ofPoint position;
        ofVec2f direction;
        float angleMean = 0;
        float angleDeviation = 0;
        bool active = false;
        long lastUpdate = 0;
        long lastTriggered = 0;
        
//        ofVec2f lastPositions[5];
//        int currentPositionIndex = 0;
        float angles[5];
        int currentAngle = 0;
        bool anglesInitialized = false;
        
        void update(ofPoint pos){
            lastUpdate = ofGetElapsedTimeMillis();
            active = true;
            ofVec2f dir = pos - position;
            float angle = direction.angle(dir);
            
            angles[currentAngle] = angle;
            currentAngle++;
            if(currentAngle > 4) {currentAngle = 0; anglesInitialized = true; }
            
            angleMean = 0;
            int lastAngle;
            // if not fully initializes, only count up to the current position in the array
            if(!anglesInitialized) lastAngle = currentAngle - 1;
            else lastAngle = 4;

            for(int i=0; i<= lastAngle; i++){
                    angleMean += angles[i];
            }
            
            angleMean /= (float) lastAngle + 1.0;
            
            angleDeviation = angle - angleMean;

            direction = dir;
            position = pos;
            
//            lastPositions[currentPositionIndex] = pos;
//            currentPositionIndex++;
//            if(currentPositionIndex == 5) currentPositionIndex = 0;
        }
    };
    
    Finger finger[20];
    
};

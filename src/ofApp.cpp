#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    ofSetVerticalSync(true);
    
    // initialize prism and collider
    prism = new Prism(ofGetWidth()/2 - 100, ofGetHeight()/2 - 120, 200, 0.1);
    collider = new PrismRayCollider(rays, *prism);
    
    // initialize tuio stuff
    tuioClient.start(3333);
    ofAddListener(tuioClient.cursorAdded,this,&ofApp::tuioAdded);
    ofAddListener(tuioClient.cursorRemoved,this,&ofApp::tuioRemoved);
    ofAddListener(tuioClient.cursorUpdated,this,&ofApp::tuioUpdated);

    // setup the gui
    gui.setup("settings"); // most of the time you don't need a name but don't forget to call setup
    gui.add(triggerTimeout.set("trigger timeout", 400, 0, 1000));
    gui.add(triggerSpeed.set( "trigger speed", 20, 1, 50));
}


//--------------------------------------------------------------
void ofApp::update(){
    tuioClient.getMessage();

    prism->update();
    collider->update();
    
    for(int i = 0; i< rays.size(); i++){
        rays[i].update();
        
        // kill dead rays
        if(rays[i].isDead()){
            rays.erase(rays.begin() + i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(drawGui) ofShowCursor();
    else ofHideCursor();
    
    ofEnableAntiAliasing();
    ofBackground(20);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // draw rays
    for(auto& ray: rays){
        ray.draw();
    }

    // draw prism
    prism->draw();
   
    // draw the fingers
    for (auto& f : finger){
        f.draw();
    }
    
    // draw debug stuff
    if(drawGui){
        gui.draw();
        ofSetColor(255);
        ofDrawBitmapString(ofGetFrameRate(), 5, ofGetHeight() - 25);
        ofDrawBitmapString(rays.size(), 5, ofGetHeight()-10);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key){
        case 'r':
            rays.clear();
            break;
        case 'h':
            drawGui = !drawGui;
            break;
    }
}

void ofApp::tuioAdded(ofxTuioCursor &cursor){
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    finger[cursor.getFingerId()].update(loc);
}

void ofApp::tuioUpdated(ofxTuioCursor &cursor){
    Finger& f = finger[cursor.getFingerId()];
    
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    
    bool wasActive = f.isActive();
    f.update(loc);
    
    if(f.getDirection().length() > triggerSpeed && wasActive && f.getTimeSinceLastTriggered() > triggerTimeout){
        ParticleRay r = ParticleRay(f.getPosition(), f.getDirection());
        rays.push_back(r);
        f.triggered();
    }
}

void ofApp::tuioRemoved(ofxTuioCursor &cursor){
    finger[cursor.getFingerId()].deactivate();
}
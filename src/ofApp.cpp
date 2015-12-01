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
    gui.add(spread.set( "spread", 0.8, 0.0, 2.0));
    gui.add(spreadSpeed.set( "spread speed", 0.001, 0, 0.005));
    gui.add(particleSpeed.set( "particle speed", 10.0, 1.0, 30.0));
    gui.add(fullscreen.setup("fullscreen"));
    fullscreen.addListener(this,&ofApp::fullscreenPressed);
    gui.add(dmx_port.set("dmx_port", "tty.usbserial-0020111D"));
    
    gui.loadFromFile("settings.xml");
    
    spreadCircle.load("spreadcircle.png");
    spreadCircle.resize(spreadCircle.getWidth()/4.5, spreadCircle.getHeight()/4.5);
    
    tstar.load("TSTAR-Headline.ttf", 12);
    
    //LEDFrame setup
    ledFrame.setup(dmx_port);
    
    //Syphon stuff
    syphonMainOut.setName("Raybreak Main Out");
}

//--------------------------------------------------------------
void ofApp::fullscreenPressed(){
    ofToggleFullscreen();
}

void ofApp::windowResized(int w, int h){
    prism->setPosition(w/2 - 100, h/2 - 120);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    long deltaTime = ofGetElapsedTimeMillis() - lastUpdate;
    
    tuioClient.getMessage();

    // update the prism's shape
    prism->update();
    
    // update the collider and the spread of the refraction
    collider->setSpread(spread);
    collider->update();
    spread += spreadSpeed_sign * spreadSpeed;
    if(spread >= 2 || spread <= 0) spreadSpeed_sign *= -1;
    
    // update rays
    for(int i = 0; i< rays.size(); i++){
        rays[i].update(deltaTime);
        
        // don't kill dead rays, reuse them instead!!
        // kill dead rays
//        if(rays[i].isDead()){
//            rays.erase(rays.begin() + i);
//        }
    }
    
    // DMX UPDATE
    ledFrame.updateLevel();
    ledFrame.update();
    
    lastUpdate = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(drawGui) ofShowCursor();
    else ofHideCursor();
    
    ofEnableAntiAliasing();
    ofBackground(0);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // draw rays
    for(auto& ray: rays){
        if(!ray.isDead()){
            ray.draw();
        }
    }

    // draw prism
    prism->draw();
    
    // draw the fingers
    for (auto& f : finger){
        f.draw();
    }
    
    // draw spread display
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(0, 500);
    ofSetLineWidth(2);
    spreadCircle.draw(ofGetWidth()/2 - spreadCircle.getWidth()/2, 50);
    ofVec2f v(-1, 0);
    v.rotate(spread/2.0 * 180);
    v.normalize();
    ofPoint c(ofGetWidth()/2, 89.25);
    ofSetColor(255);
    ofDrawLine(c + 10 * v, c + v * 45);
    ofRectangle bounds = tstar.getStringBoundingBox(ofToString(spread.get(), 1), 0, 0);
    tstar.drawString(ofToString(spread.get(), 1),
                     (c + v * 60).x - (bounds.getWidth()/2.0),
                     (c + v * 60).y + (bounds.getHeight()/2.0));
    ofPopMatrix();
    ofPopStyle();
    
    syphonMainOut.publishScreen();
    
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

//--------------------------------------------------------------
void ofApp::tuioAdded(ofxTuioCursor &cursor){
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    finger[cursor.getFingerId()].update(loc);
    
    ledFrame.updateLastPointsTime();
}

//--------------------------------------------------------------
void ofApp::tuioUpdated(ofxTuioCursor &cursor){
    Finger& f = finger[cursor.getFingerId()];
    
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    
    // save the active value because it will be overwritten after the update
    bool wasActive = f.isActive();

    f.update(loc);
    
    // make a new ray if the speed is high enough, the finger was active and if the finger hasn't triggered anything lately
    if(f.getDirection().length() > triggerSpeed && wasActive && f.getTimeSinceLastTriggered() > triggerTimeout){
        f.triggered();
        ParticleRay r = ParticleRay(f.getPosition(), f.getDirection().scale(particleSpeed));
        
        // check if we need to create a new ray or if an old one can be reused
        // this could very well be coded more efficiently...
        int i = 0;
        for(i = 0; i< rays.size(); i++){
            if(rays[i].isDead()){
                break;
            }
        }
        if(i < rays.size()){
            rays[i] = r;
        } else{
            rays.push_back(r);
        }
    }
    
//    ledFrame.stopPulsing();
    ledFrame.updateLastPointsTime();
}

//--------------------------------------------------------------
void ofApp::tuioRemoved(ofxTuioCursor &cursor){
    finger[cursor.getFingerId()].deactivate();
}

//--------------------------------------------------------------
void ofApp::exit(){
    ledFrame.disconnect();
}

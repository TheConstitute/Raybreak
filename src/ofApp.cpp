#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    ofSetVerticalSync(true);
    
    // initialize prism and collider
    prism = new Prism(400, 200, 200, 0.1);
    collider = new PrismRayCollider(rays, *prism);
    
    tuioClient.start(3333);
    
    ofAddListener(tuioClient.cursorAdded,this,&ofApp::tuioAdded);
    ofAddListener(tuioClient.cursorRemoved,this,&ofApp::tuioRemoved);
    ofAddListener(tuioClient.cursorUpdated,this,&ofApp::tuioUpdated);}

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
    
    ofHideCursor();
    ofEnableAntiAliasing();
    ofBackground(20);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(auto& ray: rays){
        ray.draw();
    }
    
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofEnableAlphaBlending();
//    ofDisableBlendMode();
    prism->draw();

//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ofPushStyle();
    
    for (auto cursor : tuioClient.getTuioCursors()){
        int x = cursor->getX() * ofGetWidth();
        int y = cursor->getY() * ofGetHeight();
        ofSetCircleResolution(1024);
        ofSetColor(255, 0, 0);
        ofDrawCircle(x, y, 10);
        ofSetColor(0, 255, 0);
        ofDrawCircle(x-5, y+5, 10);
        ofSetColor(0, 0, 255);
        ofDrawCircle(x+5, y+5, 10);
    }
    

    ofPopStyle();

    
    
//    for(int i=0; i < normals.size(); i++){
//        ofPushStyle();
//        ofSetColor(0, 200, 50);
//        normals[i].draw();
//        ofPopStyle();
//    }
//
//    ofSetColor(200, 200, 200, 150);
    
//    //    prism.draw();
//    ofBeginShape();
//    for( int i = 0; i < prism.getVertices().size(); i++) {
//        ofVertex(prism.getVertices().at(i).x, prism.getVertices().at(i).y);
//    }
//    ofEndShape();
    
    
    ofSetColor(255);
    ofDrawBitmapString(ofGetFrameRate(), 5, 10);
    ofDrawBitmapString(rays.size(), 5, 25);
    ofDrawBitmapString(additive_colors, 5, 40);
    ofDrawBitmapString(lightcolor, 5, 55);
    ofDrawBitmapString(ofToString(ofGetMouseX()) + " / " + ofToString(ofGetMouseY()), 5, 70);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'r'){
//        rays.clear();
        rays.clear();
//        normals.clear();
        ofLog() << "\n\n==========================\n\n";
    }
    else if (key == 'a'){
        additive_colors = !additive_colors;
    }
    else if (key == '+'){
        lightcolor+=10;
    }
    else if (key == '-'){
        lightcolor-=10;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_press_pos.set(x, y);
    mouse_pressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    Ray ray;
//    ray.init(mouse_press_pos, ofPoint(x, y) - mouse_press_pos, &prism);
//    rays.push_back(ray);
    
    mouse_pressed = false;
 
    ParticleRay r = ParticleRay(ofPoint(x, y), ofVec2f(x- mouse_press_pos.x, y-mouse_press_pos.y));
    
//    for(int i=0; i< colors.size(); i++){
//
//        LightParticle p(ofPoint(x, y),
//                        ofPoint(x, y) - ofPoint(mouse_press_pos.x, mouse_press_pos.y),
//                        1.0,
//                        colors[i]);
//        p.setSpeed(10);
//        r.add(p);
//    }
    
    rays.push_back(r);
}

void ofApp::tuioAdded(ofxTuioCursor &cursor){
//    ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
//    cout << "Point n" << tuioCursor.getSessionId() << " add at " << loc << endl;
    
    finger_positions[cursor.getFingerId()] = ofPoint(cursor.getX() * ofGetWidth(), cursor.getY() * ofGetHeight());
    
}

void ofApp::tuioUpdated(ofxTuioCursor &cursor){
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    
    // get the speed
    if(finger_positions[cursor.getFingerId()] != ofPoint(0,0)){
        ofVec2f speed = loc - finger_positions[cursor.getFingerId()];
        ofVec2f acc = speed - finger_speed[cursor.getFingerId()];
        finger_speed[cursor.getFingerId()] = speed;
        
        ofLog() << acc.length();
    }
    
    finger_positions[cursor.getFingerId()] = loc;
    
//    cout << tuioCursor.getSessionId() << " " << tuioCursor.getMotionAccel() << endl;
//    if(tuioCursor.getMotionAccel() > 100){
//        tuioCursor.get
//        ParticleRay r = ParticleRay(loc, ofVec2f(x- mouse_press_pos.x, y-mouse_press_pos.y));
//        rays.push_back(r);
//    }
    
//    cout << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;
}

void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor){
    ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    cout << "Point n" << tuioCursor.getSessionId() << " remove at " << loc << endl;
}


//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


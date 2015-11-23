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
   
    // draw the fingers
    ofPushStyle();
    for (auto f : finger){
        if(f.active){
        ofSetCircleResolution(1024);
        ofSetColor(255, 0, 0);
        ofDrawCircle(f.position.x, f.position.y - 5, 10);
        ofSetColor(0, 255, 0);
        ofDrawCircle(f.position.x - 5, f.position.y + 5, 10);
        ofSetColor(0, 0, 255);
        ofDrawCircle(f.position.x + 5, f.position.y + 5, 10);
    }
        
//        ofSetColor(255, 255, 255);
//        ofDrawCircle(f.position, 10);
//        
//        ofSetColor(255, 0, 0);
//        ofDrawLine(f.position, f.position + 5 * f.direction.getRotated(f.angleMean));
        
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

    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    finger[cursor.getFingerId()].update(loc);
    
}

void ofApp::tuioUpdated(ofxTuioCursor &cursor){
    Finger& f = finger[cursor.getFingerId()];
    
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    
    bool wasActive = f.active;
    f.update(loc);

    if(f.direction.length() > 20 && wasActive && ofGetElapsedTimeMillis() - f.lastTriggered > 400){
        ParticleRay r = ParticleRay(f.position, f.direction);
        rays.push_back(r);
        f.lastTriggered = ofGetElapsedTimeMillis();
        
    }
    
//    ofLog() << finger[cursor.getFingerId()].position << ", " << finger[cursor.getFingerId()].direction << ", " << finger[cursor.getFingerId()].direction.length();
    
//    if(abs(finger[cursor.getFingerId()].angleDeviation) > 60){
////        ParticleRay r = ParticleRay(loc, finger_speed[cursor.getFingerId()]);
////        ofDrawLine(f.position, f.direction.getRotated(f.angleMean));
////        rays.push_back(r);
//        ofLog() << "now";
//    }
    
//        float angle = speed.angle(finger_speed[cursor.getFingerId()]);
//        //ofLog() << "angle: " << angle;
//        
//        if(abs(angle) > 90 && finger_speed[cursor.getFingerId()] != ofVec2f(0,0)){
//            //ofLog() << "richtungswechsel " << cursor.getFingerId();
//            ParticleRay r = ParticleRay(loc, finger_speed[cursor.getFingerId()]);
//            rays.push_back(r);
//        }
//        finger_speed[cursor.getFingerId()] = speed;
        
        
//        float speed_f = loc.length() - finger_positions[cursor.getFingerId()].length();
//        ofVec2f acc = speed - finger_speed[cursor.getFingerId()];
//        float acc_f = speed_f - finger_speed[cursor.getFingerId()].length();

//
//        ofLog() << acc.length() << " " << acc_f;
//    }
//    
//    finger_positions[cursor.getFingerId()] = loc;
    
//    cout << tuioCursor.getSessionId() << " " << tuioCursor.getMotionAccel() << endl;
//    if(tuioCursor.getMotionAccel() > 100){
//        tuioCursor.get
//        ParticleRay r = ParticleRay(loc, ofVec2f(x- mouse_press_pos.x, y-mouse_press_pos.y));
//        rays.push_back(r);
//    }
    
//    cout << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;
}

void ofApp::tuioRemoved(ofxTuioCursor &cursor){
    ofPoint loc = ofPoint(cursor.getX()*ofGetWidth(),cursor.getY()*ofGetHeight());
    //cout << "Finger " << cursor.getFingerId() << " removed" << endl;
    
    finger[cursor.getFingerId()].active = false;
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


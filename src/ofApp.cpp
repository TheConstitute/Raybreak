#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPoint p1, p2, p3;
    ofPoint p_mouse, p_center;

    p_center.set(150,150);
    p_mouse.set(ofGetMouseX(), ofGetMouseY());
    
    
    p1.set(150, 100);
    p2.set(200, 200);
    p3.set(100, 200);
    
    
    ofSetColor(0, 0, 0);
    ofDrawLine(p1, p2);
    ofDrawLine(p2, p3);
    ofDrawLine(p3, p1);
    
    ofSetColor(200, 0, 0);
    ofDrawLine(p_mouse, p_center);
    
    ofVec2f v1, v2, reflexionswinkel, vektorImMedium;
    
    
    ofSetColor(0, 200, 0);
    ofPoint intersection;
    if(ofLineSegmentIntersection(p1, p2, p_mouse, p_center, intersection)) {
        ofDrawCircle(intersection, 5);
        
        // lot-vektor berechnen
        v1.set(p1.x - p2.x, p1.y - p2.y);
        v1.rotate(90);
        
        ofSetColor(0, 0, 255);
        ofDrawLine(intersection, intersection + 10*v1.normalize());
        
        // ausfallswinkel berechnen
        v2.set(p_mouse.x - p_center.x, p_mouse.y - p_center.y);
        double eintrittswinkel = v2.angle(v1);
        ofVec2f reflexionswinkel = v1;
        reflexionswinkel.rotate(eintrittswinkel);
        
        ofSetColor(255, 255, 0);
        ofDrawLine(intersection, intersection + 20*reflexionswinkel.normalize());
        
        // eintrittswinkel berechnen
        double n_glass = 1.46;
        double neuer_winkel = asin( sin((PI/180) * eintrittswinkel) / n_glass) * (180.0/PI);
        vektorImMedium = v1.rotate(180 - neuer_winkel);
        ofLog() << neuer_winkel;
        ofSetColor(0, 255, 200);
        ofDrawLine(intersection, intersection + 40*vektorImMedium.normalize());
        
        
    }

    ofSetColor(0, 200, 0);
    if(ofLineSegmentIntersection(p2, p3, p_mouse, p_center, intersection)) {
        ofDrawCircle(intersection, 5);
        
        // lot-winkel berechnen
        
        v1.set(p2.x - p3.x, p2.y - p3.y);
        v1.rotate(90);
        
        ofSetColor(0, 0, 255);
        ofDrawLine(intersection, intersection + 10*v1.normalize());
        
        // ausfallswinkel berechnen
        v2.set(p_mouse.x - p_center.x, p_mouse.y - p_center.y);
        double eintrittswinkel = v2.angle(v1);
        ofVec2f reflexionswinkel = v1;
        reflexionswinkel.rotate(eintrittswinkel);
        
        ofSetColor(255, 255, 0);
        ofDrawLine(intersection, intersection + 20*reflexionswinkel.normalize());
        
        // eintrittswinkel berechnen
        double n_glass = 1.46;
        double neuer_winkel = asin( sin((PI/180) * eintrittswinkel) / n_glass) * (180.0/PI);
        vektorImMedium = v1.rotate(180 - neuer_winkel);
        ofLog() << neuer_winkel;
        ofSetColor(0, 255, 200);
        ofDrawLine(intersection, intersection + 40*vektorImMedium.normalize());
    }
    
    ofSetColor(0, 200, 0);
    if(ofLineSegmentIntersection(p3, p1, p_mouse, p_center, intersection)) {
        ofDrawCircle(intersection, 5);
        
        // lot-winkel berechnen
        
        v1.set(p3.x - p1.x, p3.y - p1.y);
        v1.rotate(90);
        
        ofSetColor(0, 0, 255);
        ofDrawLine(intersection, intersection + 10*v1.normalize());
        
        // ausfallswinkel berechnen
        v2.set(p_mouse.x - p_center.x, p_mouse.y - p_center.y);
        double eintrittswinkel = v2.angle(v1);
        ofVec2f reflexionswinkel = v1;
        reflexionswinkel.rotate(eintrittswinkel);
        
        ofSetColor(255, 255, 0);
        ofDrawLine(intersection, intersection + 20*reflexionswinkel.normalize());
        
        // eintrittswinkel berechnen
        double n_glass = 1.46;
        double neuer_winkel = asin( sin((PI/180) * eintrittswinkel) / n_glass) * (180.0/PI);
        vektorImMedium = v1.rotate(180 - neuer_winkel);
        ofLog() << neuer_winkel;
        ofSetColor(0, 255, 200);
        ofDrawLine(intersection, intersection + 40*vektorImMedium.normalize());
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
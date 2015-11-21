#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    // initialize prism and collider
    prism = new Prism(400, 200, 200, 0.1);
    collider = new PrismRayCollider(rays, *prism);
}

//--------------------------------------------------------------
void ofApp::update(){
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
    ofSetCircleResolution(1024);
    ofSetColor(255, 0, 0);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY()-5, 10);
    ofSetColor(0, 255, 0);
    ofDrawCircle(ofGetMouseX()-5, ofGetMouseY()+5, 10);
    ofSetColor(0, 0, 255);
    ofDrawCircle(ofGetMouseX()+5, ofGetMouseY()+5, 10);
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


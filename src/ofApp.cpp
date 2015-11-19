#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    // choose the colors => also determines the number of rays
    for(float i = 380; i<700; i+=5){
        colors.push_back(i);
    }
    
    // initialize prism and collider
    prism = new Prism(400, 200, 200, 0.1);
    collider = new PrismRayCollider(rays, *prism);
}

//--------------------------------------------------------------
void ofApp::update(){
    prism->update();
    collider->update();
    
    for(auto& ray: rays){
        ray.update();
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
    prism->drawBackground();

    
    
    
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
//    
    ParticleRay r;
    
    for(int i=0; i< colors.size(); i++){

        int rand_x = 0;//ofRandom(-5, 5);
        int rand_y = 0;//ofRandom(-5, 5);
        LightParticle p(ofPoint(x + rand_x, y + rand_y),
                                             ofPoint(x + rand_x, y + rand_y) - ofPoint(mouse_press_pos.x + rand_x, mouse_press_pos.y + rand_y),
                                             1.0,
                                             //5 * (int) ofRandom(90, 130) // 450 bis 650nm
                                             //               lightcolor
                                             colors[i]);
        p.setSpeed(10);
        r.add(p);
    }
    
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


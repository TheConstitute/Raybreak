//
//  Prism.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 19.11.15.
//
//

#include "Prism.h"

Prism::Prism(int offsetX, int offsetY, int edgeLength, float morphSpeed){

    morph_speed = morphSpeed;
    edge_length = edgeLength;
    
    vector<ofPoint> vertices(6);
    
    vertices[TOP].set(edgeLength/2 + offsetX, offsetY);
    int y = sqrt(pow(edgeLength,2) - pow((edgeLength/2), 2));
    vertices[LEFT].set(offsetX, y + offsetY);
    vertices[RIGHT].set(offsetX + edgeLength, y + offsetY);
    //    p4.set(200, 600);
    
    // middle values
    vertices[MIDDLE_LEFT].set((vertices[LEFT] - vertices[TOP])/2 + vertices[TOP]);
    vertices[MIDDLE_BOTTOM].set((vertices[RIGHT] - vertices[LEFT])/2 + vertices[LEFT]);
    vertices[MIDDLE_RIGHT].set((vertices[TOP] - vertices[RIGHT])/2 + vertices[RIGHT]);
    
    ofLineSegmentIntersection(vertices[MIDDLE_LEFT], vertices[RIGHT], vertices[LEFT], vertices[MIDDLE_RIGHT], center);
    
    polyline.addVertices(vertices);
    
    polyline.close();
}

void Prism::setPosition(int offsetX, int offsetY){  
    deformation = 0;
    
    vector<ofPoint>& vertices = polyline.getVertices();
    
    vertices[TOP].set(edge_length/2 + offsetX, offsetY);
    int y = sqrt(pow(edge_length,2) - pow((edge_length/2), 2));
    vertices[LEFT].set(offsetX, y + offsetY);
    vertices[RIGHT].set(offsetX + edge_length, y + offsetY);
    //    p4.set(200, 600);
    
    // middle values
    vertices[MIDDLE_LEFT].set((vertices[LEFT] - vertices[TOP])/2 + vertices[TOP]);
    vertices[MIDDLE_BOTTOM].set((vertices[RIGHT] - vertices[LEFT])/2 + vertices[LEFT]);
    vertices[MIDDLE_RIGHT].set((vertices[TOP] - vertices[RIGHT])/2 + vertices[RIGHT]);
    
    ofLineSegmentIntersection(vertices[MIDDLE_LEFT], vertices[RIGHT], vertices[LEFT], vertices[MIDDLE_RIGHT], center);
    
    polyline.close();
}

void Prism::update(){
    polyline[MIDDLE_LEFT] += ((polyline[MIDDLE_LEFT] - center).normalize()) * morph_speed;
    polyline[MIDDLE_BOTTOM] += ((polyline[MIDDLE_BOTTOM] - center).normalize()) * morph_speed;
    polyline[MIDDLE_RIGHT] += ((polyline[MIDDLE_RIGHT] - center).normalize()) * morph_speed;
    
    deformation += morph_speed;
    
    if(deformation > 60 || deformation <= -40)
        morph_speed = -morph_speed;
    
}

bool Prism::inside(float x, float y){
    return polyline.inside(x, y);
}

void Prism::draw(){
    ofPushStyle();
        
    ofBeginShape();
//    ofSetColor(120, 180, 255, 230);
    ofSetColor(223, 233, 240, 230);
    for(auto vertex: polyline.getVertices()){
        ofVertex(vertex);
    }
    ofEndShape();
    
    ofNoFill();
    ofSetLineWidth(3);
    
    ofMesh m;
    m.setMode(OF_PRIMITIVE_LINE_LOOP);
    m.addVertex(polyline[TOP]);
//    m.addColor(ofFloatColor(58.0/255.0, 191.0/255.0, 239.0/255.0, 0.8));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));
    
    m.addVertex(polyline[MIDDLE_LEFT]);
//    m.addColor(ofFloatColor(58.0/255.0, 191.0/255.0, 239.0/255.0, 0.8));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));
    
    m.addVertex(polyline[LEFT]);
//    m.addColor(ofFloatColor(58.0/255.0, 191.0/255.0, 239.0/255.0, 0.8));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));

    m.addVertex(polyline[MIDDLE_BOTTOM]);
//    m.addColor(ofFloatColor(180.0/255.0, 242.0/255.0, 249.0/255.0, 0.8));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));
    
    m.addVertex(polyline[RIGHT]);
//    m.addColor(ofFloatColor(1, 1, 1, 0.5));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));
    
    m.addVertex(polyline[MIDDLE_RIGHT]);
//    m.addColor(ofFloatColor(180.0/255.0, 242.0/255.0, 249.0/255.0, 0.8));
    m.addColor(ofFloatColor(16.0/255.0, 12.0/255.0, 130.0/255.0, 0.8));

//    m.draw();
    
    ofPopStyle();
}

vector<ofPoint>& Prism::getVertices(){
    return polyline.getVertices();
}
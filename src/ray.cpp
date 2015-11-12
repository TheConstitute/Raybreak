//
//  ray.cpp
//  emptyExample
//
//  Created by Julian Adenauer on 11.11.15.
//
//

#include "ray.h"

Ray::Ray(){
    
//    if(ofLineSegmentIntersection(p1, p2, p_mouse, p_center, intersection)) {
//        ofDrawCircle(intersection, 5);
//        
//        // lot-vektor berechnen
//        v1.set(p1.x - p2.x, p1.y - p2.y);
//        v1.rotate(90);
//        
//        ofSetColor(0, 0, 255);
//        ofDrawLine(intersection, intersection + 10*v1.normalize());
//        
//        // ausfallswinkel berechnen
//        v2.set(p_mouse.x - p_center.x, p_mouse.y - p_center.y);
//        double eintrittswinkel = v2.angle(v1);
//        ofVec2f reflexionswinkel = v1;
//        reflexionswinkel.rotate(eintrittswinkel);
//        
//        ofSetColor(255, 255, 0);
//        ofDrawLine(intersection, intersection + 20*reflexionswinkel.normalize());
//        
//        // eintrittswinkel berechnen
//        double n_glass = 1.46;
//        double neuer_winkel = asin( sin((PI/180) * eintrittswinkel) / n_glass) * (180.0/PI);
//        vektorImMedium = v1.rotate(180 - neuer_winkel);
//        ofLog() << neuer_winkel;
//        ofSetColor(0, 255, 200);
//        ofDrawLine(intersection, intersection + 40*vektorImMedium.normalize());
//    }
    
}

void Ray::init(ofPoint position, ofVec2f dir, ofPolyline* p){
    dir_start = dir.normalize();
    prism = p;
    timestamp = ofGetElapsedTimeMillis();
    
    ofPoint intersection_in;
    ofVec2f perpendicular;
    
    bool intersects_with_object = getClosestIntersection(position, position + dir.scale(2000), p, intersection_in, perpendicular);
    
    if (intersects_with_object){
        // neue richtung bestimmen
        double n_glass = 1.46; // brechungsindex
        float angle = dir.angle(perpendicular);
        double angle_inside = asin( sin((PI/180) * angle) / n_glass) * (180.0/PI);
        ofVec2f vektorImMedium = perpendicular.rotate(180 + angle_inside);
        
        // austrittspunkt bestimmen
        // ACHTUNG: Das muss nicht zwangsläufig der Austrittspunkt sein. Es kann auch sein, dass der Strahl hier wieder ins Prisma hinein gebrochen wird!!!
        ofPoint intersection_out;
        ofPoint start_point_in_medium = intersection_in + vektorImMedium.scale(1);
        ofPoint end_point_in_medium = intersection_in + vektorImMedium.scale(2000);
        getClosestIntersection(start_point_in_medium, end_point_in_medium, prism, intersection_out, perpendicular);
        
        // endpunkt bestimmen
        angle = vektorImMedium.angle(perpendicular);
        double angle_outside = asin( n_glass * sin((PI/180) * angle)) * (180.0/PI);
        //ofVec2f vektorOutside = perpendicular.rotate(180 + angle_outside);
        //ofPoint end = end_point_in_medium + vektorOutside.scale(2000);
        
        ofPoint end = end_point_in_medium + perpendicular.scale(2000);
        
        
        // make the beam
        beam.addVertex(position);
        beam.addVertex(intersection_in);
        beam.addVertex(intersection_out);
        beam.addVertex(end);
        
//        ofLog() << intersection_in.x << " " << intersection_in.y << " " << intersection_out.x << " " << intersection_out.y;     
        
    }
}

bool Ray::getClosestIntersection(ofPoint ray_start, ofPoint ray_end, ofPolyline* line, ofPoint& intersection, ofVec2f& perpendicular){
    // kollisionen mit allen seiten der polyline bestimmen
    vector<ofPoint> intersections;
    vector<ofVec2f> line_direction;
    
    for(int i = 0; i < prism->getVertices().size(); i++){
        ofPoint match;
        
        // determine the vertext the current one makes a line with
        // if it is the last element, the next is the first
        ofPoint next;
        if(i == prism->getVertices().size() - 1) {
            next = prism->getVertices()[0];
        } else {
            next = prism->getVertices()[i+1];
        }
        
        // calculate intersection. if ther is one, put it into the list
        bool intersection_found = ofLineSegmentIntersection(ray_start, ray_end, prism->getVertices()[i], next, match);
        if(intersection_found){
            intersections.push_back(match);
            ofVec2f direction_of_line;
            direction_of_line.set(prism->getVertices()[i] - next);
            line_direction.push_back(direction_of_line); // remember which line of the prism has been hit
        }
    }
    
    // exit the function if nothing is found
    if(intersections.size() == 0){  return false; }
    
    // now determine which intersection is the closest one
    ofPoint closest;
    int closest_index;
    float distance_min = 999999;
    for(int i=0; i<intersections.size(); i++){
        float d = fabs(ray_start.distance(intersections[i]));
        if(d < distance_min){
            distance_min = d;
            closest_index = i;
        }
    }
    
    // set the resulting intersection
    intersection = intersections[closest_index];
    
    // lot-vektor berechnen
    perpendicular = line_direction[closest_index];
    perpendicular.rotate(90);

    // calculate angle of the intersection
//    angle = perpendicular.angle(ray_start - ray_end);

    return true;
}


void Ray::update(){
    
}

void Ray::draw(){
    beam.draw();
}
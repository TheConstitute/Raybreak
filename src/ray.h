//
//  ray.h
//  emptyExample
//
//  Created by Julian Adenauer on 11.11.15.
//
//

#ifndef ray_h
#define ray_h

#include <stdio.h>
#include "ofMain.h"

class Ray {

private:
    ofVec2f dir_start;
    ofVec2f dir_in;
    ofVec2f dir_out;
    
    ofPolyline beam;
    
    float size;
    
    ofPoint entry1, entry2;
    ofPoint exit1, exit2;
    
    float timestamp;
    
    ofPolyline* prism;
    bool getClosestIntersection(ofPoint line_start, ofPoint line_end, ofPolyline* line, ofPoint& intersection, ofVec2f& perpendicular);
    
public:
    Ray();

    void init(ofPoint position, ofVec2f dir, ofPolyline* prism);
    
    void update();
    void draw();
    
};

#endif /* ray_h */

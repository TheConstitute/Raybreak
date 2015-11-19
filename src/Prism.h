//
//  Prism.h
//  Raybreak
//
//  Created by Julian Adenauer on 19.11.15.
//
//

#ifndef Prism_h
#define Prism_h

#include <stdio.h>
#include "ofMain.h"

#define TOP 0
#define MIDDLE_LEFT 1
#define LEFT 2
#define MIDDLE_BOTTOM 3
#define RIGHT 4
#define MIDDLE_RIGHT 5

class Prism{
    float deformation;
    float morph_speed;
    ofPolyline polyline;
    ofPoint center;
    
public:    
    Prism(int offsetX, int offsetY, int edgeLength, float morphSpeed);
    void update();
    void drawBackground();
    void drawForeground();
    vector<ofPoint>& getVertices();
    bool inside(float x, float y);
    
};

#endif /* Prism_h */

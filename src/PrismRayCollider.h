//
//  PrismRayCollider.h
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#ifndef PrismRayCollider_h
#define PrismRayCollider_h

#include <stdio.h>
#include "ofMain.h"
#include "ParticleRay.h"
#include "Prism.h"

class PrismRayCollider{

private:
    vector<ParticleRay>& rays;
    Prism& prism;
    std::map<int, float> refraction_lookup;
    float spread = 0.8;

    void initLookup();
    float getInterpolatedIndex(float wavelength);
    
public:
    PrismRayCollider(vector<ParticleRay>& rays, Prism& prism);
    void setSpread(float s){spread = s;}
    void update();
    
};

#endif /* PrismRayCollider_h */

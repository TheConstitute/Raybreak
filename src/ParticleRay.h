//
//  ParticleRay.h
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#ifndef ParticleRay_h
#define ParticleRay_h

#include <stdio.h>
#include "ofMain.h"
#include "LightParticle.h"

class ParticleRay {

private:
    vector<LightParticle> particles;

public:
    void add(LightParticle particle);
    void remove(LightParticle particle);
    void update();
    vector<LightParticle>& getParticles();
    void draw();
    
    
};

#endif /* ParticleRay_h */

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
    bool is_dead;

public:
    ParticleRay(ofPoint position, ofVec2f direction);
    void add(LightParticle particle);
    void remove(LightParticle particle);
    void update();
    vector<LightParticle>& getParticles();
    void draw();
    bool isDead(){return is_dead;}
    
    
};

#endif /* ParticleRay_h */

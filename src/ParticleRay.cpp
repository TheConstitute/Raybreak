//
//  ParticleRay.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#include "ParticleRay.h"

ParticleRay::ParticleRay(ofPoint position, ofVec2f direction){
    for(float i = 380; i<700; i+=5){
            LightParticle p(position,
                            direction.scale(10),
                            -1.0, // set the index to -1 because we don't know right now if it is inside the prism or not
                            i);
            particles.push_back(p);
    }
    
    is_dead = false;

}

void ParticleRay::draw(){
    for(auto& particle: particles){
        particle.draw();
    }
}

vector<LightParticle>& ParticleRay::getParticles(){
    return particles;
}

void ParticleRay::update(){
    if(!is_dead){
        bool allDead = true;
        for(auto& particle: particles){
            // make the move
            particle.update();
            if(!particle.isFadedOut()) allDead = false;
        }
        
        is_dead = allDead;
    }
}
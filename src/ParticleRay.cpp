//
//  ParticleRay.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#include "ParticleRay.h"

//void ParticleRay::add(LightParticle particle){
//    particles.push_back(particle);
//}

ParticleRay::ParticleRay(ofPoint position, ofVec2f direction){
    for(float i = 380; i<700; i+=5){
            LightParticle p(position,
                            direction.scale(10),
                            1.0,
                            i);
            particles.push_back(p);
    }
    
    is_dead = false;

}

//void ParticleRay::remove(LightParticle p){
////     ParticleRay* found = find(particles.begin(), particles.end(), p);
////    particles.erase(find(particles.begin(), particles.end(), p));
//
////    ofLog() << "remove " << p.getId();
////    particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());
//
//    for(int i=0; i<particles.size(); i++){
////        ofLog() << i << " " << particles[i].getId();
//        if(particles[i] == p) {
//            particles[i].setWavelength(250);
////            particles.erase(particles.begin() + i-1);
////            particles[i]
////            i--;
////            break;
//        }
//    }
//}

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
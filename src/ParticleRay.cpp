//
//  ParticleRay.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#include "ParticleRay.h"

void ParticleRay::add(LightParticle particle){
    particles.push_back(particle);
}

void ParticleRay::remove(LightParticle p){
//     ParticleRay* found = find(particles.begin(), particles.end(), p);
//    particles.erase(find(particles.begin(), particles.end(), p));

//    ofLog() << "remove " << p.getId();
//    particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());

    for(int i=0; i<particles.size(); i++){
//        ofLog() << i << " " << particles[i].getId();
        if(particles[i] == p) {
            particles[i].setWavelength(250);
//            particles.erase(particles.begin() + i-1);
//            particles[i]
//            i--;
//            break;
        }
    }
    
}

void ParticleRay::draw(){
    for(auto& particle: particles){
        particle.draw();
    }
    
//    for(auto& particle: particles){
//        vector<ofPoint> vertices = particle.getPath().getVertices();
//        
//        float width = 0;
//    
//        // loop through the vertices starting with the second one
//        for(int v = 1; v < vertices.size(); v++){
//            ofVec2f last = vertices[v-1];
//            ofVec2f current = vertices[v];
//            
//            ofVec2f normal = (current - last).getPerpendicular();
//            
//            ofSetColor(particle.getColor());
//            ofDrawTriangle(
//                           last + width*normal,
//                           last - width*normal,
//                           current + width*normal
//                           );
//            ofDrawTriangle(
//                           current + width*normal,
//                           current - width*normal,
//                           last - width*normal
//                           );
//            
//            width += 0.5;
//        }
//    }
    
//    for(int i = 0; i< particles.size(); i++){
//        if(i < particles.size()-1){
//            ofSetColor(particles[i].getColor());
//            for(int v=0; v<particles[i].getPath().getVertices().size(); v++)
//                ofDrawLine(
//                           particles[i].getPath().getVertices()[v],
//                           particles[i+1].getPath().getVertices()[v]
//                );
//        }
//    }
}

vector<LightParticle>& ParticleRay::getParticles(){
    return particles;
}

void ParticleRay::update(){
    for(auto& particle: particles){
        // make the move
        particle.update();
    }
}
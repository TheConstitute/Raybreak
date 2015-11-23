//
//  PrismRayCollider.cpp
//  Raybreak
//
//  Created by Julian Adenauer on 16.11.15.
//
//

#include "PrismRayCollider.h"

PrismRayCollider::PrismRayCollider(vector<ParticleRay>& r, Prism& p) : rays(r), prism(p){
    initLookup();
}

void PrismRayCollider::update(){
    
//    vector<ParticleRay> newRays;
    
    for(auto& ray: rays){
        //ParticleRay ray = rays->at(r);
        
//        vector<LightParticle> abgespaltene;
        
        // loop throught the particles in the ray
        for(auto& particle: ray.getParticles()){
            
            // don't calculate anything for particles that are outside the view
            if(particle.isOutsideViewport()) break;
            
            // if the refraction index hasn't been set yet, find it out now
            if(particle.getRefractionIndex() < 0){
                if(prism.inside(particle.getPosition().x, particle.getPosition().y)){
                    // spreizung der werte
                    float f = (1- (particle.getWavelength() / 510.0)) * spread;
                    
                    //index = refraction_lookup[particle.getWavelength()] + f;
                    particle.setRefractionIndex(getInterpolatedIndex(particle.getWavelength()) + f);
                }
                else
                    particle.setRefractionIndex(1.0);
            }
            
            
            // loop through the lines of the prism
            for(int v = 0; v < prism.getVertices().size(); v++){
                ofPoint intersection;
                
                ofPoint p1 = prism.getVertices()[v];
                
                // determine the vertext the current one makes a line with
                // if it is the last element, the next is the first
                ofPoint p2;
                if(v == prism.getVertices().size() - 1) {
                    p2 = prism.getVertices()[0];
                } else {
                    p2 = prism.getVertices()[v+1];
                }
                
                bool intersects = ofLineSegmentIntersection(particle.getPosition(), particle.getPosition() + particle.getDirection(), p1, p2, intersection);
                
                if(intersects){
                    // determine if the particle is currently in the prism or not
                    // determine the refraction index of the new medium
                    float index = 1.0;
                    if(!prism.inside(particle.getPosition().x, particle.getPosition().y)){
                        // is not inside the prism right now => set the new index to the prism's index
                        
                        // spreizung der werte
                        float f = (1- (particle.getWavelength() / 510.0)) * spread;
                        
                        //index = refraction_lookup[particle.getWavelength()] + f;
                        index = getInterpolatedIndex(particle.getWavelength()) + f;
                    }
                    
                    // get the normal and make sure it points in the right direction
                    // NOT SURE ABOUT THIS IMPLEMENTATION YET!!!
                    ofVec2f normal = (p1 - p2);
                    normal = normal.getPerpendicular();
                    
                    // nicht sicher, ob dieser schritt nötig ist
                    if(fabs(normal.angle(particle.getDirection())) < 90){
                        normal.rotate(180);
                    }
                    
                    // Position auf Kollisionsposition setzen
                    particle.setPosition(intersection);
                    
                    particle.hitBorder(normal, index);
                }
            }
        }
    }
}

float PrismRayCollider::getInterpolatedIndex(float wavelength){
    float wavelength1 = ((int) wavelength / 10) * 10;
    float wavelength2 = (((int) wavelength / 10) * 10) + 10;
    float index = refraction_lookup[wavelength1];
    float nextIndex = refraction_lookup[wavelength2];
    float dIndex = nextIndex - index;
    float dWavelength = wavelength - wavelength1;
    float x = ((dWavelength * dIndex) / 10) + index;
    return x;
}

void PrismRayCollider::initLookup(){
    refraction_lookup[210] = 1.5384;
    refraction_lookup[215] = 1.5332;
    refraction_lookup[220] = 1.5285;
    refraction_lookup[225] = 1.5242;
    refraction_lookup[230] = 1.5202;
    refraction_lookup[235] = 1.5166;
    refraction_lookup[240] = 1.5133;
    refraction_lookup[245] = 1.5103;
    refraction_lookup[250] = 1.5074;
    refraction_lookup[255] = 1.5048;
    refraction_lookup[260] = 1.5024;
    refraction_lookup[265] = 1.5001;
    refraction_lookup[270] = 1.498;
    refraction_lookup[275] = 1.496;
    refraction_lookup[280] = 1.4942;
    refraction_lookup[285] = 1.4924;
    refraction_lookup[290] = 1.4908;
    refraction_lookup[295] = 1.4892;
    refraction_lookup[300] = 1.4878;
    refraction_lookup[305] = 1.4864;
    refraction_lookup[310] = 1.4851;
    refraction_lookup[315] = 1.4839;
    refraction_lookup[320] = 1.4827;
    refraction_lookup[325] = 1.4816;
    refraction_lookup[330] = 1.4806;
    refraction_lookup[335] = 1.4796;
    refraction_lookup[340] = 1.4787;
    refraction_lookup[345] = 1.4778;
    refraction_lookup[350] = 1.4769;
    refraction_lookup[355] = 1.4761;
    refraction_lookup[360] = 1.4753;
    refraction_lookup[365] = 1.4745;
    refraction_lookup[370] = 1.4738;
    refraction_lookup[375] = 1.4731;
    refraction_lookup[380] = 1.4725;
    refraction_lookup[385] = 1.4719;
    refraction_lookup[390] = 1.4713;
    refraction_lookup[395] = 1.4707;
    refraction_lookup[400] = 1.4701;
    refraction_lookup[405] = 1.4696;
    refraction_lookup[410] = 1.4691;
    refraction_lookup[415] = 1.4686;
    refraction_lookup[420] = 1.4681;
    refraction_lookup[425] = 1.4676;
    refraction_lookup[430] = 1.4672;
    refraction_lookup[435] = 1.4668;
    refraction_lookup[440] = 1.4663;
    refraction_lookup[445] = 1.466;
    refraction_lookup[450] = 1.4656;
    refraction_lookup[455] = 1.4652;
    refraction_lookup[460] = 1.4648;
    refraction_lookup[465] = 1.4645;
    refraction_lookup[470] = 1.4641;
    refraction_lookup[475] = 1.4638;
    refraction_lookup[480] = 1.4635;
    refraction_lookup[485] = 1.4632;
    refraction_lookup[490] = 1.4629;
    refraction_lookup[495] = 1.4626;
    refraction_lookup[500] = 1.4623;
    refraction_lookup[505] = 1.4621;
    refraction_lookup[510] = 1.4618;
    refraction_lookup[515] = 1.4615;
    refraction_lookup[520] = 1.4613;
    refraction_lookup[525] = 1.461;
    refraction_lookup[530] = 1.4608;
    refraction_lookup[535] = 1.4606;
    refraction_lookup[540] = 1.4603;
    refraction_lookup[545] = 1.4601;
    refraction_lookup[550] = 1.4599;
    refraction_lookup[555] = 1.4597;
    refraction_lookup[560] = 1.4595;
    refraction_lookup[565] = 1.4593;
    refraction_lookup[570] = 1.4591;
    refraction_lookup[575] = 1.4589;
    refraction_lookup[580] = 1.4587;
    refraction_lookup[585] = 1.4586;
    refraction_lookup[590] = 1.4584;
    refraction_lookup[595] = 1.4582;
    refraction_lookup[600] = 1.458;
    refraction_lookup[605] = 1.4579;
    refraction_lookup[610] = 1.4577;
    refraction_lookup[615] = 1.4576;
    refraction_lookup[620] = 1.4574;
    refraction_lookup[625] = 1.4572;
    refraction_lookup[630] = 1.4571;
    refraction_lookup[635] = 1.457;
    refraction_lookup[640] = 1.4568;
    refraction_lookup[645] = 1.4567;
    refraction_lookup[650] = 1.4565;
    refraction_lookup[655] = 1.4564;
    refraction_lookup[660] = 1.4563;
    refraction_lookup[665] = 1.4561;
    refraction_lookup[670] = 1.456;
    refraction_lookup[675] = 1.4559;
    refraction_lookup[680] = 1.4558;
    refraction_lookup[685] = 1.4556;
    refraction_lookup[690] = 1.4555;
    refraction_lookup[695] = 1.4554;
    refraction_lookup[700] = 1.4553;
    refraction_lookup[710] = 1.4551;
    refraction_lookup[720] = 1.4549;
    refraction_lookup[730] = 1.4546;
    refraction_lookup[740] = 1.4544;
    refraction_lookup[750] = 1.4542;
    refraction_lookup[760] = 1.454;
    refraction_lookup[770] = 1.4539;
    refraction_lookup[780] = 1.4537;
    refraction_lookup[790] = 1.4535;
    refraction_lookup[800] = 1.4533;
    refraction_lookup[810] = 1.4531;
    refraction_lookup[820] = 1.453;
    refraction_lookup[830] = 1.4528;
    refraction_lookup[840] = 1.4527;
    refraction_lookup[850] = 1.4525;
    refraction_lookup[860] = 1.4523;
    refraction_lookup[870] = 1.4522;
    refraction_lookup[880] = 1.452;
    refraction_lookup[890] = 1.4519;
    refraction_lookup[900] = 1.4518;
    refraction_lookup[910] = 1.4516;
    refraction_lookup[920] = 1.4515;
    refraction_lookup[930] = 1.4513;
    refraction_lookup[940] = 1.4512;
    refraction_lookup[950] = 1.4511;
    refraction_lookup[960] = 1.4509;
    refraction_lookup[970] = 1.4508;
    refraction_lookup[980] = 1.4507;
    refraction_lookup[990] = 1.4505;
}
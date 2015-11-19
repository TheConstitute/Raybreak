//
//  LightParticle.cpp
//  emptyExample
//
//  Created by Julian Adenauer on 12.11.15.
//
//

#include "LightParticle.h"

int LightParticle::last_id = 0;

LightParticle::LightParticle() : particle_id(++last_id){
    
}

// Konstruktor
LightParticle::LightParticle(ofPoint p, ofVec2f d, float refIndex, float w) : particle_id(++last_id){
    position = p;
    wavelength = w;
    refraction_index = refIndex;
    color = waveLengthToRGB(wavelength);
    direction = d;
    creationTime = ofGetElapsedTimeMillis();
    lastIntersection = creationTime;
}

// Copy-Konstruktor
LightParticle::LightParticle(const LightParticle& lp) : particle_id(lp.particle_id){
    position = lp.position;
    wavelength = lp.wavelength;
    refraction_index = lp.refraction_index;
    color = lp.color;
    direction = lp.direction;
    creationTime = lp.creationTime;
    lastIntersection = lp.lastIntersection;
    points = lp.points;
}

bool LightParticle::operator==(const LightParticle &p){
    if(p.getId() == particle_id){
        return true;
    }
    else{
        return false;
    }
}

LightParticle& LightParticle::operator=(const LightParticle &lp){
    if(this != &lp){
        position = lp.position;
        wavelength = lp.wavelength;
        refraction_index = lp.refraction_index;
        color = lp.color;
        direction = lp.direction;
        creationTime = lp.creationTime;
        lastIntersection = lp.lastIntersection;
        points = lp.points;
    }
    return *this;
}

void LightParticle::setDirection(ofVec2f d){
    direction = d;
}

ofVec2f LightParticle::getDirection(){
    return direction;
}

void LightParticle::setWavelength(float w){
    wavelength = w;
    color = waveLengthToRGB(wavelength);
}

float LightParticle::getWavelength(){
    return wavelength;
}

int LightParticle::getId() const{
    return particle_id;
}

bool LightParticle::hitBorder(ofVec2f normal, float indexNewMedium){
    
    lastIntersection = ofGetElapsedTimeMillis();
    
    // die normale steht auf der geraden in richtung des einfallenden strahls
    // um hier den richtigen winkel zu bekommen, muss sie aber genau andersherum definiert sein
    normal.rotate(180);
    float angle = direction.angle(normal);
    
    // totalreflexion?
    if(indexNewMedium < refraction_index &&
       fabs(angle) > asin(indexNewMedium/refraction_index) * (180.0/PI)){
        
        // winkel nach totalreflexion. einfallswinkel = ausfallswinkel
        direction.rotate(-2.0*(90.0-angle));
        
        return true;
    }
    
    else{
        splitted = true;
        
        // calculate new direction
        double new_angle = asin( (refraction_index/indexNewMedium) * sin((PI/180.0) * angle)) * (180.0/PI);
        
        // set new direction
        direction.rotate(angle - new_angle);
        
        // set new speed
        setSpeed(direction.length() * (refraction_index/indexNewMedium));
        
        refraction_index = indexNewMedium;
        
        //ofLog() << wavelength << ", " << refraction_index << ", " << direction.length();
        
        return false;
    }
}

ofVec2f LightParticle::getPosition(){
    return position;
}

void LightParticle::update(){
    if(!outsideView){
        // check if particle is outside the view
        if(position.x > ofGetWidth() || position.x < 0 || position.y > ofGetHeight() || position.y < 0){
            outsideView = true;
            return;
        }
        
        this->position += direction;
        points.push_back(Punkt(position));
    }
}

void LightParticle::setPosition(ofPoint pos){
    points.push_back(Punkt(pos));
    position = pos;
}

void LightParticle::draw(){
    if(fadedOut) return;
    
    ofPushStyle();

    ofSetLineWidth(3);
    
    for(int i=0; i< points.size() - 1; i++){
        if(points[i].alpha > 0){
            if(splitted)
                points[i].alpha -= 5.0;
            else
                points[i].alpha -= 20.0;
            
            ofSetColor(color.r, color.g, color.b, points[i].alpha);
            ofDrawLine(points[i].position, points[i+1].position);
        }
        
    }

    ofPopStyle();
}

void LightParticle::setSpeed(float s){
    direction.scale(s);
}

float LightParticle::getRefractionIndex(){
    return refraction_index;
}

ofColor LightParticle::getColor(){
    return color;
}


/** Taken from Earl F. Glynn's web page:
 * <a href="http://www.efg2.com/Lab/ScienceAndEngineering/Spectra.htm">Spectra Lab Report</a>
 * */
ofColor LightParticle::waveLengthToRGB(double Wavelength){
    double Gamma = 0.80;
    double IntensityMax = 255;

    double factor;
    double Red,Green,Blue;
    
    if((Wavelength >= 380) && (Wavelength<440)){
        Red = -(Wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    }else if((Wavelength >= 440) && (Wavelength<490)){
        Red = 0.0;
        Green = (Wavelength - 440) / (490 - 440);
        Blue = 1.0;
    }else if((Wavelength >= 490) && (Wavelength<510)){
        Red = 0.0;
        Green = 1.0;
        Blue = -(Wavelength - 510) / (510 - 490);
    }else if((Wavelength >= 510) && (Wavelength<580)){
        Red = (Wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    }else if((Wavelength >= 580) && (Wavelength<645)){
        Red = 1.0;
        Green = -(Wavelength - 645) / (645 - 580);
        Blue = 0.0;
    }else if((Wavelength >= 645) && (Wavelength<781)){
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    }else{
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    };
    
    // Let the intensity fall off near the vision limits
    
    if((Wavelength >= 380) && (Wavelength<420)){
        factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
    }else if((Wavelength >= 420) && (Wavelength<701)){
        factor = 1.0;
    }else if((Wavelength >= 701) && (Wavelength<781)){
        factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
    }else{
        factor = 0.0;
    };
    
    
    ofColor c;
    // Don't want 0^x = 1 for x <> 0
    c.set( Red==0.0 ? 0 : (int) round(IntensityMax * pow(Red * factor, Gamma)),
          Green==0.0 ? 0 : (int) round(IntensityMax * pow(Green * factor, Gamma)),
          Blue==0.0 ? 0 : (int) round(IntensityMax * pow(Blue * factor, Gamma)));
    
    return c;
}
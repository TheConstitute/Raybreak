//
//  LightParticle.cpp
//  emptyExample
//
//  Created by Julian Adenauer on 12.11.15.
//
//

#include "LightParticle.h"

void LightParticle::init(ofPoint p, ofVec2f d, float refIndex, float w){
    position = p;
    wavelength = w;
    refraction_index = refIndex;
    color = waveLengthToRGB(wavelength);
    direction = d;
    creationTime = ofGetElapsedTimeMillis();
    lastIntersection = creationTime;
}

void LightParticle::setDirection(ofVec2f d){
    direction = d;
}

ofVec2f LightParticle::getDirection(){
    return direction;
}

void LightParticle::setWavelength(int w){
    wavelength = w;
    ofColor c = waveLengthToRGB(wavelength);
}

int LightParticle::getWavelength(){
    return wavelength;
}

void LightParticle::hitBorder(ofVec2f normal, float indexNewMedium){
    
    // HACK: Um doppelte reflexionen zu vermeiden. Das Problem sollte aber eigentlich woanders behoben werden!
    long deltaTime = ofGetElapsedTimeMillis() - lastIntersection;
    if(deltaTime < 30) return;
    
    lastIntersection = ofGetElapsedTimeMillis();
    
    // die normale steht auf der geraden in richtung des einfallenden strahls
    // um hier den richtigen winkel zu bekommen, muss sie aber genau andersherum definiert sein
    normal.rotate(180);
    float angle = direction.angle(normal);
    //ofLog() << angle;
    
    // totalreflexion?
    if(indexNewMedium < refraction_index &&
       fabs(angle) > asin(indexNewMedium/refraction_index) * (180.0/PI)){
//        ofLog() << "totalreflexion";
        if(angle > 0) direction.rotate(-90);
        else direction.rotate(90);
    }
    else{
        // calculate new direction
        double new_angle = asin( (refraction_index/indexNewMedium) * sin((PI/180.0) * angle)) * (180.0/PI);
        
        //ofLog() << angle << "(" << refraction_index << ") => " << new_angle << "(" << indexNewMedium << ") // " << deltaTime;
        
        refraction_index = indexNewMedium;
    
        direction.rotate(angle - new_angle);
    
//        ofPolyline p;
//        p.addVertex(position);
//        p.addVertex(position + normal.scale(10));
//        turnedNormals.push_back(p);
//        
//        normal.normalize();
//        normal.rotate(new_angle);
//        direction = normal;
//        
//        ofPolyline d;
//        d.addVertex(position);
//        d.addVertex(position + normal.scale(50));
//        newDirections.push_back(d);
    }
}

ofVec2f LightParticle::getPosition(){
    return position;
}

void LightParticle::update(){
    position += direction;
}

void LightParticle::draw(){
    ofPushStyle();
    ofSetColor(color);
    ofDrawCircle(position, 4);

//    ofDrawLine(position, position + (direction));
//    ofSetColor(0, 0, 0);
//    ofDrawBitmapString(refraction_index, position + ofVec2f(5, -5));

    ofSetColor(200, 0, 0);
    for (int i=0; i< turnedNormals.size(); i++)
        turnedNormals[i].draw();
    
    ofSetColor(0, 0, 0);
    for (int i=0; i< newDirections.size(); i++)
        newDirections[i].draw();
    
    ofPopStyle();
}

void LightParticle::setSpeed(float s){
    direction.scale(s);
}

float LightParticle::getRefractionIndex(){
    return refraction_index;
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
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
}

void LightParticle::setDirection(ofVec2f d){
    direction = d;
}

ofVec2f LightParticle::getDirection(){
    return direction;
}

void LightParticle::setFrequency(float w){
    wavelength = w;
    color = waveLengthToRGB(wavelength);
}

void LightParticle::hitBorder(ofVec2f normal, float indexNewMedium){
    float angle = direction.angle(normal);
    
    // calculate new direction
    double new_angle = asin( indexNewMedium/refraction_index * sin((PI/180.0) * angle)) * (180.0/PI);
    refraction_index = indexNewMedium;
    normal.rotate(180);
    
    ofPolyline p;
    p.addVertex(position);
    p.addVertex(position + normal.scale(10));
    turnedNormals.push_back(p);
    
    normal.normalize();
    normal.rotate(new_angle);
    direction = normal;
    
    ofPolyline d;
    d.addVertex(position);
    d.addVertex(position + normal.scale(20));
    newDirections.push_back(d);
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
    ofDrawCircle(position, 5);

//    ofDrawLine(position, position + (direction));
//    ofDrawBitmapString(refraction_index, position);

    ofSetColor(200, 0, 0);
    for (int i=0; i< turnedNormals.size(); i++)
        turnedNormals[i].draw();
    
    ofSetColor(200, 0, 255);
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
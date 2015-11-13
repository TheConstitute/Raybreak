#pragma once

#include "ofMain.h"
#include "ray.h"
#include "LightParticle.h"

class ofApp : public ofBaseApp{
    private:
        vector<Ray> rays;
        vector<LightParticle> particles;
    
        vector<ofPolyline> normals;
    
        std::map<int, float> refraction_lookup;
    
        void initLookup();
    
    bool mouse_pressed = false;
    
	public:
		void setup();
		void update();
		void draw();
    
    ofPolyline prism;
    
    ofPoint mouse_press_pos;
    
    
    
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

#pragma once

#include "ofMain.h"
#include "ray.h"
#include "LightParticle.h"
#include "ParticleRay.h"
#include "PrismRayCollider.h"
#include "Prism.h"

class ofApp : public ofBaseApp{
    private:
//        vector<Ray> rays;
//        vector<ofPolyline> normals;

//        vector<LightParticle> particles;

        vector<ParticleRay> rays;
        PrismRayCollider* collider;
    
    
        bool additive_colors = true;
        bool mouse_pressed = false;
        int lightcolor = 400;
        bool rainbowlight = true;
        int light_increment = 10;
        Prism* prism;
        ofPoint mouse_press_pos;
    
        vector<float> colors;
    
	public:
		void setup();
		void update();
		void draw();
		
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

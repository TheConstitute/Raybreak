#pragma once

#include "ofMain.h"
#include "ray.h"

class ofApp : public ofBaseApp{
    private:
        vector<Ray> rays;
    
    
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

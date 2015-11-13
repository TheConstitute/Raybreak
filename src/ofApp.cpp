#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    ofPoint p1, p2, p3, p4;
    
    int offsetX = 400;
    int offsetY = 200;
    int d = 200;
    
    p1.set(d/2 + offsetX, offsetY);
    int y = sqrt(pow(d,2) - pow((d/2), 2));
    p2.set(offsetX, y + offsetY);
    p3.set(offsetX + d, y + offsetY);
//    p4.set(200, 600);
    
    prism.addVertex(p1);
    prism.addVertex(p2);
    prism.addVertex(p3);
//    prism.addVertex(p4);
    
    prism.close();
    
    initLookup();

}

//--------------------------------------------------------------
void ofApp::update(){
    if(mouse_pressed){
        for(int i = 0; i< 10; i++){
        LightParticle p;
        p.init(mouse_press_pos,
               ofPoint(500, 300) - mouse_press_pos,
               1.0,
               5 * (int) ofRandom(90, 130) // 450 bis 650nm
               );
        p.setSpeed(2);
        particles.push_back(p);
        }
    }
    
    
    
    for(int i=0; i < particles.size(); i++){
        
//        if(prism.inside(particles[i].getPosition().x, particles[i].getPosition().y)){
//            particles[i].setFrequency(700);
//        }
//
//        else {
//            particles[i].setFrequency(430);
//        }
        
        for(int v = 0; v < prism.getVertices().size(); v++){
            ofPoint intersection;
            
            // determine the vertext the current one makes a line with
            // if it is the last element, the next is the first
            ofPoint next;
            if(v == prism.getVertices().size() - 1) {
                next = prism.getVertices()[0];
            } else {
                next = prism.getVertices()[v+1];
            }
            
            bool intersects = ofLineSegmentIntersection(particles[i].getPosition(), particles[i].getPosition() + particles[i].getDirection(), prism.getVertices()[v], next, intersection);

            if(intersects){
                // determine the refraction index of the new medium
                float index = 1.0;
                if(fabs(particles[i].getRefractionIndex() - 1.0) < 0.1){
                    index = refraction_lookup[particles[i].getWavelength()];
//                    ofLog() << particles[i].getWavelength() << " " << index;
                }
                
                // get the normal and make sure it points in the right direction
                // NOT SURE ABOUT THIS IMPLEMENTATION YET!!!
                ofVec2f normal = (prism.getVertices()[v] - next);
                normal = normal.getPerpendicular();
                
                ofPolyline p;
                p.addVertex(intersection);
                if(fabs(normal.angle(particles[i].getDirection())) < 90){
                    normal.rotate(180);
                }
                p.addVertex(intersection + normal.scale(10));


                normals.push_back(p);
                normal.normalize();
                
                
                particles[i].hitBorder(normal, index);
            }
        }
        
        // make the move
        particles[i].update();
        
        // remove particles that are outside the view
//        if(particles[i].getPosition().x > ofGetWidth() || particles[i].getPosition().x < 0 ||
//           particles[i].getPosition().y > ofGetHeight() || particles[i].getPosition().y < 0){
//            particles.erase(particles.begin() + i);
//            break;
//        }
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    prism.draw();
    
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(int i=0; i < particles.size(); i++){
        particles[i].draw();
    }
//    ofDisableBlendMode();
    
//    for(int i=0; i < normals.size(); i++){
//        ofPushStyle();
//        ofSetColor(0, 200, 50);
//        normals[i].draw();
//        ofPopStyle();
//    }
//    
    ofDrawBitmapString(ofGetFrameRate(), 5, 10);
    ofDrawBitmapString(particles.size(), 5, 25);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'r'){
        rays.clear();
        particles.clear();
        normals.clear();
        ofLog() << "\n\n==========================\n\n";
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_press_pos.set(x, y);
    mouse_pressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    Ray ray;
//    ray.init(mouse_press_pos, ofPoint(x, y) - mouse_press_pos, &prism);
//    rays.push_back(ray);
    
    mouse_pressed = false;
    
//    LightParticle p;
//    
//    for(int i=0; i<100; i++){
//        int rand_x = ofRandom(-5, 5);
//        int rand_y = ofRandom(-5, 5);
//        p.init(ofPoint(x + rand_x, y + rand_y),
//               ofPoint(x + rand_x, y + rand_y) - ofPoint(mouse_press_pos.x + rand_x, mouse_press_pos.y + rand_y),
//               1.0,
//               5 * (int) ofRandom(90, 130) // 450 bis 650nm
//               );
//        p.setSpeed(2);
//        particles.push_back(p);
//    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::initLookup(){
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
    refraction_lookup[1000] = 1.4504;
    refraction_lookup[1010] = 1.4503;
    refraction_lookup[1020] = 1.4502;
    refraction_lookup[1030] = 1.45;
    refraction_lookup[1040] = 1.4499;
    refraction_lookup[1050] = 1.4498;
    refraction_lookup[1060] = 1.4497;
    refraction_lookup[1070] = 1.4496;
    refraction_lookup[1080] = 1.4494;
    refraction_lookup[1090] = 1.4493;
    refraction_lookup[1100] = 1.4492;
    refraction_lookup[1110] = 1.4491;
    refraction_lookup[1120] = 1.449;
    refraction_lookup[1130] = 1.4489;
    refraction_lookup[1140] = 1.4487;
    refraction_lookup[1150] = 1.4486;
    refraction_lookup[1160] = 1.4485;
    refraction_lookup[1170] = 1.4484;
    refraction_lookup[1180] = 1.4483;
    refraction_lookup[1190] = 1.4482;
    refraction_lookup[1200] = 1.4481;
    refraction_lookup[1210] = 1.4479;
    refraction_lookup[1220] = 1.4478;
    refraction_lookup[1230] = 1.4477;
    refraction_lookup[1240] = 1.4476;
    refraction_lookup[1250] = 1.4475;
    refraction_lookup[1260] = 1.4474;
    refraction_lookup[1270] = 1.4473;
    refraction_lookup[1280] = 1.4471;
    refraction_lookup[1290] = 1.447;
    refraction_lookup[1300] = 1.4469;
    refraction_lookup[1310] = 1.4468;
    refraction_lookup[1320] = 1.4467;
    refraction_lookup[1330] = 1.4466;
    refraction_lookup[1340] = 1.4465;
    refraction_lookup[1350] = 1.4464;
    refraction_lookup[1360] = 1.4462;
    refraction_lookup[1370] = 1.4461;
    refraction_lookup[1380] = 1.446;
    refraction_lookup[1390] = 1.4459;
    refraction_lookup[1400] = 1.4458;
    refraction_lookup[1410] = 1.4457;
    refraction_lookup[1420] = 1.4455;
    refraction_lookup[1430] = 1.4454;
    refraction_lookup[1440] = 1.4453;
    refraction_lookup[1450] = 1.4452;
    refraction_lookup[1460] = 1.4451;
    refraction_lookup[1470] = 1.445;
    refraction_lookup[1480] = 1.4449;
    refraction_lookup[1490] = 1.4447;
    refraction_lookup[1500] = 1.4446;
    refraction_lookup[1510] = 1.4445;
    refraction_lookup[1520] = 1.4444;
    refraction_lookup[1530] = 1.4443;
    refraction_lookup[1540] = 1.4441;
    refraction_lookup[1550] = 1.444;
    refraction_lookup[1560] = 1.4439;
    refraction_lookup[1570] = 1.4438;
    refraction_lookup[1580] = 1.4437;
    refraction_lookup[1590] = 1.4435;
    refraction_lookup[1600] = 1.4434;
    refraction_lookup[1610] = 1.4433;
    refraction_lookup[1620] = 1.4432;
    refraction_lookup[1630] = 1.4431;
    refraction_lookup[1640] = 1.4429;
    refraction_lookup[1650] = 1.4428;
    refraction_lookup[1660] = 1.4427;
    refraction_lookup[1670] = 1.4426;
    refraction_lookup[1680] = 1.4424;
    refraction_lookup[1690] = 1.4423;
    refraction_lookup[1700] = 1.4422;
    refraction_lookup[1710] = 1.442;
    refraction_lookup[1720] = 1.4419;
    refraction_lookup[1730] = 1.4418;
    refraction_lookup[1740] = 1.4417;
    refraction_lookup[1750] = 1.4415;
    refraction_lookup[1760] = 1.4414;
    refraction_lookup[1770] = 1.4413;
    refraction_lookup[1780] = 1.4411;
    refraction_lookup[1790] = 1.441;
    refraction_lookup[1800] = 1.4409;
    refraction_lookup[1810] = 1.4407;
    refraction_lookup[1820] = 1.4406;
    refraction_lookup[1830] = 1.4405;
    refraction_lookup[1840] = 1.4403;
    refraction_lookup[1850] = 1.4402;
    refraction_lookup[1860] = 1.4401;
    refraction_lookup[1870] = 1.4399;
    refraction_lookup[1880] = 1.4398;
    refraction_lookup[1890] = 1.4397;
    refraction_lookup[1900] = 1.4395;
    refraction_lookup[1910] = 1.4394;
    refraction_lookup[1920] = 1.4392;
    refraction_lookup[1930] = 1.4391;
    refraction_lookup[1940] = 1.4389;
    refraction_lookup[1950] = 1.4388;
    refraction_lookup[1960] = 1.4387;
    refraction_lookup[1970] = 1.4385;
    refraction_lookup[1980] = 1.4384;
    refraction_lookup[1990] = 1.4382;
    refraction_lookup[2000] = 1.4381;
    refraction_lookup[2010] = 1.4379;
    refraction_lookup[2020] = 1.4378;
    refraction_lookup[2030] = 1.4376;
    refraction_lookup[2040] = 1.4375;
    refraction_lookup[2050] = 1.4373;
    refraction_lookup[2060] = 1.4372;
    refraction_lookup[2070] = 1.437;
    refraction_lookup[2080] = 1.4369;
    refraction_lookup[2090] = 1.4367;
    refraction_lookup[2100] = 1.4366;
    refraction_lookup[2110] = 1.4364;
    refraction_lookup[2120] = 1.4363;
    refraction_lookup[2130] = 1.4361;
    refraction_lookup[2140] = 1.436;
    refraction_lookup[2150] = 1.4358;
    refraction_lookup[2160] = 1.4357;
    refraction_lookup[2170] = 1.4355;
    refraction_lookup[2180] = 1.4353;
    refraction_lookup[2190] = 1.4352;
    refraction_lookup[2200] = 1.435;
    refraction_lookup[2210] = 1.4349;
    refraction_lookup[2220] = 1.4347;
    refraction_lookup[2230] = 1.4345;
    refraction_lookup[2240] = 1.4344;
    refraction_lookup[2250] = 1.4342;
    refraction_lookup[2260] = 1.434;
    refraction_lookup[2270] = 1.4339;
    refraction_lookup[2280] = 1.4337;
    refraction_lookup[2290] = 1.4335;
    refraction_lookup[2300] = 1.4334;
    refraction_lookup[2310] = 1.4332;
    refraction_lookup[2320] = 1.433;
    refraction_lookup[2330] = 1.4328;
    refraction_lookup[2340] = 1.4327;
    refraction_lookup[2350] = 1.4325;
    refraction_lookup[2360] = 1.4323;
    refraction_lookup[2370] = 1.4322;
    refraction_lookup[2380] = 1.432;
    refraction_lookup[2390] = 1.4318;
    refraction_lookup[2400] = 1.4316;
    refraction_lookup[2410] = 1.4314;
    refraction_lookup[2420] = 1.4313;
    refraction_lookup[2430] = 1.4311;
    refraction_lookup[2440] = 1.4309;
    refraction_lookup[2450] = 1.4307;
    refraction_lookup[2460] = 1.4305;
    refraction_lookup[2470] = 1.4304;
    refraction_lookup[2480] = 1.4302;
    refraction_lookup[2490] = 1.43;
    refraction_lookup[2500] = 1.4298;
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
    refraction_lookup[1000] = 1.4504;
    refraction_lookup[1010] = 1.4503;
    refraction_lookup[1020] = 1.4502;
    refraction_lookup[1030] = 1.45;
    refraction_lookup[1040] = 1.4499;
    refraction_lookup[1050] = 1.4498;
    refraction_lookup[1060] = 1.4497;
    refraction_lookup[1070] = 1.4496;
    refraction_lookup[1080] = 1.4494;
    refraction_lookup[1090] = 1.4493;
    refraction_lookup[1100] = 1.4492;
    refraction_lookup[1110] = 1.4491;
    refraction_lookup[1120] = 1.449;
    refraction_lookup[1130] = 1.4489;
    refraction_lookup[1140] = 1.4487;
    refraction_lookup[1150] = 1.4486;
    refraction_lookup[1160] = 1.4485;
    refraction_lookup[1170] = 1.4484;
    refraction_lookup[1180] = 1.4483;
    refraction_lookup[1190] = 1.4482;
    refraction_lookup[1200] = 1.4481;
    refraction_lookup[1210] = 1.4479;
    refraction_lookup[1220] = 1.4478;
    refraction_lookup[1230] = 1.4477;
    refraction_lookup[1240] = 1.4476;
    refraction_lookup[1250] = 1.4475;
    refraction_lookup[1260] = 1.4474;
    refraction_lookup[1270] = 1.4473;
    refraction_lookup[1280] = 1.4471;
    refraction_lookup[1290] = 1.447;
    refraction_lookup[1300] = 1.4469;
    refraction_lookup[1310] = 1.4468;
    refraction_lookup[1320] = 1.4467;
    refraction_lookup[1330] = 1.4466;
    refraction_lookup[1340] = 1.4465;
    refraction_lookup[1350] = 1.4464;
    refraction_lookup[1360] = 1.4462;
    refraction_lookup[1370] = 1.4461;
    refraction_lookup[1380] = 1.446;
    refraction_lookup[1390] = 1.4459;
    refraction_lookup[1400] = 1.4458;
    refraction_lookup[1410] = 1.4457;
    refraction_lookup[1420] = 1.4455;
    refraction_lookup[1430] = 1.4454;
    refraction_lookup[1440] = 1.4453;
    refraction_lookup[1450] = 1.4452;
    refraction_lookup[1460] = 1.4451;
    refraction_lookup[1470] = 1.445;
    refraction_lookup[1480] = 1.4449;
    refraction_lookup[1490] = 1.4447;
    refraction_lookup[1500] = 1.4446;
    refraction_lookup[1510] = 1.4445;
    refraction_lookup[1520] = 1.4444;
    refraction_lookup[1530] = 1.4443;
    refraction_lookup[1540] = 1.4441;
    refraction_lookup[1550] = 1.444;
    refraction_lookup[1560] = 1.4439;
    refraction_lookup[1570] = 1.4438;
    refraction_lookup[1580] = 1.4437;
    refraction_lookup[1590] = 1.4435;
    refraction_lookup[1600] = 1.4434;
    refraction_lookup[1610] = 1.4433;
    refraction_lookup[1620] = 1.4432;
    refraction_lookup[1630] = 1.4431;
    refraction_lookup[1640] = 1.4429;
    refraction_lookup[1650] = 1.4428;
    refraction_lookup[1660] = 1.4427;
    refraction_lookup[1670] = 1.4426;
    refraction_lookup[1680] = 1.4424;
    refraction_lookup[1690] = 1.4423;
    refraction_lookup[1700] = 1.4422;
    refraction_lookup[1710] = 1.442;
    refraction_lookup[1720] = 1.4419;
    refraction_lookup[1730] = 1.4418;
    refraction_lookup[1740] = 1.4417;
    refraction_lookup[1750] = 1.4415;
    refraction_lookup[1760] = 1.4414;
    refraction_lookup[1770] = 1.4413;
    refraction_lookup[1780] = 1.4411;
    refraction_lookup[1790] = 1.441;
    refraction_lookup[1800] = 1.4409;
    refraction_lookup[1810] = 1.4407;
    refraction_lookup[1820] = 1.4406;
    refraction_lookup[1830] = 1.4405;
    refraction_lookup[1840] = 1.4403;
    refraction_lookup[1850] = 1.4402;
    refraction_lookup[1860] = 1.4401;
    refraction_lookup[1870] = 1.4399;
    refraction_lookup[1880] = 1.4398;
    refraction_lookup[1890] = 1.4397;
    refraction_lookup[1900] = 1.4395;
    refraction_lookup[1910] = 1.4394;
    refraction_lookup[1920] = 1.4392;
    refraction_lookup[1930] = 1.4391;
    refraction_lookup[1940] = 1.4389;
    refraction_lookup[1950] = 1.4388;
    refraction_lookup[1960] = 1.4387;
    refraction_lookup[1970] = 1.4385;
    refraction_lookup[1980] = 1.4384;
    refraction_lookup[1990] = 1.4382;
    refraction_lookup[2000] = 1.4381;
    refraction_lookup[2010] = 1.4379;
    refraction_lookup[2020] = 1.4378;
    refraction_lookup[2030] = 1.4376;
    refraction_lookup[2040] = 1.4375;
    refraction_lookup[2050] = 1.4373;
    refraction_lookup[2060] = 1.4372;
    refraction_lookup[2070] = 1.437;
    refraction_lookup[2080] = 1.4369;
    refraction_lookup[2090] = 1.4367;
    refraction_lookup[2100] = 1.4366;
    refraction_lookup[2110] = 1.4364;
    refraction_lookup[2120] = 1.4363;
    refraction_lookup[2130] = 1.4361;
    refraction_lookup[2140] = 1.436;
    refraction_lookup[2150] = 1.4358;
    refraction_lookup[2160] = 1.4357;
    refraction_lookup[2170] = 1.4355;
    refraction_lookup[2180] = 1.4353;
    refraction_lookup[2190] = 1.4352;
    refraction_lookup[2200] = 1.435;
    refraction_lookup[2210] = 1.4349;
    refraction_lookup[2220] = 1.4347;
    refraction_lookup[2230] = 1.4345;
    refraction_lookup[2240] = 1.4344;
    refraction_lookup[2250] = 1.4342;
    refraction_lookup[2260] = 1.434;
    refraction_lookup[2270] = 1.4339;
    refraction_lookup[2280] = 1.4337;
    refraction_lookup[2290] = 1.4335;
    refraction_lookup[2300] = 1.4334;
    refraction_lookup[2310] = 1.4332;
    refraction_lookup[2320] = 1.433;
    refraction_lookup[2330] = 1.4328;
    refraction_lookup[2340] = 1.4327;
    refraction_lookup[2350] = 1.4325;
    refraction_lookup[2360] = 1.4323;
    refraction_lookup[2370] = 1.4322;
    refraction_lookup[2380] = 1.432;
    refraction_lookup[2390] = 1.4318;
    refraction_lookup[2400] = 1.4316;
    refraction_lookup[2410] = 1.4314;
    refraction_lookup[2420] = 1.4313;
    refraction_lookup[2430] = 1.4311;
    refraction_lookup[2440] = 1.4309;
    refraction_lookup[2450] = 1.4307;
    refraction_lookup[2460] = 1.4305;
    refraction_lookup[2470] = 1.4304;
    refraction_lookup[2480] = 1.4302;
    refraction_lookup[2490] = 1.43;
    refraction_lookup[2500] = 1.4298;
}
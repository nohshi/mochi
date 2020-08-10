#pragma once

#include "ofMain.h"

#include "mochi.hpp"
#include "mochi_grabber.hpp"
#include "mochi_flow.hpp"
#include "mochi_moveOnLine.hpp"
#include "mochi_regLtc.hpp"

#include "gradientMetaballs.hpp"
#include "mochiRenderer.hpp"

#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    //----------------モチモチした物体のクラス
    vector<Mochi_RegLtc> mochis;
    
    //----------------モチモチした物体をメタボールとしてレンダリングするクラス
    MochiRenderer mochiRenderer;
    
    //----------------モチモチした物体を操作するためのクラス
    Mochi_Grabber grabber;
    //Mochi_Flow flow;
    //Mochi_MoveOnLine mol;
    
    //----------------GUI
    ofxPanel gui;
    ofxFloatSlider g_a, g_d, g_ballSize;
    //ofxFloatSlider g_handRad, g_force;
    ofxToggle g_bPtsDraw;
    //ofxToggle g_bGrabber, g_bPusher, g_bPusherDebugDraw, g_bDrawHands, g_bMeshDraw, g_bGridsDraw;
    
    //----------------画面の大きさ
    float w = 1920;
    float h = 1080;
};

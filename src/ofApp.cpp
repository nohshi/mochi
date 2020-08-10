#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(40);
    ofSetFrameRate(60);
    ofSetVerticalSync(false);
    
    //-----------------------------モチを追加
    int mochiNum = 3;
    mochis.reserve(mochiNum);
    for (int i=0; i<mochiNum; i++) {
        mochis.emplace_back();
        mochis.back().setup(4, 100);
        mochis.back().setPosition(ofRandom(100, w-100), ofRandom(100, h-100));
    }
    //-----------------------------掴む対象としてモチを追加
    grabber.addTargets(mochis);
    
    //-----------------------------GUI等のセットアップ
    mochiRenderer.init(w, h);
    mochiRenderer.gui.setPosition(10, 200);
    
    gui.setup();
    gui.setName("main");
    gui.setPosition(10, 30);
    gui.add(g_a.setup("a", 0.5, 0, 1));
    gui.add(g_d.setup("d", 0.5, 0, 1));
    gui.add(g_ballSize.setup("ballSize", 200, 0, 300));
    gui.add(g_bPtsDraw.setup("drawPts", false));
    
}

//--------------------------------------------------------------
void ofApp::update(){

    //-----------------------------各種毎フレームのアップデート
    grabber.update();
    
    for (auto & mochi : mochis) {
        mochi.setParam(g_a, g_d);
        mochi.update();
    }
    
    //-----------------------------レンダラークラスに餅を追加
    for (auto & mochi : mochis) {
        mochiRenderer.addMochi(mochi, g_ballSize);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);

    //-----------------------------モチをレンダリング
    mochiRenderer.draw();
    mochiRenderer.clear();
    
    //-----------------------------デバッグ用
    if (g_bPtsDraw) {
        for (auto & mochi : mochis) {
            mochi.drawPts();
        }
    }
    
    //-----------------------------GUIの表示
    mochiRenderer.drawGui();
    gui.draw();
    grabber.drawHands();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'w') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    grabber.mousePressed(glm::vec2(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    grabber.mouseReleased();
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

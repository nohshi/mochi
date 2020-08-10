//
//  mochi_moveOnLine.hpp
//  mochi
//
//  Created by 藤田　恭輔 on 2020/01/04.
//

#ifndef mochi_moveOnLine_hpp
#define mochi_moveOnLine_hpp

#include "mochi.hpp"
#include "mochi_regLtc.hpp"
#include "ofxGui.h"
#include "ofxEasing.h"

class Mochi_MoveOnLine {
public:
    
    vector<shared_ptr<LSMD_Point>> pts;
    vector<shared_ptr<LSMD_Point>> grabbedPts;
    vector<glm::vec2> grabedPos;
    glm::vec2 anchorPos = glm::vec2(0);
    float scaleAmnt = 1;
    
    ofPolyline line;
    ofPolyline tempLine; //temporary
    bool bMousePressed = false;
    
    ofxPanel gui;
    ofxFloatSlider g_line_space, g_ball_slider, g_ball_spead;
    ofxToggle g_bMove, g_bDrawLine;
    
    
    //--------------------------------fuctions
    Mochi_MoveOnLine() {
        gui.setup();
        gui.setPosition(10, 30);
        gui.add(g_line_space.setup("line_space", 30, 0, 100));
        gui.add(g_ball_slider.setup("ball_slider", 0, 0, 1));
        gui.add(g_ball_spead.setup("ball_spead", 1, 0, 3));
        gui.add(g_bMove.setup("bMove", true));
        gui.add(g_bDrawLine.setup("bDrawLine", true));
    }
    
    void addTarget(const Mochi &_mochi) {
        for (const auto & pt : _mochi.lsmdPts) {
            pts.push_back(pt);
            if (glm::distance(pt->p0, glm::vec2(0,_mochi.scale*0.5)) < _mochi.scale*0.5) {
                this->addGrabbedPoint(pt);
            }
        }
    }
    
    void addTarget(const Mochi_RegLtc &_mochi) {
        for (const auto & pt : _mochi.lsmdPts) {
            pts.push_back(pt);
            if (glm::distance(pt->p0, glm::vec2(0,_mochi.scale*0.5)) < _mochi.scale*0.5) {
                this->addGrabbedPoint(pt);
            }
        }
    }
    
    
    void addGrabbedPoint(const shared_ptr<LSMD_Point> &_pt) {
        grabbedPts.push_back(_pt);
        grabedPos.emplace_back(_pt->p);
    }
    
    void clear() {
        pts.clear();
    }
    
    void update() {
        //--------------------------------描画
        //if(g_bMove) g_ball_slider = ofWrap(g_ball_slider + 1.f/60*g_ball_spead, 0, 1);
        if(g_bMove) g_ball_slider = g_ball_slider + /*ofGetLastFrameTime()*/1.f/60*g_ball_spead;
        
        //イージング
        float move = ofxeasing::map_clamp(g_ball_slider, 0.1, 0.9, 0, 1, ofxeasing::cubic::easeOut);
        anchorPos = line.getPointAtIndexInterpolated(line.getIndexAtPercent(move));
        glm::vec3 prev = line.getPointAtIndexInterpolated(line.getIndexAtPercent(ofClamp(move-0.00001,0,1)));
        
        glm::vec2 dir = glm::vec2(anchorPos.x, anchorPos.y) - glm::vec2(prev.x, prev.y);
        float theta = glm::orientedAngle(glm::normalize(glm::vec2(0,1)),glm::normalize(dir));
        
        //--------------------------------モチの大きさを時間で変化させるやつ
        /*
         float scalePct = 1;
         float a = 0.2; //attack
         float r = 0.8; //release
         if (g_ball_slider < a) scalePct = ofxeasing::map_clamp(g_ball_slider, 0,a, 0,1, ofxeasing::cubic::easeOut);
         if (g_ball_slider > r) scalePct = ofxeasing::map_clamp(g_ball_slider, r,1, 1,0, ofxeasing::cubic::easeIn);
         this->scale(scalePct);
         */
        
        for (int i=0; i<grabbedPts.size(); i++) {
            glm::vec2 p;
            p = glm::rotate(grabedPos[i], theta);
            grabbedPts[i]->p = p + anchorPos;
        }
    }
    
    //スケーリングするやつ
    void scale(float amnt) { // 0.f <= _amnt <= 1.f
        amnt = glm::max(amnt, 0.01f);
        for (auto & pt : pts) {
            pt->p0 /= scaleAmnt;
            pt->p0 *= amnt;
        }
        for (auto & gp : grabedPos) {
            gp /= scaleAmnt;
            gp *= amnt;
        }
        scaleAmnt = amnt;
    }
    
    void debugDraw() {
        for (int i=0; i<grabbedPts.size(); i++) {
            ofPushStyle();
            ofSetColor(255, 144, 10);
            ofDrawCircle(grabbedPts[i]->p, 6);
            ofPopStyle();
        }
    }
    
    //----------------------------------ラインの描画
    void drawLine() {
        ofSetColor(255);
        line.draw();
        for (const auto &v : line.getVertices()){
            ofSetColor(255,100,100);
            ofDrawCircle(v, 3);
        }
        
        if (ofGetMousePressed()) {
            ofSetColor(255);
            tempLine.draw();
            for (const auto &v : tempLine.getVertices()){
                ofSetColor(100,100,255);
                ofDrawCircle(v, 3);
            }
        }
    }
    
    //--------------------------------gui
    void drawGui() {
        ofSetColor(255);
        gui.draw();
    }
    
    //-----------------------------mouse
    //--------------------------------------------------------------
    void mouseDragged(int x, int y, int button){
        if (!g_bDrawLine) return;
        
        if (bMousePressed) {
            tempLine.addVertex(x, y);
        }
    }
    
    //--------------------------------------------------------------
    void mousePressed(int x, int y, int button){
        if (!g_bDrawLine) return;
        
        bMousePressed = true;
        
    }
    
    //--------------------------------------------------------------
    void mouseReleased(int x, int y, int button){
        if (!g_bDrawLine) return;
        
        bMousePressed = false;
        line = tempLine.getResampledBySpacing(g_line_space).getSmoothed(2);
        tempLine.clear();
    }
    
    
    
};

#endif /* mochi_moveOnLine_hpp */

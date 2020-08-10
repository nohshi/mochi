//
//  grabber.hpp
//  ShapeMarchingDynamics2
//
//  Created by 藤田　恭輔 on 2019/11/22.
//

#ifndef grabber_hpp
#define grabber_hpp

#include "ofMain.h"
#include "lsmd.hpp"

class LSMD_Grabber {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    vector<glm::vec2> grabedPs;
    vector<bool> bGrab;
    float radius = 100;
    
    LSMD_Grabber() {};
    
    virtual void addTarget(const shared_ptr<LSMD_Point> &_pt) {
        pts.push_back(_pt);
        bGrab.push_back(false);
        grabedPs.emplace_back(glm::vec2(0));
    }
    
    virtual void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts) {
        for (const auto _pt : _pts) {
            addTarget(_pt);
        }
    }
    
    void clear() {
        pts.clear();
    }
    
    void update() {
        for (int i=0; i<pts.size(); i++) {
            if (bGrab[i]) {
                pts[i]->p = grabedPs[i] + glm::vec2(ofGetMouseX(), ofGetMouseY());
            }
        }
    }
    
    void drawHands() {
        ofPushStyle();
        ofSetColor(30, 255, 100);
        ofNoFill();
        ofDrawCircle(glm::vec2(ofGetMouseX(), ofGetMouseY()), radius);
        ofPopStyle();
    }
    
    void debugDraw() {
        for (int i=0; i<pts.size(); i++) {
            ofPushStyle();
            if (bGrab[i]) ofSetColor(255, 144, 10);
            else ofSetColor(10, 144, 255);
            ofDrawCircle(pts[i]->p, 6);
            ofPopStyle();
        }
    }
    
    void mousePressed(const glm::vec2 &_mouse) {
        for (int i=0; i<pts.size(); i++) {
            if (glm::distance(_mouse, pts[i]->p) < radius) {
                bGrab[i] = true;
                grabedPs[i] = pts[i]->p - _mouse;
            }
        }
    }
    
    void mouseReleased(){
        for (int i=0; i<pts.size(); i++) {
            bGrab[i] = false;
        }
    }
    
    
};

#endif /* grabber_hpp */

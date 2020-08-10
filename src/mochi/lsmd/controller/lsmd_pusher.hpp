//
//  lsmd_pusher.hpp
//  lsmd_test2
//
//  Created by 藤田　恭輔 on 2019/12/01.
//

#ifndef lsmd_pusher_hpp
#define lsmd_pusher_hpp

#include "ofMain.h"
#include "lsmd.hpp"

class LSMD_Pusher {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    
    float radius = 50;
    float k = 3000; //バネ係数
    
    glm::vec2 handPos;
    
    void addTarget(const shared_ptr<LSMD_Point> &_pt) {
        pts.push_back(_pt);
    }
    
    void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts) {
        for (const auto _pt : _pts) {
            addTarget(_pt);
        }
    }
    
    void clear() {
        pts.clear();
    }
    
    void update() {
        for (const auto _pt : pts) {
            float d = glm::max(radius - glm::length(handPos - _pt->p), 0.f);
            glm::vec2 f = -k * d * (handPos - _pt->p)/glm::length(handPos - _pt->p);
            //_pt->p += glm::min(f * glm::pow(ofGetLastFrameTime(),2), radius);
            _pt->addForce(f);
            glm::vec2 dir = _pt->p-handPos;
            if (glm::length(dir) > radius) continue;
            _pt->p = handPos + glm::normalize(dir)*radius;
        }
    }
    
    void drawHands() {
        ofPushStyle();
        ofSetColor(30, 100, 255);
        ofNoFill();
        ofDrawCircle(handPos, radius);
        ofPopStyle();
    }
    
    void debugDraw() {
        for (int i=0; i<pts.size(); i++) {
            ofPushStyle();
            ofSetColor(10, 144, 255);
            ofDrawCircle(pts[i]->p, 6);
            ofPopStyle();
        }
    }
    
    void mousePressed(const glm::vec2 &_mouse) {
        
    }
    
    void mouseReleased(){
        
    }
    
    
};


#endif /* lsmd_pusher_hpp */

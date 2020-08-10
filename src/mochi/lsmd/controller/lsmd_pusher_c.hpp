//
//  lsmd_pusher_c.hpp
//  lsmd_test2_pusher
//
//  Created by 藤田　恭輔 on 2019/12/03.
//

#ifndef lsmd_pusher_c_hpp
#define lsmd_pusher_c_hpp

#include "ofMain.h"
#include "lsmd.hpp"

class LSMD_Pusher_c {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    float radius = 50;
    glm::vec2 handPos; //円の中心位置
    vector<bool> bConstrained;
    vector<glm::vec2> relativePos; //相対位置
    
    
    //-------------------------------------------------------ポインタ追加するやつ
    void addTarget(const shared_ptr<LSMD_Point> &_pt) {
        pts.push_back(_pt);
        bConstrained.push_back(false);
        relativePos.emplace_back(0);
    }
    
    void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts) {
        for (const auto _pt : _pts) {
            addTarget(_pt);
        }
    }
    
    void clear() {
        pts.clear();
        bConstrained.clear();
    }
    
    
    //-------------------------------------------------------処理
    void update() {
        for (int i=0; i<pts.size(); i++) {
            
            float dist = glm::distance(pts[i]->p, handPos);
            /*
            if ( glm::length(relativePos[i]) < dist-1 ){
                bConstrained[i] = false;
            }
            
            if ( dist < radius ) {
                bConstrained[i] = true;
                relativePos[i] = pts[i]->p - handPos;
            }
            
            if (bConstrained[i]==true) {
                pts[i]->p = relativePos[i] + handPos;
            }
            */
            if ( glm::length(relativePos[i]) < dist+1/*radius/10*/ ) {
                bConstrained[i] = false;
            }
            
            if (bConstrained[i] == true) {
                glm::vec2 &dir = relativePos[i];
                pts[i]->p = handPos + glm::normalize(dir)*radius;
                continue;
            }
            
            if ( dist < radius ) {
                relativePos[i] = pts[i]->p - handPos;
                glm::vec2 &dir = relativePos[i];
                pts[i]->p = handPos + glm::normalize(dir)*radius;
                bConstrained[i] = true;
            }
        }
    }
        
        
    //-------------------------------------------------------描画
    void drawHands() {
        ofPushStyle();
        ofSetColor(30, 100, 255);
        ofNoFill();
        ofDrawCircle(handPos, radius);
        ofPopStyle();
    }
    
    
    void debugDraw() {
        for (int i=0; i<pts.size(); i++) {
            if (!bConstrained[i]) continue;
            ofPushStyle();
            ofSetColor(10, 144, 255);
            ofDrawCircle(pts[i]->p, 6);
            ofPopStyle();
        }
    }
        
    
    
    
    
    
    
};

#endif /* lsmd_pusher_c_hpp */

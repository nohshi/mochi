//
//  lsmd_weighting.hpp
//  lsmd_test2_triGrid2_vectorField
//
//  Created by 藤田　恭輔 on 2020/01/01.
//

#ifndef lsmd_weighting_hpp
#define lsmd_weighting_hpp

#include "ofMain.h"
#include "lsmd.hpp"

class LSMD_Weighting {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    glm::vec2 center;
    glm::vec2 goal;
    vector<float> w; //weight
    
    
    LSMD_Weighting() { }
    
    
    virtual void addTarget(const shared_ptr<LSMD_Point> &_pt, const float &_scale) {
        pts.push_back(_pt);
        glm::vec2 offset = glm::vec2(0, _scale/4);
        //w.push_back( ofClamp(1.-glm::length((_pt->p0+offset)/_scale)*2.5, 0,1) );
        w.push_back( ofClamp(glm::length((_pt->p0+offset)/_scale)*5.5, 0,3)/3 );
        //w.push_back( (_pt->p0.y+_scale/2)/_scale );
    }
    
    virtual void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts, const float &_scale) {
        for (const auto _pt : _pts) {
            addTarget(_pt, _scale);
        }
    }
    
    void clear() {
        pts.clear();
    }
    
    
    virtual void update() {
        if (!ofGetMousePressed()) return;
    }
    
    
    virtual void debugDraw() {
        for (int i=0; i<pts.size(); i++) {
            ofPushStyle();
            ofSetColor(255*w[i], 0, 0);
            ofDrawCircle(pts[i]->p, 6);
            ofPopStyle();
        }
    }
    
};

#endif /* lsmd_weighting_hpp */

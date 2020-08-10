//
//  lsmd_attractor.hpp
//  lsmd_test2_triGrid2_exp2
//
//  Created by 藤田　恭輔 on 2019/12/25.
//

#ifndef lsmd_attractor_hpp
#define lsmd_attractor_hpp

#include "ofMain.h"
#include "lsmd.hpp"
#include "ofxEasing.h"

class LSMD_Attractor {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    //bool bAttract;
    glm::vec2 center;
    glm::vec2 target;
    
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
        if (!ofGetMousePressed()) return;
        
        glm::vec2 force;
        float d = glm::distance(target,center) / 500.;
        d = 1 - ofClamp(d, 0, 1);
        d = 1.0 - pow(glm::max(0.f, float(abs(d) * 2 - 1)), 3.5);
        //d = ;
        force = glm::normalize(target - center) * d * 30000.;
        
        for (auto & pt : pts) {
            pt->addForce(force);
            //pt->v += ofGetFrameRate()/force; //こっちの方が質量に依存しない
        }
    }
    
    
    
};

#endif /* lsmd_attractor_hpp */

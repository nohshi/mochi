//
//  lsmd_attractor_weighting.hpp
//  lsmd_test2_triGrid2_exp2
//
//  Created by 藤田　恭輔 on 2019/12/25.
//

#ifndef lsmd_attractor_weighting_hpp
#define lsmd_attractor_weighting_hpp

#include "ofMain.h"
#include "lsmd.hpp"
#include "ofxEasing.h"

class LSMD_Attractor_Weighting {
public:
    vector<shared_ptr<LSMD_Point>> pts;
    //bool bAttract;
    glm::vec2 center;
    glm::vec2 goal;
    vector<float> w; //weight
    
    void addTarget(const shared_ptr<LSMD_Point> &_pt, const float &_size) {
        pts.push_back(_pt);
        w.push_back( (_pt->p0.y+_size/2)/_size );
    }
    
    void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts, const float &_size) {
        for (const auto _pt : _pts) {
            addTarget(_pt, _size);
        }
    }
    
    void clear() {
        pts.clear();
    }
    
    void setGoal(const glm::vec2 &_target) {
        goal = _target;
    }
    
    void setCenter(const glm::vec2 &_center) {
        center = _center;
    }
    
    virtual void update() {
        if (!ofGetMousePressed()) return;
        
        glm::vec2 force;
        float d = glm::distance(goal,center) / 500.;
        d = 1 - ofClamp(d, 0, 1);
        d = 1.0 - pow(glm::max(0.f, float(abs(d) * 2 - 1)), 3.5);
        //d = ;
        force = glm::normalize(goal - center) * d * 80000.;
        /*
        for (auto & pt : pts) {
            pt->addForce(force);
            //pt->v += ofGetFrameRate()/force; //こっちの方が質量に依存しない
        }*/
        for (int i=0; i<pts.size(); i++) {
            pts[i]->addForce(force * w[i]);
        }
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


#endif /* lsmd_attractor_weighting_hpp */

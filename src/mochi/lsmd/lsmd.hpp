//
//  lsmd.hpp
//  lsmd_test
//
//  Created by 藤田　恭輔 on 2019/11/28.
//

#ifndef lsmd_hpp
#define lsmd_hpp

#include "ofMain.h"

struct LSMD_Point {
    int id;
    glm::vec2 p = glm::vec2(0); //位置(smdの式においてはx)
    glm::vec2 p0 = glm::vec2(0); //初期位置（合わせるべき基準点）
    float m = 1.00f; //質量
    glm::vec2 f = glm::vec2(0); //外力
    glm::vec2 v = glm::vec2(0); //外力
    
    LSMD_Point (){
    }
    
    LSMD_Point (const glm::vec2 &_p, const float &_m = 1.00f){
        p = _p;
        p0 = p;
        m = _m;
    }
    
    void setPosition(const glm::vec2 &_p) {
        p = _p;
    }
    
    void addForce(const glm::vec2 &_f){
        f += _f;
    }
    
    const int & getId() {
        return id;
    }
    
    void debugDraw() const {
        ofPushStyle();
        ofFill();
        ofSetColor(140, 144, 255*m/2.f);
        ofDrawCircle(p, 4);
        ofPopStyle();
    };
};

class LSMD {
public:
    
    
    
    LSMD () {
        h = 1.f/60;
        a = .1;
        d = .1;
    }
    
    
    
    //-----------------------------------------------objects
    vector<shared_ptr<LSMD_Point>> tgts;
    vector<vector<shared_ptr<LSMD_Point>>> clusters;
    vector<glm::vec2> g; //goal positions
    
    float h; //deltaTime
    float a; //硬さ係数
    float d; //減衰係数/振動抑制 damping
    glm::mat2 P0; //前フレームの直交行列P
    bool isUseP0 = false; //P0を使うかどうかの判定
    int idCount = 0;
    
    //--------------------初期化及び頂点をセット
    void addTarget(const shared_ptr<LSMD_Point> &_pt) {
        tgts.push_back(_pt);
        tgts.back()->id = idCount;
        idCount++;
        g.emplace_back(0);
    }
    
    void addTargets(const vector<shared_ptr<LSMD_Point>> &_pts) {
        for (const auto _pt : _pts) {
            addTarget(_pt);
        }
    }
    
    void clear(){
        tgts.clear();
        clusters.clear();
    }
    
    
    //-------------------------円形のクラスタを作る
    void makeClusters(int _r) {
        clusters.resize(tgts.size());
        
        for (int i=0; i<tgts.size(); i++) {
            glm::vec2 & tip = tgts[i]->p0;
            for (const auto & tn : tgts) {
                if ( glm::distance(tip, tn->p0) < _r ) {
                    clusters[i].emplace_back(tn);
                }
            }
        }
    }
    
    //-------------------------四角のクラスタを作る
    void makeClustersByQuad(int _w) {
        _w += 1;
        clusters.resize(tgts.size());
        
        for (int i=0; i<tgts.size(); i++) {
            glm::vec2 & tip = tgts[i]->p0; //現在見てるtgt
            for (const auto & tn : tgts) { //tnは周りのtgt
                if ( tn->p0.x - tip.x <  _w &&
                     tn->p0.x - tip.x > -_w &&
                     tn->p0.y - tip.y <  _w &&
                     tn->p0.y - tip.y > -_w    ) {
                    clusters[i].emplace_back(tn);
                }
            }
        }
        
    }
    
    //-------------------------硬さaと減衰係数dのセット
    virtual void setParam(const float &_a, const float &_d) {
        a = _a;
        d = _d;
    }
    
    //--------------------SMDの計算式を実行
    virtual void calculate();
    
    
    
    
    //--------------------ヤコビ法
    std::tuple<glm::mat2, glm::mat2> jacobi22(glm::mat2 M);
    
};

#endif /* lsmd_hpp */

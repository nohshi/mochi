//
//  mochi.hpp
//  lsmd_test2_triGrid2_vectorField2
//
//  Created by 藤田　恭輔 on 2020/01/03.
//

#ifndef mochi_hpp
#define mochi_hpp

#include "ofMain.h"
#include "lsmd.hpp"
#include "lsmd_tri_grids.hpp"
#include "my_ofImage.hpp"



class Mochi {
public:
    //----------------LSMD
    vector<shared_ptr<LSMD_Point>> lsmdPts;
    LSMD lsmd;
    LSMD_TriGrids triGrids;
    My_ofImage tex;
    float scale = 1;
    
    float a = 0.5;
    float d = 0.5;
    
    
    //--------------------------constructor
    Mochi() {
        
    }
    /*
    Mochi(const int &_res, const float &_scale) {
        setup(_res, _scale);
    }
    */
    
    
    //--------------------------setup
    virtual void setup(const int &_res, const float &_scale) { //res->resolution
        ofDisableArbTex();
        tex = My_ofImage();
        tex.load("nikonikoman-original.png");
        ofEnableArbTex();
        lsmdPts = triGrids.init(_res, tex, _scale);
        lsmd.addTargets(lsmdPts);
        lsmd.makeClusters(_scale*0.3);
        scale = _scale;
    }
    
    //--------------------------transform
    void setPosition(const glm::vec2 &_pos) {
        for (auto & pt : lsmdPts) {
            pt->p = pt->p0 + _pos;
        }
    }
    void setPosition(const float _x, const float _y) {
        setPosition(glm::vec2(_x, _y));
    }
    
    void setScale(const float &_scale) {
        for (auto & pt : lsmdPts) {
            pt->p0 /= scale;
            pt->p0 *= _scale;
        }
        scale = _scale;
    }
    
    void setParam(const float &_a, const float &_d) {
        a = _a;
        d = _d;
    }
    
    //--------------------------you have to call this every frame
    void update() {
        lsmd.setParam(a, d);
        lsmd.calculate();
    }
    
    //--------------------------draw
    void drawPts();
    virtual void drawGrids();
    virtual void drawMesh();
    
    //--------------------------自らの幾何学重心を返す
    glm::vec2 getPosition();
    
};

#endif /* mochi_hpp */

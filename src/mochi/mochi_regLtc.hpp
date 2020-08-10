//
//  mochi_regLtc.hpp
//  mochi2_regGrid
//
//  Created by 藤田　恭輔 on 2020/03/27.
//

#ifndef mochi_regLtc_hpp
#define mochi_regLtc_hpp


#include "ofMain.h"
#include "lsmd.hpp"
#include "lsmd_tri_grids.hpp"
#include "my_ofImage.hpp"
#include "lsmd_reg_grids.hpp"
#include "Mochi.hpp"

class Mochi_RegLtc : public Mochi{
public:
    
    LSMD_RegGrids regGrids;
    //--------------------------setup
    void setup(const int &_res, const float &_scale) override { //res->resolution
        ofDisableArbTex();
        tex = My_ofImage();
        tex.load("nikonikoman-original.png");
        ofEnableArbTex();
        lsmdPts = regGrids.init(_res, tex, _scale);
        
        lsmd.addTargets(lsmdPts);
        lsmd.makeClustersByQuad(_scale*0.3);
        scale = _scale;
    }
    
    //--------------------------draw
    
     void drawGrids() override{
        
    }
     void drawMesh() override{}
};


#endif /* mochi_regLtc_hpp */




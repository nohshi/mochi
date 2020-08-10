//
//  lsmd_w_vf.hpp
//  lsmd_test2_triGrid2_vectorField
//
//  Created by 藤田　恭輔 on 2020/01/01.
//

#ifndef lsmd_w_vf_hpp
#define lsmd_w_vf_hpp

#include "lsmd_weighting.hpp"
#include "vectorField.hpp"

class LSMD_W_Vf : public LSMD_Weighting {
public:
    VectorField2d vf;
    float forceAmnt = 10000;
    
    LSMD_W_Vf() {
        vf.setupTornado();
    }
    
    LSMD_W_Vf(const glm::vec2 &_range, const glm::vec2 &_offset) {
        vf = VectorField2d(_range, _offset);
        vf.setupTornado();
    }
    
    void update() {
        for (int i=0; i<pts.size(); i++) {
            glm::vec2 f = vf.lookup(pts[i]->p);
            f *= forceAmnt * w[i];
            pts[i]->addForce(f);
        }
    }
    
    void display() {
        vf.display();
    }
    
};

#endif /* lsmd_w_vf_hpp */

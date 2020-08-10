//
//  mochi_draw.hpp
//  mochi2
//
//  Created by 藤田　恭輔 on 2020/01/06.
//

#ifndef mochi_draw_hpp
#define mochi_draw_hpp

#include "gradientMetaballs.hpp"
#include "mochi.hpp"

class MochiRenderer : public GradientMetaballs {
public:
    void addMochi(const Mochi &_mochi, const float &_pointSize) {
        for (const auto & pt : _mochi.lsmdPts) {
            this->addPoint(glm::vec3(pt->p.x, pt->p.y, 0), _pointSize);
        }
    }
    
    
};


#endif /* mochi_draw_hpp */

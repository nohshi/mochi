//
//  mochi_flow.hpp
//  mochi
//
//  Created by 藤田　恭輔 on 2020/01/03.
//

#ifndef mochi_flow_hpp
#define mochi_flow_hpp

#include "mochi.hpp"
#include "mochi_regLtc.hpp"
#include "lsmd_w_vf.hpp"

class Mochi_Flow : public LSMD_W_Vf  {
public:
    
    Mochi_Flow() {}
    
    Mochi_Flow(const glm::vec2 &_range, const glm::vec2 &_offset) : LSMD_W_Vf(_range, _offset) {}
    
    void addTarget(const Mochi &_mochi) {
        LSMD_W_Vf::addTargets(_mochi.lsmdPts, _mochi.scale);
    }
    
    void addTargets(const vector<Mochi> &_mochis) {
        for (const auto & mochi : _mochis) {
            LSMD_W_Vf::addTargets(mochi.lsmdPts, mochi.scale);
        }
    }
    
    void addTarget(const Mochi_RegLtc &_mochi) {
        LSMD_W_Vf::addTargets(_mochi.lsmdPts, _mochi.scale);
    }
    
    void addTargets(const vector<Mochi_RegLtc> &_mochis) {
        for (const auto & mochi : _mochis) {
            LSMD_W_Vf::addTargets(mochi.lsmdPts, mochi.scale);
        }
    }
};

#endif /* mochi_flow_hpp */

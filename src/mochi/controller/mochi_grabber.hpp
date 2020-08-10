//
//  mochi_grabber.hpp
//  mochi
//
//  Created by 藤田　恭輔 on 2020/01/03.
//

#ifndef mochi_grabber_hpp
#define mochi_grabber_hpp

#include "mochi.hpp"
#include "mochi_regLtc.hpp"
#include "lsmd_grabber.hpp"


class Mochi_Grabber : public LSMD_Grabber {
public:
    void addTarget(const Mochi &_mochi) {
        LSMD_Grabber::addTargets(_mochi.lsmdPts);
    }
    
    void addTargets(const vector<Mochi> &_mochis) {
        for (const auto & mochi : _mochis) {
            LSMD_Grabber::addTargets(mochi.lsmdPts);
        }
    }
    
    void addTarget(const Mochi_RegLtc &_mochi) {
        LSMD_Grabber::addTargets(_mochi.lsmdPts);
    }
    
    void addTargets(const vector<Mochi_RegLtc> &_mochis) {
        for (const auto & mochi : _mochis) {
            LSMD_Grabber::addTargets(mochi.lsmdPts);
        }
    }
};

#endif /* mochi_grabber_hpp */

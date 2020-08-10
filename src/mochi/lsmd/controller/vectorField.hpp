//
//  vectorField.hpp
//  brushSticker
//
//  Created by 藤田　恭輔 on 2019/10/08.
//

#ifndef vectorField_hpp
#define vectorField_hpp

#include "ofMain.h"
#include "ofxFastNoise.h"

class VectorField2d {
public:
    glm::vec2 resolution;
    glm::vec2 range;
    glm::vec2 offset;
    glm::vec2 scale = glm::vec2(1,1);
    bool bUpdated;
    std::vector< std::vector<glm::vec2> > vectors;
    ofPixels viewer;
    ofImage displayBuffer;
    
    VectorField2d() {
        range = glm::vec2(ofGetWidth(), ofGetHeight());
        resolution = glm::vec2(1,1);
        offset = glm::vec2(0,0);
        init();
    }
    
    VectorField2d(const glm::vec2 &_range){
        range = _range;
        resolution = glm::vec2(1,1);
        offset = glm::vec2(0,0);
        init();
    }
    
    
    VectorField2d(const glm::vec2 &_range, const glm::vec2 &_offset){
        range = _range;
        resolution = glm::vec2(1,1);
        offset = _offset;
        init();
    }
    
    VectorField2d(const glm::vec2 &_range, const glm::vec2 &_scale, const glm::vec2 &_offset){
        range = _range;
        resolution = glm::vec2(1,1);
        offset = _offset;
        scale = _scale;
        init();
    }
    
    void init();
    void setupPerlin();
    void setupCubic();
    void setupTornado();
    void setupCustom1();
    void setupCustom2();
    void setupCustom3();
    void setupCustom4();
    
    const glm::vec2 & lookup(const glm::vec2 &_pos);
    void display();
    
private:
    glm::vec2 limit(const glm::vec2 &v, float maximum) {
        auto l = glm::length(v);
        if (l > maximum) {
            return glm::normalize(v) * maximum;
        }
        return v;
    }
};

#endif /* vectorField_hpp */

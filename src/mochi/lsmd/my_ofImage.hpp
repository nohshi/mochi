//
//  my_ofImage.hpp
//  getColorAtPercentFromImage
//
//  Created by 藤田　恭輔 on 2019/12/01.
//

#ifndef my_ofImage_hpp
#define my_ofImage_hpp

#include "ofMain.h"

class My_ofImage : public ofImage {
public:
    
    ofColor getColorAtPos(const glm::vec2 &_pos) {
        ofPixels &pixels = this->getPixels();
        if ( pixels.getWidth() < _pos.x || pixels.getHeight() < _pos.y ) {
            cout << "error : My_ofImage : pos is too large" << endl;
            return ofColor(0,0,0,0);
        }else{
            int c0x = _pos.x;
            int c0y = _pos.y;
            ofColor c0 = pixels.getColor(c0x  , c0y  );
            ofColor c1 = pixels.getColor(c0x+1, c0y  );
            ofColor c2 = pixels.getColor(c0x  , c0y+1);
            ofColor c3 = pixels.getColor(c0x+1, c0y+1);
            glm::vec2 pct = glm::vec2(_pos.x-c0x, _pos.y-c0y);
            ofColor c;
            c = c0.getLerped(c1, pct.x);
            c.lerp(c2.getLerped(c3, pct.x), pct.y);
            return c;
        }
    }
    
    ofColor getColorAtPercent(glm::vec2 _pct) {
        _pct = glm::clamp(_pct, 0.f,1.f);
        ofPixels &pixels = this->getPixels();
        glm::vec2 pos;
        pos.x = ofMap(_pct.x, 0, 1, 0, pixels.getWidth());
        pos.y = ofMap(_pct.y, 0, 1, 0, pixels.getHeight());
        
        return getColorAtPos(pos);
    }
    /*
    ofColor getColorInGrid(const glm::vec2 &_p00, const glm::vec2 &_p01,
                           const glm::vec2 &_p10, const glm::vec2 &_p11) {
        ofPixels &pixels = this->getPixels();
        
    }*/
    
};


#endif /* my_ofImage_hpp */

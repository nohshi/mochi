//
//  gradientMetaballs.hpp
//  textureMetaball_add
//
//  Created by 藤田　恭輔 on 2019/12/21.
//

#ifndef gradientMetaballs_hpp
#define gradientMetaballs_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "gradientRenderer.hpp"


class GradientMetaballs {
public:
    
    GradientMetaballs() {
        gui.setup();
        gui.setName("GradientMetaballs");
        gui.add(g_threshold.setup("threshold", 1, 0, 1));
        gui.add(doShader.setup(true));
        
        shader.load("gradientMetaballs/drawShaders/shader");
    };
    
    void init(const int &_width, const int &_height) {
        ofFbo::Settings settings;
        settings.width = _width;
        settings.height = _height;
        settings.internalformat = GL_RGB16F;
        settings.numSamples = 0;
        fbo.allocate(settings);
    }
    
    void addPoint(const glm::vec3 &_p, const float &_pointSize){
        pRenderer.addPoint(_p, ofFloatColor(1), _pointSize);
    }
    
    void draw() {
        fbo.begin();
        {
            ofClear(0,0,0,255);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            pRenderer.draw();
            ofEnableAlphaBlending();
            pRenderer.clear();
        }
        fbo.end();
        
        if(doShader) {
            shader.begin();
            shader.setUniform1f("u_threshold", g_threshold);
        }
        fbo.draw(0, 0);
        if(doShader) shader.end();
    }
    
    void clear() {
        pRenderer.clear();
    }
    
    void drawGui() {
        gui.draw();
    }
    
    ofxPanel gui;
    ofxFloatSlider g_threshold;
    ofxToggle doShader;
    
    ofFbo fbo;
    ofShader shader;
    
    GradientRenderer pRenderer;
};


#endif /* gradientMetaballs_hpp */


#pragma once

#include "ofMain.h"

#pragma once

#include "ofMain.h"
#include "pointsRenderer.hpp"

class GradientRenderer : public PointsRenderer {
public:
    
    GradientRenderer() : PointsRenderer(false){
        
        shader.load("gradientMetaballs/ballGradientShader/shader.vert",
                    "gradientMetaballs/ballGradientShader/shader.frag",
                    "gradientMetaballs/ballGradientShader/shader.geom");
    }
    
    
    
};


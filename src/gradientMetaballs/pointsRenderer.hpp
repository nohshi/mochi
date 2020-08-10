
#pragma once

#include "ofMain.h"

class PointsRenderer {
public:
    PointsRenderer(bool loadShaders = true);
    
    //you add points with these functions
    void addVertex(const glm::vec3 &_p);
    void addColor(const ofFloatColor &_col);
    void addPointSize(const float &_pointSize);
    void addPoint(const glm::vec3 &_p, const ofFloatColor &_col, const float &_pointSize);
    
    void addVertices(const vector<glm::vec3> &_ps);
    void addColors(const vector<ofFloatColor> &_cols);
    void addPointSizes(const vector<float> &_pointSizes);
    void addPoints(const vector<glm::vec3> &_ps, const vector<ofFloatColor> &_cols, const vector<float> &_pointSizes);
    
    void clear();
    void clearColors();
    void clearVertices();
    void clearPointSizes();
    
    //then draw added points
    virtual void draw();
    
    ofVboMesh vboMesh;
    ofShader shader;
    bool doShader = true;
    vector<float> pointsSize;
    
protected:
    bool bSetCustomAttributes = false;
};



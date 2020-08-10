//
//  pointsRenderer.cpp
//
//  Created by 藤田　恭輔 on 2019/04/17.
//

#include "pointsRenderer.hpp"


PointsRenderer::PointsRenderer(bool loadShaders){
    vboMesh.setMode(OF_PRIMITIVE_POINTS);
    pointsSize.reserve(50);
    
    if (loadShaders) {
        shader.setGeometryInputType(GL_POINTS);
        shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
        shader.setGeometryOutputCount(4);
        shader.load("pointsShader/shader.vert","pointsShader/shader.frag","pointsShader/shader.geom");
    }
    
}
//-------------------------
void PointsRenderer::addVertex(const glm::vec3 &_p){
    vboMesh.addVertex(_p);
}

void PointsRenderer::addPointSize(const float &_pointSize){
    pointsSize.push_back(_pointSize);
}

void PointsRenderer::addColor(const ofFloatColor &_col){
    vboMesh.addColor(_col);
}

void PointsRenderer::addPoint(const glm::vec3 &_p, const ofFloatColor &_col, const float &_pointSize){
    this->addVertex(_p);
    this->addColor(_col);
    this->addPointSize(_pointSize);
}
//--------------------
void PointsRenderer::addVertices(const vector<glm::vec3> &_ps){
    vboMesh.addVertices(_ps);
}

void PointsRenderer::addPointSizes(const vector<float> &_pointSizes){
    for (int i=0; i<_pointSizes.size(); i++) {
        pointsSize.push_back(_pointSizes[i]);
    }
}

void PointsRenderer::addColors(const vector<ofFloatColor> &_cols){
    vboMesh.addColors(_cols);
}

void PointsRenderer::addPoints(const vector<glm::vec3> &_ps, const vector<ofFloatColor> &_cols, const vector<float> &_pointSizes){
    this->addVertices(_ps);
    this->addColors(_cols);
    this->addPointSizes(_pointSizes);
}
//--------------------
void PointsRenderer::draw(){
    if(doShader) {
        shader.begin();
        //ofEnableAlphaBlending();
    }
    
    //-------------------------------------------二回目以降はupdateAttributeDataを実行した方がいい気がする
    if(!bSetCustomAttributes) {
        vboMesh.getVbo().setAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], 1, pointsSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
        bSetCustomAttributes = true;
    }else {
        vboMesh.getVbo().updateAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], pointsSize.size());
    }
    
    vboMesh.draw();
    
    if(doShader) {
        shader.end();
    }
    
    
    
}


void PointsRenderer::clear() {
    vboMesh.clear();
    pointsSize.clear();
}


void PointsRenderer::clearColors() {
    vboMesh.clearColors();
}

void PointsRenderer::clearVertices() {
    vboMesh.clearVertices();
}

void PointsRenderer::clearPointSizes() {
    pointsSize.clear();
}





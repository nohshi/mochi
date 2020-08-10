//
//  mochi.cpp
//  lsmd_test2_triGrid2_vectorField2
//
//  Created by 藤田　恭輔 on 2020/01/03.
//

#include "mochi.hpp"



//--------------------------draw
void Mochi::drawPts() {
    int index=0;
    for (const auto & pt : lsmdPts) {
        pt->debugDraw();
        ofSetColor(100, 100, 255);
        ofDrawBitmapString(ofToString(index), pt->p.x, pt->p.y);
        index ++;
    }
    
    //---------display clusters
    int clusterId = int(ofWrap(ofGetElapsedTimef()*10, 0, lsmd.clusters.size()));
    for (const auto & p : lsmd.clusters[clusterId]) {
        ofPushStyle();
        ofSetColor(255, 255, 100);
        ofDrawCircle(p->p, 4);
        ofPopStyle();
    }
}

void Mochi::drawGrids() {
    triGrids.debugDraw();
}

void Mochi::drawMesh() {
    triGrids.updateMesh();
    ofFill();
    ofSetColor(255);
    tex.getTexture().bind();
    triGrids.getMesh().draw();
    tex.getTexture().unbind();
}

glm::vec2 Mochi::getPosition() {
    glm::vec2 sum = glm::vec2(0);
    for (const auto & pt : lsmdPts) {
        sum += pt->p;
    }
    return sum/lsmdPts.size();
}

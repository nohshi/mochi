//
//  vectorField.cpp
//  brushSticker
//
//  Created by 藤田　恭輔 on 2019/10/08.
//

#include "vectorField.hpp"


void VectorField2d::init() {
    bUpdated = true;
    int cellNumX = int(range.x/resolution.x)+1;
    int cellNumY = int(range.y/resolution.y)+1;
    vectors.resize(cellNumX);
    for( int i=0; i<cellNumX; i++ ){
        vectors[i].resize(cellNumY);
    }
}

void VectorField2d::setupPerlin() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            float seedX = x * 0.3;
            float seedY = y * 0.3;
            vectors[x][y].x = noise.GetPerlin(seedX,seedY,10);
            vectors[x][y].y = noise.GetPerlin(seedX,seedY,80);
        }
    }
    bUpdated = true;
}


void VectorField2d::setupCubic() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            float seedX = x * 1.;
            float seedY = y * 1.;
            vectors[x][y].x = noise.GetCubic(seedX,seedY,10);
            vectors[x][y].y = noise.GetCubic(seedX,seedY,80);
        }
    }
    bUpdated = true;
}

void VectorField2d::setupTornado() {
    
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            glm::vec2 p = glm::vec2(x,y);
            p += offset;
            
            glm::vec2 f;
            f.x = p.x / float(width);
            f.x = f.x*2 - 1;
            f.y = p.y / float(height);
            f.y = f.y*2 - 1;
        
            glm::vec2 out;
            out = glm::normalize(f) * 0.05;
            
            vectors[x][y].x = -f.y;
            vectors[x][y].y = f.x;
            //vectors[x][y] += out;
            vectors[x][y] = glm::normalize(vectors[x][y]);
        }
    }
    bUpdated = true;
}

void VectorField2d::setupCustom1() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            glm::vec2 p = glm::vec2(x,y);
            p += offset;
            
            glm::vec2 f;
            f.x = p.x / float(width);
            f.x = f.x*2 - 1;
            f.y = p.y / float(height);
            f.y = f.y*2 - 1;
           
            glm::vec2 f2 = f;
            
            float n = 0.5;
            if (f2.x > 0){
                f2.x = pow(f2.x, n);
            }else{
                f2.x = -pow(-f2.x, n);
            }
            if (f2.y > 0){
                f2.y = pow(f2.y, n);
            }else{
                f2.y = -pow(-f2.y, n);
            }
            f2 = limit(f2, 0.3);
            f2 *= 0.5;
            
            float amp = 0.5;
            float seedX = p.x * amp;
            float seedY = p.y * amp;
            glm::vec2 nval;
            nval.x = noise.GetSimplex(seedX,seedY,10);
            nval.y = noise.GetSimplex(seedX,seedY,90);
            nval *= 0.3;
            
            vectors[x][y].x = -f.y + f2.x +nval.x;
            vectors[x][y].y = f.x + f2.y +nval.y;
            vectors[x][y] = glm::normalize(vectors[x][y]);
        }
    }
    bUpdated = true;
}

void VectorField2d::setupCustom2() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            glm::vec2 p = glm::vec2(x,y);
            p *= scale;
            p += offset;
            
            float amp = 0.2;
            float seedX = p.x * amp;
            float seedY = p.y * amp;
            
            vectors[x][y].x = noise.GetCubic(seedX, seedY,  10);
            vectors[x][y].y = noise.GetCubic(seedX, seedY, 300);
            vectors[x][y] = glm::normalize(vectors[x][y]);
        }
    }
    bUpdated = true;
}

void VectorField2d::setupCustom3() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            glm::vec2 p = glm::vec2(x,y);
            p *= scale;
            p += offset;
            
            float amp = 0.1;
            float seedX = p.x * amp;
            float seedY = p.y * amp;
            
            vectors[x][y].x = noise.GetSimplexFractal(seedX, seedY,  10);
            vectors[x][y].y = noise.GetSimplexFractal(seedX, seedY, 300);
            vectors[x][y] = glm::normalize(vectors[x][y]);
        }
    }
    bUpdated = true;
}

void VectorField2d::setupCustom4() {
    FastNoise noise;
    int width = vectors.size();
    for (int x=0; x < width; x++) {
        int height = vectors[x].size();
        for (int y=0; y < height; y++) {
            glm::vec2 v = glm::vec2(1, 0);
            
            vectors[x][y] = v;
            vectors[x][y].y += sin(float(x)/width * PI*4);
            
            vectors[x][y] = glm::normalize(vectors[x][y]);
        }
    }
    bUpdated = true;
}


const glm::vec2 & VectorField2d::lookup(const glm::vec2 &_pos) {
    glm::vec2 p = _pos + offset;
    int cellX = ofClamp(p.x/resolution.x, 0,range.x/resolution.x);
    int cellY = ofClamp(p.y/resolution.y, 0,range.y/resolution.y);
    
    return vectors[cellX][cellY];
}

void VectorField2d::display() {
    if (bUpdated) {
        viewer.allocate(range.x, range.y, OF_PIXELS_RGB);
        for (int y=0; y<viewer.getHeight(); y++) {
            for (int x=0; x<viewer.getWidth(); x++) {
                glm::vec2 val = lookup(glm::vec2(x,y));
                float r = (val.x+1)*0.500 * 255;
                float g = (val.y+1)*0.500 * 255;
                r = ofClamp(r, 0, 255);
                g = ofClamp(g, 0, 255);
                viewer.setColor(x, y, ofColor(r,g,0));
            }
        }
        bUpdated = false;
        displayBuffer.setFromPixels(viewer);
    }
    
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(offset);
    displayBuffer.draw(0,0,range.x,range.y);
    ofPopMatrix();
}

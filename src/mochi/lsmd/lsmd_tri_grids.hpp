//
//  lsmd_tri_grids.hpp
//  lsmd_test2_triGrid
//
//  Created by 藤田　恭輔 on 2019/12/03.
//

#ifndef lsmd_tri_grids_hpp
#define lsmd_tri_grids_hpp

#include "ofMain.h"
#include "lsmd.hpp"
#include "my_ofImage.hpp"

class LSMD_TriGrids {
public:
    
    struct Grid {
        //------------------頂点は反時計回りに入れる
        vector<shared_ptr<LSMD_Point>> pts;
        //------------------このグリッドが保持しているポイントのインデックス
        vector<int> indices;
        
        Grid(){
            pts.resize(3);
        }
        
        Grid(const vector<shared_ptr<LSMD_Point>> &_pts){
            pts.resize(3);
            for (int i=0; i<_pts.size(); i++) {
                pts[i] = _pts[i];
            }
        }
        
        Grid(const shared_ptr<LSMD_Point> &_pt0,
             const shared_ptr<LSMD_Point> &_pt1,
             const shared_ptr<LSMD_Point> &_pt2) {
            pts.resize(3);
            pts[0] = _pt0;
            pts[1] = _pt1;
            pts[2] = _pt2;
        }
    };
    
    //---------------------------メンバ変数
    vector<shared_ptr<LSMD_Point>> pts;
    vector<Grid> grids; //格子
    ofVboMesh mesh;
    float scale = 1;
    
    //---------------------------コンストラクタ
    LSMD_TriGrids() {
        
    }
    
    
    //---------------------------格子の数はsizeの二倍になる sizeってかresolutionだけど
    vector<shared_ptr<LSMD_Point>> init(const int &_size, My_ofImage _img, const float &_scale = 300) {
        
        vector<vector<shared_ptr<LSMD_Point>>> gridPts;
        
        //格子状に点を置く
        int num = 2*_size+1;
        
        gridPts.resize(num);
        float stepX = 1.f/num;
        for (int x = 0; x<num; x++) {
            for (int y = 0; y<num; y++) {
                glm::vec2 p;
                int px = x - _size;
                int py = y - _size;
                p.x = stepX * px + y%2*stepX/2;
                p.y = stepX * sqrt(3)/2 * py;
                auto pt = make_shared<LSMD_Point>(p);
                gridPts[x].emplace_back(pt);
            }
        }
        
        
        //点を使って格子を作る
        for (int y=0; y<num-1; y++) {
            for (int x=0; x<num-1; x++) {
                
                if (y%2==0) {
                    Grid grid0 = Grid(gridPts[x][y], gridPts[x][y+1], gridPts[x+1][y]);
                    Grid grid1 = Grid(gridPts[x+1][y], gridPts[x][y+1], gridPts[x+1][y+1]);
                    grids.emplace_back(grid0);
                    grids.emplace_back(grid1);
                }
                
                if (y%2==1) {
                    Grid grid0 = Grid(gridPts[x][y], gridPts[x][y+1], gridPts[x+1][y+1]);
                    Grid grid1 = Grid(gridPts[x][y], gridPts[x+1][y+1], gridPts[x+1][y]);
                    grids.emplace_back(grid0);
                    grids.emplace_back(grid1);
                }
                
            }
        }
        
        
        
        //画像のアルファがゼロじゃない格子の点をpts配列にぶち込むアンド不要なグリッドを消す
        vector<Grid>::iterator g = grids.begin();
        while (g != grids.end()) {
            ofColor col = _img.getColorAtPercent(g->pts[0]->p+glm::vec2(0.5));
            col.lerp( _img.getColorAtPercent( g->pts[1]->p+glm::vec2(0.5) ) , 0.5);
            col.lerp( _img.getColorAtPercent( g->pts[2]->p+glm::vec2(0.5) ) , 0.5);
            if (col.a < 1) {
                g = grids.erase(g);
            } else{
                for (auto &pt : g->pts) {
                    pts.emplace_back(pt);
                }
                ++g;
            }
        }
        
        cout << pts.size() << endl;
        
        //指すメモリがかぶるポインタをpts配列の中から削除する
        std::sort(pts.begin(), pts.end());
        auto itr = std::unique(pts.begin(), pts.end());
        pts.erase(itr, pts.end());
        cout << pts.size() << endl;
        
        //メッシュを作る
        this->initMesh();
        
        //重さを画像から決める
        //これ要る？？ 使ってもいいかもしれんけど
        /*
        My_ofImage mass_map;
        mass_map.load("mass_map.png");
        this->setMassFromImg(mass_map);
        */
        
        //スケール変更
        this->setScale(_scale);
        
        return pts;
    }
    
    
    void setScale(const float &_scale = 300) {
        //スケール変更
        float curScale = _scale/scale;
        for (auto & pt : pts) {
            pt->p *= curScale;
            pt->p0 *= curScale;
        }
        scale = _scale;
    }
    
    
    
    const ofVboMesh & getMesh() {
        return mesh;
    }
    
    //---------------------------これ呼ばないとメッシュが動かない
    void updateMesh() {
        mesh.clearVertices();
        for (const auto & pt : pts) {
            mesh.addVertex(glm::vec3(pt->p.x, pt->p.y, 0));
        }
    }
    
    
    //---------------------------グリッドを描く
    void debugDraw() {
        for (auto & grid : grids) {
            ofPushMatrix();
            ofSetColor(100, 255, 40);
            ofPolyline line;
            line.addVertex(grid.pts[0]->p.x, grid.pts[0]->p.y);
            line.addVertex(grid.pts[1]->p.x, grid.pts[1]->p.y);
            line.addVertex(grid.pts[2]->p.x, grid.pts[2]->p.y);
            line.close();
            line.draw();
            ofPopMatrix();
        }
    }
    
    
protected:
    void initMesh() {
        for (auto & pt : pts) {
            mesh.addVertex(glm::vec3(pt->p.x, pt->p.y, 0));
            mesh.addTexCoord(pt->p+glm::vec2(0.5));
        }
        
        for (int i=0; i<pts.size(); i++) {
            for (auto & grid : grids) {
                for (auto & gpt : grid.pts) {
                    if (pts[i].get() == gpt.get()) {
                        grid.indices.push_back(i);
                    }
                }
            }
        }
        
        for (const auto & grid : grids) {
            mesh.addTriangle(grid.indices[0], grid.indices[1], grid.indices[2]);
        }
    }
    
    //---------------------------画像からptsの質量massを設定する
    void setMassFromImg(My_ofImage _img) {
        for (auto & pt : pts) {
            ofColor col = _img.getColorAtPercent(pt->p+glm::vec2(0.5));
            pt->m = (1.-col.r/255.f);
        }
    }
    
    
};

#endif /* lsmd_tri_grids_hpp */

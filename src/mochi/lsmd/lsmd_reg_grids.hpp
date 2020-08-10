//
//  lsmd_reg_grids.hpp
//  mochi2_regGrid
//
//  Created by 藤田　恭輔 on 2020/03/27.
//

#ifndef lsmd_reg_grids_hpp
#define lsmd_reg_grids_hpp

#include <stdio.h>

#include "ofMain.h"
#include "lsmd.hpp"
#include "my_ofImage.hpp"

class LSMD_RegGrids {
public:
    
    struct Grid {
        //------------------頂点は反時計回りに入れる
        vector<shared_ptr<LSMD_Point>> pts;
        //------------------このグリッドが保持しているポイントのインデックス
        vector<int> indices;
        
        Grid(){
            pts.resize(4);
        }
        
        Grid(const vector<shared_ptr<LSMD_Point>> &_pts){
            pts.resize(4);
            for (int i=0; i<_pts.size(); i++) {
                pts[i] = _pts[i];
            }
        }
        
        Grid(const shared_ptr<LSMD_Point> &_pt0,
             const shared_ptr<LSMD_Point> &_pt1,
             const shared_ptr<LSMD_Point> &_pt2,
             const shared_ptr<LSMD_Point> &_pt3) {
            pts.resize(4);
            pts[0] = _pt0;
            pts[1] = _pt1;
            pts[2] = _pt2;
            pts[3] = _pt3;
        }
    };
    
    //---------------------------メンバ変数
    vector<shared_ptr<LSMD_Point>> pts;
    vector<Grid> grids; //格子
    ofVboMesh mesh;
    float scale = 1;
    
    
    //---------------------------コンストラクタ
    LSMD_RegGrids() {
        
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
                p.x = stepX * px;
                p.y = stepX * py;
                auto pt = make_shared<LSMD_Point>(p);
                gridPts[x].emplace_back(pt);
            }
        }
        
        
        //点を使って格子を作る
        for (int y=0; y<num-1; y++) {
            for (int x=0; x<num-1; x++) {
                Grid grid = Grid(gridPts[x][y], gridPts[x][y+1], gridPts[x+1][y], gridPts[x+1][y+1]);
                grids.emplace_back(grid);
            }
        }
        
        
        
        //画像のアルファがゼロじゃない格子の点をpts配列にぶち込むアンド不要なグリッドを消す
        vector<Grid>::iterator g = grids.begin();
        while (g != grids.end()) {
            ofColor col = _img.getColorAtPercent(g->pts[0]->p+glm::vec2(0.5));
            col.lerp( _img.getColorAtPercent( g->pts[1]->p+glm::vec2(0.5) ) , 0.5);
            col.lerp( _img.getColorAtPercent( g->pts[2]->p+glm::vec2(0.5) ) , 0.5);
            col.lerp( _img.getColorAtPercent( g->pts[3]->p+glm::vec2(0.5) ) , 0.5);
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
    
    
    
    //---------------------------グリッドを描く
    void debugDraw() {
        for (auto & grid : grids) {
            ofPushMatrix();
            ofSetColor(100, 255, 40);
            ofPolyline line;
            /*
            line.addVertex(grid.pts[0]->p.x, grid.pts[0]->p.y);
            line.addVertex(grid.pts[1]->p.x, grid.pts[1]->p.y);
            line.addVertex(grid.pts[2]->p.x, grid.pts[2]->p.y);
             */
            line.close();
            line.draw();
            ofPopMatrix();
        }
    }
    
    
protected:
    
    //---------------------------画像からptsの質量massを設定する
    void setMassFromImg(My_ofImage _img) {
        for (auto & pt : pts) {
            ofColor col = _img.getColorAtPercent(pt->p+glm::vec2(0.5));
            pt->m = (1.-col.r/255.f);
        }
    }
    
    
};



#endif /* lsmd_reg_grids_hpp */

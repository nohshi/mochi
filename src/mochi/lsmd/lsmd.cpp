//
//  lsmd.cpp
//  lsmd_test
//
//  Created by 藤田　恭輔 on 2019/11/28.
//

#include "lsmd.hpp"

void LSMD::calculate() {
    
    int ptNum = tgts.size();
    
    //----------------goal positionのゼロ初期化
    for (auto & gi : g) {
        gi = glm::vec2(0);
    }
    
    
    //----------------goal positionの計算
    for (int r=0; r<clusters.size(); r++) {
        
        int ptNumInClstr = clusters[r].size();
        
        //-----------重心c0, cを計算する
        float M = 0;
        glm::vec2 c0 = glm::vec2(0);
        glm::vec2 c = glm::vec2(0);
        for (const auto & pt : clusters[r]) {
            float m2 = pt->m / ptNumInClstr;
            M += m2;
            c0 += m2 * pt->p0;
            c += m2 * pt->p;
        }
        c0 /= M;
        c /= M;
        
        //-----------Moment Matrix(A)の計算
        glm::mat2 A = glm::mat2(0);
        for (const auto & pt : clusters[r]){
            float m2 = pt->m / ptNumInClstr;
            glm::vec2 p = pt->p - c;
            glm::vec2 q = pt->p0 - c0;
            A += m2 * glm::outerProduct(p, q);
        }
        
        //-----------Aを対角化するP,Dを計算
        glm::mat2 P, D;
        std::tie(D, P) = this->jacobi22(glm::transpose(A) * A);
        //-----------Sを計算
        glm::mat2 S = P * glm::mat2(sqrt(D[0][0]), 0,
                                    0, sqrt(D[1][1])) * glm::transpose(P);
        //-----------回転行列Rを求めて頂点群に掛ける
        glm::mat2 R = A * glm::inverse(S);
        
        //-----------goal position(g)の計算
        //あこれ正解っぽい
        for (const auto & pt : clusters[r]) {
            int id = pt->getId();
            g[id] += (1.f/clusters[id].size()) * (R * (pt->p0-c0) + c);
        }
        //これの方がなぜかうまくいく
        //g[r] += (1.f) * (R * (tgts[r]->p0-c0) + c);
    }
    
    //---------------頂点位置・速度の計算
    if(ofGetFrameNum() > 60) h = ofGetLastFrameTime(); //deltaTime
    //-----------頂点位置と速度の計算
    for (int i=0; i < ptNum; i++){
        tgts[i]->v = tgts[i]->v + a/h * (g[i] - tgts[i]->p) + h/tgts[i]->m * tgts[i]->f;
        tgts[i]->p = tgts[i]->p + h * tgts[i]->v;
        tgts[i]->v = d * tgts[i]->v;
        
        tgts[i]->f = glm::vec2(0); //力の初期化
    }
    
}






//M' = diag(λ1,λ2,λ3) = P'T * M * P と対角化する
//入力： 2*2対称行列M, 前フレームの直交行列P0（なくても良い）
//出力： 対角化されたM, 直交行列P

std::tuple<glm::mat2, glm::mat2> LSMD::jacobi22(glm::mat2 M) {
    glm::mat2 P;
    if (isUseP0) {
        P = P0;
        M = glm::transpose(P) * M * P; //かける順序逆か？
    }else{
        P = glm::mat2(); //単位行列を代入
    }
    
    int maxNum = 1; //2*2行列だと一回でいい
    for (int i=0; i<maxNum; i++) {
        //-----絶対値の大きな非対角成分（というか一つだけ）
        float mij = M[0][1];
        float thresh = 0.001; //収束判定の閾値
        if (abs(mij) < thresh) {
            return std::forward_as_tuple(M, P);
        }
        float theta = 0.500 * atan(-2*M[0][1]/(M[0][0]-M[1][1]));
        //直交行列R
        glm::mat2 R = glm::mat2(cos(theta), sin(theta),
                                -sin(theta), cos(theta));
        M = glm::transpose(R) * M * R;
        P = P * R;
    }
    P0 = P; //次のフレームで使うためのPを保存
    isUseP0 = true;
    return std::forward_as_tuple(M, P);
}




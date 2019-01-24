#pragma once
#include"sprite.h"
#include"texture.h"
#include"block.h"
#include"release.h"
using namespace DirectX;
using namespace SimpleMath;



class Score
{
private:
    ID3D11ShaderResourceView* texture_;
    Vector2 position1;//RECT計算のための座標
    Vector2 position2;
    Vector2 position3;
    Vector2 position4;
    Vector2 position5;
    Vector2 position6;
    int score;//スコア
public:
    Score();
    bool init();//初期化
    void update();//更新（いるかわからない）
    void calculate();//描画座標の計算
    void draw();//描画
    void destroy();//破棄
};
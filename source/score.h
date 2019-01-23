#pragma once
#include"sprite.h"
#include"texture.h"
#include"pad.h"
#include"block.h"

using namespace DirectX;
using namespace SimpleMath;



class Score
{
private:

public:
    bool init();//初期化
    void update();//更新（いるかわからない）
    void calculate();//描画座標の計算
    void draw();//描画
    void destroy();//破棄
};
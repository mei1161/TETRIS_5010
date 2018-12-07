#pragma once
#include <cstdio>
#include "direct3d.h"
#include "sprite.h"
#include "texture.h"
#include"font.h"
#include "keyboard.h"
#include "pad.h"
#include "error.h"
#include "release.h"


class Field
{
private:
    ID3D11ShaderResourceView* texture_;//テクスチャ
    int width_;//横幅
    int height_;//縦幅
    int field[ 22 ][ 12 ];//フィールド配列
public:
    Field();//コンストラクタ
    bool init();    //初期化
    void draw();    //描画
    void destroy(); //破棄
};
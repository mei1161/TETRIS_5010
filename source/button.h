#pragma once
#include"keyboard.h"
#include <cstdio>
#include "direct3d.h"
#include "sprite.h"
#include "texture.h"
#include"font.h"
#include "keyboard.h"
#include "pad.h"
#include "error.h"
#include "release.h"
#include"pad.h"
class Button
{
private:
    ID3D11ShaderResourceView* texture_;//テクスチャ
    int pattern;//十字キーパターン
    int Bpattern;//ボタンパターン
    Vector2 position;
    int sizetop;
    int sizeleft;//画像左
    bool abutton;//Aボタン
    Vector2 Aposition;//Aボタン座標
    int Asize;//Aボタンサイズ
    bool bbutton;//Bボタン
    Vector2 Bposition;//Bボタン座標
    int Bsize;
    bool lbbutton;//LBボタン
    int LBsize;
    Vector2 LBposition;
    bool pausebutton;//ポーズボタン
    int pausesize;
    Vector2 Pposition;
public:
    Button();//コンストラクタ
    bool init();//初期化
    void update();//更新
    void draw();//描画
    void range();//描画範囲
    void destroy();//破棄


};
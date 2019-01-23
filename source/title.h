#pragma once
#include <d3d11.h>
#include "release.h"
#include"texture.h"
#include"position.cpp"
#include "pad.h"
#include"keyboard.h"

////////////////////////////////////
// class
////////////////////////////////////
class Title
{
private:
	ID3D11ShaderResourceView* texture_;     // テクスチャ
    int count;
    Vector2 position8;
    Keyboard::KeyboardStateTracker tracker;
    GamePad::ButtonStateTracker Btracker;
public:
	Title() :texture_(NULL) {}              // コンストラクタ
	bool init();                            // 初期化
	bool update();                          // 更新
	void draw();                            // 描画
    void move();                            //移動
	void destroy();                         // 破棄
};
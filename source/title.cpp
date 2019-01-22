/*#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "pad.h"
#include"keyboard.h"

////////////////////////////////////
// 初期化
////////////////////////////////////
bool Title::init()
{
	// テクスチャの読み込み
	if (!(texture_ = Texture::load(L"Texture/Tetris10_Title.png")))
	{
		// エラー
		return false;
	}



	return true;
}


////////////////////////////////////
// !!更新
////////////////////////////////////
bool Title::update()
{
	// コントローラの入力情報を取得
	GamePad::State pad = Pad::getState();
	Keyboard::State
	

	return true;
}

////////////////////////////////////
// 描画
////////////////////////////////////
void Title::draw()
{
	Sprite::draw(texture_, Vector2::Zero);
}


////////////////////////////////////
// 破棄
////////////////////////////////////
void Title::destroy()
{
	// テクスチャの解放
	SAFE_RELEASE(texture_);
}*/
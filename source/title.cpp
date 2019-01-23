#include "title.h"
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

    count = 0;

	return true;
}


////////////////////////////////////
// !!更新
////////////////////////////////////
bool Title::update()
{
	// コントローラの入力情報を取得
	GamePad::State pad = Pad::getState();
    Keyboard::State key = Key::getKeyState();
    tracker.Update( key );
    Btracker.Update( pad );
    if( key.A || pad.buttons.a )
    {
        return false;
    }
    if(tracker.pressed.Down||Btracker.dpadDown==GamePad::ButtonStateTracker::PRESSED)
    {
        count++;
    }
    if( tracker.pressed.Up|| Btracker.dpadUp == GamePad::ButtonStateTracker::PRESSED )
    {
        count--;
    }

	return true;
}

////////////////////////////////////
// 描画
////////////////////////////////////
void Title::draw()
{
	Sprite::draw(texture_, Vector2::Zero);

    RECT rect;
    rect.top = 947L;
    rect.left =1201L;
    rect.bottom = rect.top + 35L;
    rect.right = rect.left + 264L;
   
    move();

    Sprite::draw( texture_, position8, &rect );

}
//移動座標
void Title::move()
{
    position8.x = 504L;
   
    //リスト
    switch( count % 6 )
    {
    case 0: position8.y = 322L; break;
    case 1:position8.y = 364L; break;
    case 2:position8.y = 406L; break;
    case 3:position8.y = 448L; break;
    case 4:position8.y = 490L; break;
    case 5:position8.y = 532L; break;
    }
}

////////////////////////////////////
// 破棄
////////////////////////////////////
void Title::destroy()
{
	// テクスチャの解放
	SAFE_RELEASE(texture_);
}
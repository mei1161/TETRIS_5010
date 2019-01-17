#include"button.h"
#include"release.h"



//定数
const int Arrowsize = 227;//矢印キー1つのサイズ
const int Buttonsize = 128;//A,B,LBボタンのサイズ


//列挙体
enum
{
    None,
    Up,
    RightUp,
    Right,
    RightDown,
    Down,
    LeftDown,
    Left,
    LeftUp
};

//コンストラクタ
Button::Button()
{
    position.x = 47;
    position.y = 424;
    sizeleft = 0;
    Aposition.x = 1003;
    Aposition.y = 520;
    Asize = 0;
    Bposition.x = 1100;
    Bposition.y = 321;
    Bsize = 0;
    LBposition.x = 39;
    LBposition.y = 231;
    Pposition.x = 1062;
    Pposition.y = 82;
    pausesize = 0;
}


//初期化
bool Button::init()
{
    //テクスチャ読み込み
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // エラー
        Error::showDialog( "Tetris11_SingleT.pngが開けませんでした" );
        return false;
    }
    return true;

}

//更新
void Button::update()
{
    Keyboard::State key = Key::getKeyState();//格納先
    GamePad::State pad = Pad::getState();

    //十字キー
    if( (key.Up&&key.Left) || (pad.dpad.up&&pad.dpad.left) )
    {
        pattern = LeftUp;

    }
    else if( (key.Up&&key.Right) || (pad.dpad.up&&pad.dpad.right) )
    {
        pattern = RightUp;
    }
    else if( (key.Down&&key.Right) || (pad.dpad.down&&pad.dpad.right) )
    {
        pattern = RightDown;
    }
    else if( (key.Down&&key.Left) || (pad.dpad.down&&pad.dpad.left) )
    {
        pattern = LeftDown;
    }
    else if( key.Right || pad.dpad.right )
    {
        pattern = Right;
    }
    else if( key.Left || pad.dpad.left )
    {
        pattern = Left;
    }
    else if( key.Down || pad.dpad.down )
    {
        pattern = Down;
    }
    else if( key.Up || pad.dpad.up )
    {
        pattern = Up;
    }
    else
        pattern = None;


    //Aボタン
    if( pad.buttons.a || key.A )
    {
        abutton = true;
    }
    else
        abutton = false;
    //Bボタン
    if( pad.buttons.b || key.Z )
    {
        bbutton = true;
    }
    else
        bbutton = false;
    //LBボタン
    if( pad.buttons.leftShoulder || key.Enter )
    {
        lbbutton = true;
    }
    else lbbutton = false;
    //PAUSEボタン
    if( pad.buttons.menu || key.Space )
    {
        pausebutton = true;
    }
    else pausebutton = false;


}
//描画範囲設定
void Button::range()
{
    //矢印キー
    switch( pattern )
    {
    case None:sizeleft = Arrowsize * None; break;
    case Up:sizeleft = Arrowsize * Up; break;
    case RightUp:sizeleft = Arrowsize * RightUp; break;
    case RightDown:sizeleft = Arrowsize * RightDown; break;
    case Right:sizeleft = Arrowsize * Right; break;
    case Left:sizeleft = Arrowsize * Left; break;
    case LeftUp:sizeleft = Arrowsize * LeftUp; break;
    case LeftDown:sizeleft = Arrowsize * LeftDown; break;
    case Down:sizeleft = Arrowsize * Down; break;

    }

    //Aボタン
    if( !abutton )
    {
        Asize = 0;
    }
    else Asize = Buttonsize;
    //Bボタン
    if( !bbutton )
    {
        Bsize = 0;
    }
    else Bsize = Buttonsize;
    //LBボタン
    if( !lbbutton )
    {
        LBsize = 0;
    }
    else LBsize = Buttonsize;
    //ポーズボタン
    if( !pausebutton )
    {
        pausesize = 0;
    }
    else pausesize = 64;
}

//描画
void Button::draw()
{

    //十字キー描画
    range();
    RECT rect;
    rect.top = 720;
    rect.left = sizeleft;
    rect.right = sizeleft + Arrowsize;
    rect.bottom = rect.top + Arrowsize;

    Sprite::draw( texture_, position, &rect );

    //Aボタン描画
    RECT Arect;
    Arect.top = 464 + Asize;
    Arect.left = 1536;
    Arect.right = Arect.left + Buttonsize;
    Arect.bottom = Arect.top + Buttonsize;

    Sprite::draw( texture_, Aposition, &Arect );

    RECT Brect;
    Brect.top = 464 + Bsize;
    Brect.left = 1664;
    Brect.right = Brect.left + Buttonsize;
    Brect.bottom = Brect.top + Buttonsize;
    Sprite::draw( texture_, Bposition, &Brect );


    RECT LBrect;
    LBrect.top = 464 + LBsize;
    LBrect.left = 1280;
    LBrect.right = LBrect.left + Buttonsize;
    LBrect.bottom = LBrect.top + Buttonsize;
    Sprite::draw( texture_, LBposition, &LBrect );
    RECT Prect;
    Prect.top = 336 + pausesize;
    Prect.left = 1920;
    Prect.right = Prect.left + 128;
    Prect.bottom = Prect.top + 64;
    Sprite::draw( texture_, Pposition, &Prect );
}




//破棄
void Button::destroy()
{
    SAFE_RELEASE( texture_ );
}
#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down,
    None
};
//定数




//コンストラクタ
Block::Block()
{
    texture_ = NULL;
    position_.y = 173L;//ブロック座標
    position_.x = 635L;
    plus =25.0F;
    Animation_counter = 0;
    move_ = false;
    count = 0;
}

//初期化
bool Block::init()
{
    // テクスチャの読み込み
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // エラー
        return false;
    }
    return true;




}


//更新
void Block::update()
{
    Keyboard::State key = Key::getKeyState();
    
    
    if( position_.y <= 670&&position_.x<=721&&position_.x>=512) {
        if( key.Left )
        {
            key_state = Left;
        }
        else if( key.Right )
        {
            key_state = Right;
        }
        else if( key.Up )
        {
            key_state = Up;
        }
        else if( key.Down )
        {
            key_state = Down;
        }
        else
            key_state = None;

        Animation();
       
    }
           
    }




 
 


//描画
void Block::draw()
{
    RECT rect;//ブロックの描画
    rect.top = 956L;
    rect.left = 688L;
    rect.right = rect.left + 25L;
    rect.bottom = rect.top + 25L;
   
        Sprite::draw( texture_, position_, &rect );
    
    
}

//破棄
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}

//アニメーション処理
void Block::Animation()
{
    //アニメーション処理
    if( ++count >= 25 ) {
        switch( key_state ) {
        case Left: position_.x -= plus; break;
        case Right: position_.x += plus; break;
        case Down: position_.y += plus; break;
        case Up:position_.y -= plus; break;
        case None:position_.y += plus; break;
        }
        count = 0;

    }
}
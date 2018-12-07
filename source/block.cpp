#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down
};




//コンストラクタ
Block::Block()
{
    texture_ = NULL;
    position_.y = 173L;
    position_.x = 635L;
    plus =2.5F;

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
    if( position_.y <= 670 ) {
        if( key.Left )
        {
            position_.x -= plus;
        }
        else if( key.Right )
        {
            position_.x += plus;
        }
        else if( key.Up )
        {
            position_.y -= plus;
        }
        else if( key.Down )
        {
            position_.y += plus;
        }
        else
        {
            position_.y += plus;
        }
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
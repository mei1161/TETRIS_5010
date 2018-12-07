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
    int count = 0;
    Keyboard::State key = Key::getKeyState();
  

   
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
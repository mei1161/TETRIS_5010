#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down,
    None,
};
//定数


const int WALL = 99;//当たり判定のあるブロック

//コンストラクタ
Block::Block()
{
    texture_ = NULL;
    position_.y =173L;//ブロック座標
    position_.x =511L;
    plus =25.0F;
    Animation_counter = 0;
    move_ = false;
    count = 0;
    flag = false;
    r_flag = false;
    cdelete = 0;
    
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
    int i;//ループカウンタ
    int j;
    for( i = 0; i < 22; i++ )
        for( j = 0; j < 12; j++ )
        {
            block[ i ][ j ] =0;

            if( i == 21 )
            {
                block[ i ][ j ] = WALL;
          }
            if( j == 0 || j == 11 )
            {
                block[ i ][ j ] =WALL;
            }


            
        }
    
    
    return true;
    
}


//更新
void Block::update()
{
    Keyboard::State key = Key::getKeyState();
    GamePad::State pad = Pad::getState();

  

    if( position_.y <= 695 ) {

        if( key.Left || pad.dpad.left )//左移動
        {
            key_state = Left;
            Animation();
        }
        else if( key.Right || pad.dpad.right )//右移動
        {
            key_state = Right;
            Animation();
        }
        else if( key.Up || pad.dpad.up )//自動で下に落ちる
        {
            key_state = Up;
            Animation();
        }
        else if( key.Down || pad.dpad.down )//下移動
        {
            key_state = Down;
            Animation();
        }
        else
            key_state = None;
        Animation();
    }
    Collusion();//当たり判定
    Storing();

}

//当たり判定
void Block::Collusion()
{
    //当たり判定
    if( position_.x <= 486 )//右脇
    {
        position_.x += plus;
    }
    if( position_.x >= 756 )//左脇
    {
        position_.x -= plus;
    }
    if( position_.y >= 670 )//下
    {
        position_.y = 672;
		flag = true;
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
 RECT Arect;//ブロックの描画
 Arect.top = 957L;
 Arect.left = 713L;
 Arect.right = Arect.left + 25L;
 Arect.bottom = Arect.top + 25L;

 int i, j;
 for( i = 0; i < 22; i++ ) {
     for( j = 0; j < 12; j++ )
     {
         if( block[ i ][ j ] == WALL )
         {
             Aposition_.x = (j* 25) + 487;
             Aposition_.y = (i * 25) + 173;
             Sprite::draw( texture_, Aposition_, &Arect );
         }
         if( block[ i ][ j ] == 1 )
         {
             position2.x= (j* 25) + 487;
             position2.y = (i* 25) + 173;
             Sprite::draw( texture_, position2, &rect );
         }

     }
 }
 

}

//破棄
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}

void Block::Animation()
{
    //アニメーション処理
    if( ++count >= 25 ) {
        switch( key_state ) {
        case Left: position_.x -= plus; break;
        case Right: position_.x += plus; break;
        case Down: position_.y += plus; break;
        case Up:position_.y = 672; break;
        case None:position_.y += plus; break;

        }
        count = 0;
    }
}
//配列に格納
void Block::Storing()
{
    int i, j;

    if( flag == true )
    {
        i= (position_.y-148) / 25;
        j= (position_.x-486) / 25;
        block[ i ][ j ] = 1;//中身の値を増やす  
        Load();
        position_.y = 173L;//ブロック座標
        position_.x = 511L;
      

    }

     flag = false;
}

//削除処理
void Block::Delete()
{




}
void Block::Load()
{
  
    int k;
    i = (position_.y - 148) / 25;
    for( k = 0; k < 12; k++ ) {
        if( block[ i ][ k + 1 ] == 1 )
        {
            cdelete++;
        }
    }
    if( cdelete == 10 )
    {
        for( k = 1; k < 11; k++ )
        {
            if( block[ i ][ k ] == 1 )
            {
                block[ i ][ k ] = 0;
               
            }
        }
        cdelete = 0;
    }


}


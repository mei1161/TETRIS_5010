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
    Aflag = true;
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
            Check();
            Animation();
        }
        else if( key.Right || pad.dpad.right )//右移動
        {
            key_state = Right;
            Check();
            Animation();
        }
        else if( key.Up || pad.dpad.up )//自動で下に落ちる
        {
            key_state = Up;
            Check();
            Animation();
        }
        else if( key.Down || pad.dpad.down )//下移動
        {
            key_state = Down;
            Check();
            Animation();
        }
        else
            key_state = None;
            Check();
        Animation();
    }
    Collusion();//当たり判定
    Storing();

}
//確認する用の関数
void Block::Check()
{
    int i2, j2;//一つ先の配列番号を格納する用の変数
    i = (position_.y - 148) / 25;//座標から、一致する入れる番号を求める
    j = (position_.x - 486) / 25;
    switch( key_state )
    {
    case Down:i2 = i + 1; j2 = j; break;
    case None:i2 = i+1; j2 = j; break;
    case Left:i2 = i; j2 = j - 1; break;
    case Right:i2 = i; j2 = j + 1; break;
    }
    if(block[i2][j2]==99 )//壁だった場合
    {
        if( key_state == Left )//一つ右側の座標にする
        {
            j2 = j++;
        }
        if( key_state == Right )//一つ左側の座標にする
        {
            j2 = j--;
        }
    }
    if( block[ i2 ][ j2 ] == 1 )//一つ先の配列が、ブロックだった場合
    {
        flag = true;//配列に格納
        Aflag = false;//アニメションを行わない
    }
    else
        Aflag = true;
    


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
         if( block[ i ][ j ] == WALL )//当たり判定の壁の表示
         {
             Aposition_.x = (j* 25) + 487;
             Aposition_.y = (i * 25) + 173;
             Sprite::draw( texture_, Aposition_, &Arect );
         }
         if( block[ i ][ j ] == 1 )//ブロックの表示
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
    if( Aflag == true )
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
}
//配列に格納
void Block::Storing()
{
    int i, j;
    int count;//iのカウント用変数
    if( flag == true )
    {
        i= (position_.y-148) / 25;//座標から、一致する入れる番号を求める
        j= (position_.x-486) / 25;
        block[ i ][ j ] = 1;//ブロックの中身を入れる
        
        count = i;
        for( j = 1; j < 11; j++ )//ブロックが入った配列の要素を左から確認
        {
          
            if( block[count][ j ] == 1 )//ブロックの中身が１ならdeletecountインクリメント
            {
                cdelete++;
            }
            else//ブロックが入っていない場合は、deletecountの初期化を行い、ループから抜ける
                cdelete = 0;
                
        }

       


		Delete(count);//消す処理
        position_.y = 173L;//ブロック座標
        position_.x = 511L;
      

    }

     flag = false;
}

//削除処理
void Block::Delete(int count)
{

    
    int k;
	if (cdelete>=10)//カウントが10以上なら
	{
		cdelete = 0;//カウントの初期化
		for (k = 1; k < 11; k++)
		{
			if (block[count][k] == 1)//ブロックの中身の初期化
			{
				block[count][k] = 0;
			}
		}
        Drop(count);
	}

}
//消された場合、積んであるブロックを下に落とす処理
void Block::Drop(int count)
{
    for( i = 1; i < 21; i++ )
        for( j = 1; j < 11; j++ )
        {
            if( block[ i ][ j ] == 1 )
            {
                block[ i + 1 ][ j ] = block[ i ][ j ];
                block[ i ][ j ] = block[ i - 1 ][ j ];
            }
    }
}

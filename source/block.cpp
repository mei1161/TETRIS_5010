#include"block.h"
#include"color.h"
#include"color.cpp"
#include"mino.h"
enum keyboard
{
    Left,
    Right,
    Up,
    Down,
    None,
};


//コンストラクタ
Block::Block()
{
    texture_ = NULL;
	count = 0;//カウント
	exist_fallingblock = false;//ブロック生成
  
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
	int i, j, k;
	for(i=0;i<4;i++)
		for (j = 0; j < 4; j++)//落ちているブロックの初期化
		{
			falling_block[i][j].index[0] =-1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].color = -1000;
			falling_block[i][j].is_wall = false;
		}

	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++)
		{
			field[i][j].color =-1;  //色情報初期化
			for (k = 0; k < 2; k++) //座標初期化
			{
				field[i][j].index[k] = 99;
			}
			if (i == 21 || j == 0 || j == 11)//壁
			{
				field[i][j].is_wall = true;
				field[i][j].index[0] = j;//左右当たり判定番号
				field[i][j].index[1] = i;//下当たり判定配列番号
				field[i][j].color =Black;
			}
			else//壁以外
			{
				field[i][j].is_wall = false;//壁の当たり判定なし
			}

		}
	}

    return true;
    
}
//ブロック生成
void Block::Make_fallingblock()
{
    int i, j;
    int k = 1;
    int l = 0;
    for( i = 0; i < 4; i++ )
    {
    for( j = 0; j < 4; j++ )
    {
        if( mino_1[ i ][ j ] == 1 )
        {

            falling_block[ i ][ j ].index[ 0 ] = k;
            falling_block[ i ][ j ].index[ 1 ] = l;
            k++;
            if( j == 3 )
            {
                l++;
            }
    if(j==1)
    {
        k = 1;
    }
   
        }
            falling_block[ i ][ j ].color = Green;
        }


    }

}
//更新処理
void Block::update()
{
	
	Keyboard::State key = Key::getKeyState();
	GamePad::State pad = Pad::getState();
    int i, j;
	if (exist_fallingblock == false) {
		/*falling_block[0][0].index[0] =1; //faling_blockのX座標
		falling_block[0][0].index[1] =-1;//falling_block のY座標
		falling_block[0][0].color = Green;*/
        Make_fallingblock();
		exist_fallingblock = true;
	}

	count++;
	//自動落下

	if (key.Down||pad.dpad.down) 
	{
		if (count % 3== 0)
		{
			move_down();
		}
	}
	else 	if (count % 60 == 0)
	{
		move_down();
	}	

	if (key.Left||pad.dpad.left)
	{
		if (count % 6 == 0) {
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
                    
                    if( can_move( Left ) == true )
                    {
                        falling_block[ i ][ j ].index[ 0 ]--;//左
                    }
				}
		}
	}
	 if (key.Right||pad.dpad.right)
	{
		if (count % 6 == 0) {
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
                    if( can_move( Right ) == true )
                    {
                        falling_block[ i ][ j ].index[ 0 ]++;//右
                    }
				}
		}
	}
}
void Block::move_down()
{
	int i, j;
			if (can_move(Down)== true)//動けるなら
			{
				for(i=0;i<4;i++)
					for (j = 0; j < 4; j++)
					{
						falling_block[i][j].index[1]++;//配列番号(y座標)降下

					}
				if (can_move(Down) == false)
				{
					Copy_fallingblock_in_field();
				}
			}
			
}

//描画
void Block::draw()
{

	int i, j;
	//壁描画//固まったブロックの描画
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			Vector2 texture_UV = get_textureUV_from(field[i][j].color);
			RECT rect;
			rect.top = texture_UV.x;
			rect.left = texture_UV.y;
			rect.right = rect.left + 25L;
			rect.bottom = rect.top + 25L;

			position_.x = (field[i][j].index[0] * 25) + 487;
			position_.y = (field[i][j].index[1] * 25) + 173;

			Sprite::draw(texture_, position_, &rect);
		}
	}
	//動いてるブロック描画
	RECT Arect;
	for (i = 0; i < 4; i++)
        for( j = 0; j < 4; j++ )
        {
            Vector2 texture_UV = get_textureUV_from( falling_block[ i ][ j ].color );
            Arect.top = texture_UV.x;
            Arect.left = texture_UV.y;
            Arect.right = Arect.left + 25L;
            Arect.bottom = Arect.top + 25L;

            position2.x = (falling_block[ i ][ j ].index[ 0 ] * 25) + 487;
            position2.y = (falling_block[ i ][ j ].index[ 1 ] * 25) + 173;
            if( position2.y >= 173 ) //座標内に入ったら、描画
            {
            Sprite::draw( texture_, position2, &Arect );
             }
		}

		
}


//動けるかどうか
bool Block::can_move(int direction)
{
    int i, j;//ループ変数
    int checkx,checky;//代入用関数
    switch( direction )//方向キーの種類によって、分岐
    {
    case Left:
        for( i = 0; i < 4; i++ ) 
            for( j = 0; j < 4; j++ )
            {
                if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 1 ] >= -1 )
                {
                    checkx = falling_block[ i ][ j ].index[ 0 ];
                    checky = falling_block[ i ][ j ].index[ 1 ];
                }

                if( field[ checky ][ checkx - 1 ].is_wall == true )
                {
                    return false;
                }
                else return true;
            }
                break;
    case Down:
        for( i = 0; i < 4; i++ ) 
            for( j = 0; j < 4; j++ )
            {//落ちているブロックの中身が入っている場合、配列番号を代入
                if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 0 ] >= -1 )
                {
                    checkx = falling_block[ i ][ j ].index[ 0 ];
                    checky = falling_block[ i ][ j ].index[ 1 ];
                }

                if( field[ checky + 1 ][ checkx ].index[1]==21||field[checky + 1 ][checkx].index[1]!=99)//1つ下の配列
                {    
                    return false;
                    
                }
                else
                { 
                    return true;
                }
            }
        break;
    case Right:
		for( i = 0; i < 4; i++ )
        for( j = 0; j < 4; j++ )
        {
			//落ちているブロックの中身が入っている場合、配列番号を代入
            if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 1 ] >= -1 )
            {
                checkx = falling_block[ i ][ j ].index[ 0 ];
                checky = falling_block[ i ][ j ].index[ 1 ];
            }

            if( field[ checky][ checkx+1 ].is_wall == true )//一つ下の配列に壁があるかどうか
            {
              
                return false;
            }
            else
            {
                return true;
            }
        }
                       break;
        }
    
    }
//落ちているブロックをフィールドの中に移す
void Block::Copy_fallingblock_in_field()
{
    int i, j;
        for(i=0;i<4;i++)
            for( j = 0; j < 4; j++ )
            {
                if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 1 ] >= -1 ) //初期値が入っていた場合は行わない
                {
                    field[ falling_block[ i ][ j ].index[ 1]][ falling_block[ i ][ j ].index[0] ] = falling_block[ i ][ j ];//faling_blockの中身を代入する
					Delete_fieldblock(falling_block[i][j].index[1]);//消す処理
                }
        exist_fallingblock = false;//新しいブロック生成
    }
}

//そろったブロックを消す処理
void Block::Delete_fieldblock(int num)
{
	
    int  j;
    int delete_count=0;//カウンタ
    for( j = 1; j < 11; j++ )
    {
        if( field[ num ][ j ].index[ 0 ] != 99 )//indexの中身が初期値以外の値の場合
        {
            delete_count++;
        }
        else//初期値が１つでも入っていたら初期化
        {
            delete_count = 0;
        }

        if(delete_count>=10 )//行の中身がすべてブロックの場合
        {
            for( j = 1; j < 11; j++ )//そろった行の中身の初期化
            {
                if( field[ num ][ j ].index[0]!= 99 )
                {
                    field[ num ][ j ].index[ 0 ] = 99;
                    field[ num ][ j ].index[ 1 ] = 99;
                }
            } 
            delete_count = 0;  
         Drop_fieldblock( num );
        }
      
   }

}
//落ちた時に積まれていたブロックを下に落とす
void Block::Drop_fieldblock(int no)
{
    int i,j;
    
    for( i =no-1; i>1; i--) {
        for( j = 1; j < 11; j++ )
        {
            if( field[ i ][ j ].index[1] == 99 )
            {
                field[ i ][ j ] = field[ i ][ j ];
            }
            else
            {
                field[ i ][ j ].index[ 1 ]++;//フィールドのY座標を落とす
                field[i+1][ j ] = field[ i ][ j ];//１つ下の配列に要素丸ごと落とす
                field[i][j]=field[i-1][ j ];//上の配列を丸ごと落とす
            }
        }
    }
}
//破棄
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}
#include"block.h"
#include"color.h"
#include"color.cpp"
#include"mino.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

enum keyboard
{
	Left,
	Right,
	Up,
	Down,
	A,
	B,
};


//コンストラクタ
Block::Block()
{

	texture_ = NULL;
	count = 0;//カウント
	exist_fallingblock = false;//ブロック生成
	old_color = -99;
	old_form = -99;
	r_flag = false;
}

//初期化
bool Block::init()
{
	// テクスチャの読み込み
	if (!(texture_ = Texture::load(L"Texture/Tetris11_SingleT.png")))
	{
		// エラー
		return false;
	}
    
   //ネクスト初期化
	int i, j, k;
	for(k=0;k<3;k++)
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 2; j++)
			{
				next_block[k][i][j].color = -1000;
				next_block[k][i][j].index[0] = -1000;
				next_block[k][i][j].index[1] = -1000;

			}
		}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)//落ちているブロックの初期化
		{
			falling_block[i][j].index[0] = -1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].color = -1000;

		}

	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++)
		{
			field[i][j].color = -1;  //色情報初期化


			if (i == 21 || j == 0 || j == 11)//壁
			{

				field[i][j].index[0] = j;//左右当たり判定番号
				field[i][j].index[1] = i;//下当たり判定配列番号
				field[i][j].color = Black;
				field[i][j].is_empty = false;
			}
			else
				field[i][j].is_empty = true;
		}
	}
	return true;

}
//ゲームオーバー処理
void Block::Game_over()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (can_move(Down) == false && falling_block[i][j].index[1] == -1)
			{
				init_next();//ネクストの初期化
				r_flag = false;//フラグ初期化
				init_field();
			}
		}
}
//壁以外の初期化
bool Block::init_field()
{
	int i, j, k;

	for (i = 0; i < 21; i++)
		for (j = 1; j < 11; j++)
		{
			field[i][j].color = -1;  //色情報初期化
			for (k = 0; k < 2; k++) //座標初期化
			{
				field[i][j].index[k] = 99;
				field[i][j].is_empty = true;
			}
		}
	
	return true;
	
}
//ネクストの初期化
void Block::init_next()
{
	int i;
	for (i = 0; i < 6; i++)
	{
		next[i] = -1000;
	}

}

//ネクストブロックの初期化
void Block::init_next_block()
{
	int i, j, k;
	for(k=0;k<3;k++)
	for (i = 0; i < 4; i++)
		for (j = 0; j < 2; j++)
		{
			next_block[k][i][j].color = -1000;
			next_block[k][i][j].index[0] = -1000;
			next_block[k][i][j].index[1] = -1000;
			next_block[k][i][j].is_empty = true;//全てのブロックを空にする

		}


}
//ネクストブロックの生成
void Block::Create_next_block()
{
	int i, j, k;
	int mino_form[4][2] = { 0 };
	for(k=0;k<3;k++)
	for (i = 0; i < 4; i++)
		for (j = 0; j < 2; j++)
		{
			next_block[k][i][j].color = next[k];
		}

for(k=0;k<3;k++)
	for(i=0;i<4;i++)
		for (j = 0; j < 2; j++)
		{
			mino_form[i][j] = small_mino[next[k]][i][j];
			
			next_block[k][i][j].index[0] = j;
			next_block[k][i][j].index[1] = i;
			if (mino_form[i][j] == 1)
			{
				next_block[k][i][j].is_empty = false;
			}
		}
	
}


//ブロック生成
void Block::Make_fallingblock()
{
	srand(time(NULL));
	int i, j;
	int k, l;
	int color;//色
	int form;//形
	int mino_type[4][4];
	
	//はじめのみ生成
	if (r_flag==false) {
		for (k = 0; k < 7; k++)
		{
			next[k] = rand() % 7;

			for (l = k - 1; l < k; l--)
			{
				if (l == -1)
				{
					break;
				}
				if (next[k] == next[l])//もう一度乱数生成//パターンが被った場合
				{
					k--;
				}
			}
			
		}
		r_flag = true;
		
	}
	init_next_block();//初期化
	
	color = next[0];
	form = next[0];
	
	move_up();//繰り上げ
	Create_next_block();//ネクストブロックの表示するための何か

	old_color = color;//前の色、形として保存
	old_form = form;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			mino_type[i][j] = minos[form][0][i][j];//ミノ形のコピー
		}


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			falling_block[i][j].index[0] = j + 4;//初期値
			falling_block[i][j].index[1] = i - 1;

			if (mino_type[i][j] == 1)//タイプの中にブロックが入っている場合
			{
				falling_block[i][j].is_empty = false;
			}
			falling_block[i][j].color = color;//色情報を持たせる

		}
	}

	
	
}
//繰り上げ
void Block::move_up()
{
	srand(time(NULL));

	next[0] = next[1];//添え字の中身を繰り上げ
	next[1] = next[2];
	next[2] = next[3];
	next[3] = next[4];
	next[4] = next[5];
	

	do {
		next[5] = rand() % 7;

	} while (next[5] == next[0]||next[5]==next[1]||next[5]==next[2]||next[5]==next[3]||next[5]==next[4]);//中身が１つでもかぶったら、乱数をぶち込む
}
//落ちるブロックの初期化
void Block::init_fallingblock()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)//初期値に戻す
		{
			falling_block[i][j].index[0] = -1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].is_empty = true;
		}

}
//更新処理
void Block::update()
{
	//各インターフェースの情報取得
	Keyboard::State key = Key::getKeyState();
	GamePad::State pad = Pad::getState();
	tracker.Update(key);//トラッカーアップデート
	Btracker.Update(pad);//パッドトラッカーアップデート

	int i, j;

	if (exist_fallingblock == false)//ブロック生成
	{

		init_fallingblock();//ブロック初期化
		Make_fallingblock();//ブロックを作る
		exist_fallingblock = true;
		Game_over();
	}


	//自動落下
	count++;

	//方向キーでの移動
	if (key.Down || pad.dpad.down)
	{
		if (count % 3 == 0)//下の入力がある場合
		{
			move_down();
		}
	}
	else if (count % 50 == 0)//自動落下
	{
		move_down();
	}

	if (key.Left || pad.dpad.left)
	{
		if (count % 6 == 0)
		{
			if (can_move(Left) == true)//移動できる場合
			{
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						falling_block[i][j].index[0]--;//左
					}
			}
		}
	}
	if (key.Right || pad.dpad.right)
	{
		if (count % 6 == 0)
		{
			if (can_move(Right) == true)
			{
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						falling_block[i][j].index[0]++;//右
					}
			}


		}

	}


	if (tracker.pressed.Up || Btracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
	{


		while (move_down() == true);//ハードドロップ

	}


	if (tracker.pressed.A || Btracker.a == GamePad::ButtonStateTracker::PRESSED)//回転
	{
		Rotate(A, old_form);
	}
	if (tracker.pressed.Z || Btracker.b == GamePad::ButtonStateTracker::PRESSED)
	{
		Rotate(B, old_form);
	}



}

//下に落ちる処理
bool Block::move_down()
{
	int i, j;
	if (can_move(Down) == true)//動けるなら
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				falling_block[i][j].index[1]++;//配列番号(y座標)降下
			}
	}
	if (can_move(Down) == false)
	{
		Copy_fallingblock_in_field();//配列に情報を格納
		return false;
	}
	return true;
}

//回転処理
//回転行列を使った回転処理
//パターン、形を引数として受け取る
//反時計回りを正とする
bool Block::Rotate(int pattern, int form)
{
	int i, j;
	block copy_block[4][4] = { -1000 };//コピー配列//初期値
	int p, q;

	if (form == 0)//O型の場合回転なし
	{
		return false;
	}

	//押されたボタンのパターンによって分岐
	switch (pattern)
	{
		//Aボタン、Aキーが押された場合
	case A:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				p = falling_block[1][1].index[0];
				q = falling_block[1][1].index[1];
				copy_block[i][j] = falling_block[i][j];
				copy_block[i][j].index[0] = -(falling_block[i][j].index[1] - q) + p;
				copy_block[i][j].index[1] = (falling_block[i][j].index[0] - p) + q;
			}

		if (can_rotate(copy_block) == true)
		{
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					falling_block[i][j].index[0] = copy_block[i][j].index[0];
					falling_block[i][j].index[1] = copy_block[i][j].index[1];
				}return true;
		}
		//Bボタン、ｚキーが押された場合
	case B:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				p = falling_block[1][1].index[0];
				q = falling_block[1][1].index[1];
				copy_block[i][j] = falling_block[i][j];
				copy_block[i][j].index[0] = (falling_block[i][j].index[1] - q) + p;
				copy_block[i][j].index[1] = -(falling_block[i][j].index[0] - p) + q;
			}
		//回転できるかどうか
		if (can_rotate(copy_block) == true)
		{
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					falling_block[i][j].index[0] = copy_block[i][j].index[0];
					falling_block[i][j].index[1] = copy_block[i][j].index[1];
				}
			return true;
		}
	}

}
//回転できるかどうか
bool Block::can_rotate(block copy[4][4])
{
	int i, j;
	int count = 0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (copy[i][j].is_empty == false)
			{
				if (field[copy[i][j].index[1]][copy[i][j].index[0]].is_empty == false)
				{
					count++;

				}
			}

		}
	if (count == 0)
	{
		return true;
	}
	else
		return false;


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

			if (field[i][j].is_empty == false)
			{
				Sprite::draw(texture_, position_, &rect);
			}
		}
	}
	//動いてるブロック描画
	RECT Arect;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			Vector2 texture_UV = get_textureUV_from(falling_block[i][j].color);
			Arect.top = texture_UV.x;
			Arect.left = texture_UV.y;
			Arect.right = Arect.left + 25L;
			Arect.bottom = Arect.top + 25L;

			position2.x = (falling_block[i][j].index[0] * 25) + 487;
			position2.y = (falling_block[i][j].index[1] * 25) + 173;

			if (falling_block[i][j].is_empty == false)
			{
				if (position2.y >= 173) //座標内に入ったら、描画
				{
					Sprite::draw(texture_, position2, &Arect);
				}
			}
		}

	//ネクスト１つ目
	RECT Brect;
		for(i=0;i<4;i++)
			for (j = 0; j < 2; j++)
			{
				Vector2 texture_UV = get_textureUV2_from(next_block[0][i][j].color);
				Brect.top = texture_UV.x;
				Brect.left = texture_UV.y;
				Brect.right = Brect.left + 15L;
				Brect.bottom = Brect.top + 15L;

				position3.x = (next_block[0][i][j].index[0] * 15) + 623;
				position3.y = (next_block[0][i][j].index[1] * 15) + 99;

				if (next_block[0][i][j].is_empty == false)
				{
					Sprite::draw(texture_, position3, &Brect);
				}
			}
		//ネクスト２つ目
		RECT Crect;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 2; j++)
			{
				Vector2 texture_UV = get_textureUV2_from(next_block[1][i][j].color);
				Crect.top = texture_UV.x;
				Crect.left = texture_UV.y;
				Crect.right = Crect.left + 15L;
				Crect.bottom = Crect.top + 15L;

				position4.x = (next_block[1][i][j].index[0] * 15) + 668;
				position4.y = (next_block[1][i][j].index[1] * 15) + 99;

				if (next_block[1][i][j].is_empty == false)
				{
					Sprite::draw(texture_, position4, &Crect);
				}
			}
		//ネクスト３つ目
		RECT Drect;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 2; j++)
			{
				Vector2 texture_UV = get_textureUV2_from(next_block[2][i][j].color);
				Drect.top = texture_UV.x;
				Drect.left = texture_UV.y;
				Drect.right = Drect.left + 15L;
				Drect.bottom = Drect.top + 15L;

				position5.x = (next_block[2][i][j].index[0] * 15) + 713;
				position5.y = (next_block[2][i][j].index[1] * 15) + 99;

				if (next_block[2][i][j].is_empty == false)
				{
					Sprite::draw(texture_, position5, &Drect);
				}
			}
}


//動けるかどうか
bool Block::can_move(int direction)
{
	int i, j;//ループ変数
	int checkx = -1000, checky = -1000;//代入用関数
	switch (direction)//方向キーの種類によって、分岐
	{
	case Left:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				if (falling_block[i][j].is_empty == false)
				{
					checkx = falling_block[i][j].index[0];//座標番号の受け渡し
					checky = falling_block[i][j].index[1];
					if (field[checky][checkx - 1].is_empty == false)//ブロックの場合
					{
						return false;
					}


				}

			}
		return true;
		break;
	case Down:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{//落ちているブロックの中身が入っている場合、配列番号を代入
				if (falling_block[i][j].is_empty == false)
				{
					checkx = falling_block[i][j].index[0];
					checky = falling_block[i][j].index[1];

					if (field[checky + 1][checkx].is_empty == false)
					{
						return false;
					}


				}
			}
		return true;
		break;
	case Right:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				//落ちているブロックの中身が入っている場合、配列番号を代入
				if (falling_block[i][j].is_empty == false)
				{
					checkx = falling_block[i][j].index[0];
					checky = falling_block[i][j].index[1];

					if (field[checky][checkx + 1].is_empty == false)
					{
						return false;
					}
				}
			}
		return true;
		break;
	}

}


//落ちているブロックをフィールドの中に移す
void Block::Copy_fallingblock_in_field()
{
	int i, j;
	int max_y = -100;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (falling_block[i][j].is_empty == false) //初期値が入っていた場合は行わない
			{
				field[falling_block[i][j].index[1]][falling_block[i][j].index[0]] = falling_block[i][j];//faling_blockの中身を代入する

				if (max_y < falling_block[i][j].index[1])
				{
					max_y = falling_block[i][j].index[1];
				}

			}


		}
	for (i = max_y - 3; i <= max_y; i++)
	{
		Delete_fieldblock(i);//消す処理
	}
	exist_fallingblock = false;//新しいブロック生成
}

//そろったブロックを消す処理
void Block::Delete_fieldblock(int num)
{

	int  j;
	int delete_count = 0;//カウンタ
	int count;

	for (j = 1; j < 11; j++)
	{
		if (field[num][j].is_empty == false)//indexの中身が初期値以外の値の場合
		{
			delete_count++;
		}
		else//初期値が１つでも入っていたら初期化
		{
			delete_count = 0;
		}

		if (delete_count >= 10)//行の中身がすべてブロックの場合
		{
			for (j = 1; j < 11; j++)//そろった行の中身の初期化
			{

				field[num][j].is_empty = true;

			}
			delete_count = 0;
			Drop_fieldblock(num);
		}

	}

}
//落ちた時に積まれていたブロックを下に落とす
void Block::Drop_fieldblock(int no)
{
	int i, j;

	for (i = no - 1; i > 1; i--) {
		for (j = 1; j < 11; j++)
		{
			if (field[i][j].is_empty == true)//現在見ているブロックが空の場合、以下の処理を実行しない
			{
				continue;//処理を飛ばす
			}
			field[i][j].index[1]++;//Y座標降下
			field[i + 1][j] = field[i][j];//下の座標に入れ替え
			field[i][j] = field[i - 1][j];//上の座標といれかえ

		}
	}
}


//破棄
void Block::destroy()
{
	SAFE_RELEASE(texture_);


}
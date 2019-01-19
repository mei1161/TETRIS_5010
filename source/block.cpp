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


//�R���X�g���N�^
Block::Block()
{

	texture_ = NULL;
	count = 0;//�J�E���g
	exist_fallingblock = false;//�u���b�N����
	old_color = -99;
	old_form = -99;
}

//������
bool Block::init()
{
	// �e�N�X�`���̓ǂݍ���
	if (!(texture_ = Texture::load(L"Texture/Tetris11_SingleT.png")))
	{
		// �G���[
		return false;
	}
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)//�����Ă���u���b�N�̏�����
		{
			falling_block[i][j].index[0] = -1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].color = -1000;

		}

	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++)
		{
			field[i][j].color = -1;  //�F��񏉊���


			if (i == 21 || j == 0 || j == 11)//��
			{

				field[i][j].index[0] = j;//���E�����蔻��ԍ�
				field[i][j].index[1] = i;//�������蔻��z��ԍ�
				field[i][j].color = Black;
				field[i][j].is_empty = false;
			}
			else
				field[i][j].is_empty = true;


		}
	}



	return true;

}
//�Q�[���I�[�o�[����
void Block::Game_over()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (can_move(Down) == false && falling_block[i][j].index[1] == -1)
			{
				init_field();
			}
		}
}
//�ǈȊO�̏�����
bool Block::init_field()
{
	int i, j, k;

	for (i = 0; i < 21; i++)
		for (j = 1; j < 11; j++)
		{
			field[i][j].color = -1;  //�F��񏉊���
			for (k = 0; k < 2; k++) //���W������
			{
				field[i][j].index[k] = 99;
				field[i][j].is_empty = true;
			}
		}
	return true;

}



//�u���b�N����
void Block::Make_fallingblock()
{
	srand(time(NULL));
	int i, j;
	int color;//�F
	int form;//�`
	int mino_type[4][4];
	color = rand() % 7;
	form = rand() % 7;

	while (old_form == form)//�`�������ꍇ���[�v
	{
		form = rand() % 7;
	}

	while (old_color == color)//�F�������ꍇ���[�v
	{
		color = rand() % 7;
	}
	old_color = color;//�O�̐F�A�`�Ƃ��ĕۑ�
	old_form = form;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			mino_type[i][j] = minos[5][0][i][j];//�~�m�`�̃R�s�[
		}


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			falling_block[i][j].index[0] = j + 4;//�����l
			falling_block[i][j].index[1] = i - 1;

			if (mino_type[i][j] == 1)//�^�C�v�̒��Ƀu���b�N�������Ă���ꍇ
			{
				falling_block[i][j].is_empty = false;
			}
			falling_block[i][j].color = color;//�F������������

		}
	}


}
//������u���b�N�̏�����
void Block::init_fallingblock()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)//�����l�ɖ߂�
		{
			falling_block[i][j].index[0] = -1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].is_empty = true;
		}

}
//�X�V����
void Block::update()
{
	//�e�C���^�[�t�F�[�X�̏��擾
	Keyboard::State key = Key::getKeyState();
	GamePad::State pad = Pad::getState();
	tracker.Update(key);

	int i, j;

	if (exist_fallingblock == false)//�u���b�N����
	{

		init_fallingblock();//�u���b�N������
		Make_fallingblock();//�u���b�N�����
		exist_fallingblock = true;
		Game_over();
	}


	//��������
	count++;

	//�����L�[�ł̈ړ�
	if (key.Down || pad.dpad.down)
	{
		if (count % 3 == 0)//���̓��͂�����ꍇ
		{
			move_down();
		}
	}
	else 	if (count % 60 == 0)//��������
	{
		move_down();
	}

	if (key.Left || pad.dpad.left)
	{
		if (count % 6 == 0)
		{
			if (can_move(Left) == true)//�ړ��ł���ꍇ
			{
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						falling_block[i][j].index[0]--;//��
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
						falling_block[i][j].index[0]++;//�E
					}
			}


		}

	}


	if (tracker.pressed.Up || pad.dpad.up)
	{
		
		
			while (move_down() == true);
		
	}


	if (tracker.pressed.A|| pad.buttons.a)
	{
		Rotate(A,old_form);
	}
	if (tracker.pressed.Z|| pad.buttons.b)
	{
		Rotate(B,old_form);
	}



}

//���ɗ����鏈��
bool Block::move_down()
{
	int i, j;
	if (can_move(Down) == true)//������Ȃ�
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				falling_block[i][j].index[1]++;//�z��ԍ�(y���W)�~��
			}
	}
	if (can_move(Down) == false)
	{
		Copy_fallingblock_in_field();//�z��ɏ����i�[
		return false;
	}
	return true;
}

//��]����
bool Block::Rotate(int pattern,int form)
{
	int i, j;
	block copy_block[4][4] = { -1000 };//�R�s�[�z��
	int p, q;

	switch (pattern)
	{
	case A:	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			p = falling_block[1][1].index[0];
			q = falling_block[1][1].index[1];
			copy_block[i][j] = falling_block[i][j];
			copy_block[i][j].index[0] = -(falling_block[i][j].index[1] - q) + p;
			copy_block[i][j].index[1] = (falling_block[i][j].index[0] - p) + q;
		}


			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					falling_block[i][j].index[0] = copy_block[i][j].index[0];
					falling_block[i][j].index[1] = copy_block[i][j].index[1];
				}return true;

	case B:for(i=0;i<4;i++)
		for (j = 0; j < 4; j++)
		{
			p = falling_block[1][1].index[0];
			q = falling_block[1][1].index[1];
			copy_block[i][j] = falling_block[i][j];
		}
	}


	
}

//�`��
void Block::draw()
{

	int i, j;
	//�Ǖ`��//�ł܂����u���b�N�̕`��
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
	//�����Ă�u���b�N�`��
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
				if (position2.y >= 173) //���W���ɓ�������A�`��
				{
					Sprite::draw(texture_, position2, &Arect);
				}
			}
		}


}


//�����邩�ǂ���
bool Block::can_move(int direction)
{
	int i, j;//���[�v�ϐ�
	int checkx = -1000, checky = -1000;//����p�֐�
	switch (direction)//�����L�[�̎�ނɂ���āA����
	{
	case Left:
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				if (falling_block[i][j].is_empty == false)
				{
					checkx = falling_block[i][j].index[0];//���W�ԍ��̎󂯓n��
					checky = falling_block[i][j].index[1];
					if (field[checky][checkx - 1].is_empty == false)//�u���b�N�̏ꍇ
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
			{//�����Ă���u���b�N�̒��g�������Ă���ꍇ�A�z��ԍ�����
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
				//�����Ă���u���b�N�̒��g�������Ă���ꍇ�A�z��ԍ�����
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


//�����Ă���u���b�N���t�B�[���h�̒��Ɉڂ�
void Block::Copy_fallingblock_in_field()
{
	int i, j;
	int max_y = -100;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (falling_block[i][j].is_empty == false) //�����l�������Ă����ꍇ�͍s��Ȃ�
			{
				field[falling_block[i][j].index[1]][falling_block[i][j].index[0]] = falling_block[i][j];//faling_block�̒��g��������

				if (max_y < falling_block[i][j].index[1])
				{
					max_y = falling_block[i][j].index[1];
				}

			}


		}
	for (i = max_y - 3; i <= max_y; i++)
	{
		Delete_fieldblock(i);//��������
	}
	exist_fallingblock = false;//�V�����u���b�N����
}

//��������u���b�N����������
void Block::Delete_fieldblock(int num)
{

	int  j;
	int delete_count = 0;//�J�E���^
	int count;

	for (j = 1; j < 11; j++)
	{
		if (field[num][j].is_empty == false)//index�̒��g�������l�ȊO�̒l�̏ꍇ
		{
			delete_count++;
		}
		else//�����l���P�ł������Ă����珉����
		{
			delete_count = 0;
		}

		if (delete_count >= 10)//�s�̒��g�����ׂău���b�N�̏ꍇ
		{
			for (j = 1; j < 11; j++)//��������s�̒��g�̏�����
			{

				field[num][j].is_empty = true;

			}
			delete_count = 0;
			Drop_fieldblock(num);
		}

	}

}
//���������ɐς܂�Ă����u���b�N�����ɗ��Ƃ�
void Block::Drop_fieldblock(int no)
{
	int i, j;

	for (i = no - 1; i > 1; i--) {
		for (j = 1; j < 11; j++)
		{
			if (field[i][j].is_empty == true)//���݌��Ă���u���b�N����̏ꍇ�A�ȉ��̏��������s���Ȃ�
			{
				continue;//�������΂�
			}
			field[i][j].index[1]++;//Y���W�~��
			field[i + 1][j] = field[i][j];//���̍��W�ɓ���ւ�
			field[i][j] = field[i - 1][j];//��̍��W�Ƃ��ꂩ��

		}
	}
}


//�j��
void Block::destroy()
{
	SAFE_RELEASE(texture_);


}
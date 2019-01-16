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


//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
	count = 0;//�J�E���g
	exist_fallingblock = false;//�u���b�N����
  
}

//������
bool Block::init()
{
    // �e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // �G���[
        return false;
    }
	int i, j, k;
	for(i=0;i<4;i++)
		for (j = 0; j < 4; j++)//�����Ă���u���b�N�̏�����
		{
			falling_block[i][j].index[0] =-1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].color = -1000;
			falling_block[i][j].is_wall = false;
		}

	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++)
		{
			field[i][j].color =-1;  //�F��񏉊���
			for (k = 0; k < 2; k++) //���W������
			{
				field[i][j].index[k] = 99;
			}
			if (i == 21 || j == 0 || j == 11)//��
			{
				field[i][j].is_wall = true;
				field[i][j].index[0] = j;//���E�����蔻��ԍ�
				field[i][j].index[1] = i;//�������蔻��z��ԍ�
				field[i][j].color =Black;
			}
			else//�ǈȊO
			{
				field[i][j].is_wall = false;//�ǂ̓����蔻��Ȃ�
			}

		}
	}

    return true;
    
}
//�u���b�N����
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
//�X�V����
void Block::update()
{
	
	Keyboard::State key = Key::getKeyState();
	GamePad::State pad = Pad::getState();
    int i, j;
	if (exist_fallingblock == false) {
		/*falling_block[0][0].index[0] =1; //faling_block��X���W
		falling_block[0][0].index[1] =-1;//falling_block ��Y���W
		falling_block[0][0].color = Green;*/
        Make_fallingblock();
		exist_fallingblock = true;
	}

	count++;
	//��������

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
                        falling_block[ i ][ j ].index[ 0 ]--;//��
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
                        falling_block[ i ][ j ].index[ 0 ]++;//�E
                    }
				}
		}
	}
}
void Block::move_down()
{
	int i, j;
			if (can_move(Down)== true)//������Ȃ�
			{
				for(i=0;i<4;i++)
					for (j = 0; j < 4; j++)
					{
						falling_block[i][j].index[1]++;//�z��ԍ�(y���W)�~��

					}
				if (can_move(Down) == false)
				{
					Copy_fallingblock_in_field();
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

			Sprite::draw(texture_, position_, &rect);
		}
	}
	//�����Ă�u���b�N�`��
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
            if( position2.y >= 173 ) //���W���ɓ�������A�`��
            {
            Sprite::draw( texture_, position2, &Arect );
             }
		}

		
}


//�����邩�ǂ���
bool Block::can_move(int direction)
{
    int i, j;//���[�v�ϐ�
    int checkx,checky;//����p�֐�
    switch( direction )//�����L�[�̎�ނɂ���āA����
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
            {//�����Ă���u���b�N�̒��g�������Ă���ꍇ�A�z��ԍ�����
                if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 0 ] >= -1 )
                {
                    checkx = falling_block[ i ][ j ].index[ 0 ];
                    checky = falling_block[ i ][ j ].index[ 1 ];
                }

                if( field[ checky + 1 ][ checkx ].index[1]==21||field[checky + 1 ][checkx].index[1]!=99)//1���̔z��
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
			//�����Ă���u���b�N�̒��g�������Ă���ꍇ�A�z��ԍ�����
            if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 1 ] >= -1 )
            {
                checkx = falling_block[ i ][ j ].index[ 0 ];
                checky = falling_block[ i ][ j ].index[ 1 ];
            }

            if( field[ checky][ checkx+1 ].is_wall == true )//����̔z��ɕǂ����邩�ǂ���
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
//�����Ă���u���b�N���t�B�[���h�̒��Ɉڂ�
void Block::Copy_fallingblock_in_field()
{
    int i, j;
        for(i=0;i<4;i++)
            for( j = 0; j < 4; j++ )
            {
                if( falling_block[ i ][ j ].index[ 0 ] >= -1 && falling_block[ i ][ j ].index[ 1 ] >= -1 ) //�����l�������Ă����ꍇ�͍s��Ȃ�
                {
                    field[ falling_block[ i ][ j ].index[ 1]][ falling_block[ i ][ j ].index[0] ] = falling_block[ i ][ j ];//faling_block�̒��g��������
					Delete_fieldblock(falling_block[i][j].index[1]);//��������
                }
        exist_fallingblock = false;//�V�����u���b�N����
    }
}

//��������u���b�N����������
void Block::Delete_fieldblock(int num)
{
	
    int  j;
    int delete_count=0;//�J�E���^
    for( j = 1; j < 11; j++ )
    {
        if( field[ num ][ j ].index[ 0 ] != 99 )//index�̒��g�������l�ȊO�̒l�̏ꍇ
        {
            delete_count++;
        }
        else//�����l���P�ł������Ă����珉����
        {
            delete_count = 0;
        }

        if(delete_count>=10 )//�s�̒��g�����ׂău���b�N�̏ꍇ
        {
            for( j = 1; j < 11; j++ )//��������s�̒��g�̏�����
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
//���������ɐς܂�Ă����u���b�N�����ɗ��Ƃ�
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
                field[ i ][ j ].index[ 1 ]++;//�t�B�[���h��Y���W�𗎂Ƃ�
                field[i+1][ j ] = field[ i ][ j ];//�P���̔z��ɗv�f�ۂ��Ɨ��Ƃ�
                field[i][j]=field[i-1][ j ];//��̔z����ۂ��Ɨ��Ƃ�
            }
        }
    }
}
//�j��
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}
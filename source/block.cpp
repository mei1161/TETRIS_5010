#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down,
    None,
};
//�萔


const int WALL = 99;//�����蔻��̂���u���b�N

//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y =173L;//�u���b�N���W
    position_.x =511L;
    plus =25.0F;//�ړ���
    Animation_counter = 0;//�A�j���[�V�����J�E���^
    move_ = false;//�����邩�ǂ���
    count = 0;//�J�E���^
    flag = false;
    r_flag = false;
    cdelete = 0;
    Aflag = true;
    cauto = 0;
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
    int i;//���[�v�J�E���^
    int j;
    for( i = 0; i < 22; i++ )
        for( j = 0; j < 12; j++ )//�ǈȊO
        {
            block[ i ][ j ] =0;
            field[ i ][ j ] = 0;

            if( i == 21 )//��
            {
                block[ i ][ j ] = WALL;
                field[ i ][ j ] = WALL;
          }
            if( j == 0 || j == 11 )//��
            {
                block[ i ][ j ] =WALL;//���ݓ����Ă�u���b�N
                field[ i ][ j ] = WALL;//�Œ肳��Ă���u���b�N
            }


            
        }
    
    
    return true;
    
}


//�X�V
//������������
//�L�[�œ�������
void Block::update()
{
    Keyboard::State key = Key::getKeyState();
    GamePad::State pad = Pad::getState();
    //��������
    if( ++cauto > 60 )
    {
        key_state = None;
        position_.y += plus;//��ړ�
        cauto = 0;//�J�E���^������
        Check();//�m�F
    }
    if( ++count >= 5 )
    {
        if( key.Right )//�E
        {
            key_state = Right;
            Animation();
            Check();
        }
        else if( key.Left )
        {
            key_state = Left;
            Animation();
            Check();
        }
        else if( key.Down )
        {
            key_state = Down;
            Animation();
            Check();
        }

        else if( key.Up )
        {
            key_state = Up;
            Animation();
            Check();
        }
        Check();
		Collusion();//�����蔻��
        Storing();
    }

}
//�A�j���[�V��������

void Block::Animation()
{
    if( Aflag == true )
    {

        //�A�j���[�V��������
        if( ++count >= 25 ) {
            switch( key_state ) {
            case Left: position_.x -= plus; break;
            case Right: position_.x += plus; break;
            case Down: position_.y += plus; break;
            case Up:position_.y += plus; break;

            }
            count = 0;
        }
    }
}
//�m�F����p�̊֐�(�z��)
void Block::Check()
{
    int i2, j2;//���̔z��ԍ����i�[����p�̕ϐ�
    i2 = 0; j2 = 0;
    i = (position_.y - 148) / 25;//���W����A��v��������ԍ������߂�
    j = (position_.x - 486) / 25;
    switch( key_state )
    {
    case Down:i2 = i + 1; j2 = j; break;
    case None:i2 = i+1; j2 = j; break;//��������
    case Left:i2 = i; j2 = j - 1; break;
    case Right:i2 = i; j2 = j + 1; break;
    case Up:i2 = i + 1; j2 = j; break;
   
    }

    if(field[i2][j2]==99 )//�ǂ������ꍇ
    {
        if( key_state == Left )//��E���̍��W�ɂ���
        {
			j2++;

        }
        if( key_state == Right )//������̍��W�ɂ���
        {
			j2--;
        }
    }
    if( field[ i2 ][ j2 ] == 1)//���̔z�񂪁A�u���b�N�������ꍇ
    {
        flag = true;//�z��Ɋi�[
        Aflag = false;//�A�j��-�V�������s��Ȃ�
    }
    else{
        Aflag = true;
		}



}

//�����蔻��
void Block::Collusion()
{
    //�����蔻��
    if( position_.x <= 486 )//�E�e
    {
        position_.x += plus;
    }
    if( position_.x >= 756 )//���e
    {
        position_.x -= plus;
    }
    if( position_.y >= 670 )//��
    {
        position_.y = 672;
		flag = true;
    }

}




//�`��
void Block::draw()
{
    RECT rect;//�u���b�N�̕`��
    rect.top = 956L;
    rect.left = 688L;
    rect.right = rect.left + 25L;
    rect.bottom = rect.top + 25L;


 Sprite::draw( texture_, position_, &rect );
 RECT Arect;//�u���b�N�̕`��//�Ǖ`��
 Arect.top = 957L;
 Arect.left = 713L;
 Arect.right = Arect.left + 25L;
 Arect.bottom = Arect.top + 25L;

 int i, j;
 for( i = 0; i < 22; i++ ) {
     for( j = 0; j < 12; j++ )
     {
        if( block[ i ][ j ] == WALL )//�����蔻��̕ǂ̕\��
         {
             Aposition_.x = (j* 25) + 487;
             Aposition_.y = (i * 25) + 173;
             Sprite::draw( texture_, Aposition_, &Arect );
         }
         if( field[ i ][ j ] == 1 )//�u���b�N�̕\��
         {
             position2.x= (j* 25) + 487;
             position2.y = (i* 25) + 173;
             Sprite::draw( texture_, position2, &rect );
         }

     }
 }
 

}

//�j��
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}


//�z��Ɋi�[
void Block::Storing()
{
    int i, j;
    int count;//i�̃J�E���g�p�ϐ�
    if( flag == true )
    {
        i= (position_.y-148) / 25;//���W����A��v��������ԍ������߂�
        j= (position_.x-486) / 25;
        field[ i ][ j ] = 1;//�u���b�N�̒��g������
        
        count = i;
        for( j = 1; j < 11; j++ )//�u���b�N���������z��̗v�f��������m�F
        {
          
            if( field[count][ j ] == 1 )//�u���b�N�̒��g���P�Ȃ�deletecount�C���N�������g
            {
                cdelete++;
            }
            else//�u���b�N�������Ă��Ȃ��ꍇ�́Adeletecount�̏��������s
                cdelete = 0;
                
        }

       


		Delete(count);//��������
        position_.y = 173L;//�u���b�N���W
        position_.x = 511L;
      

    }

     flag = false;
}

//�폜����
void Block::Delete(int count)
{

    
    int k;
	if (cdelete>=10)//�J�E���g��10�ȏ�Ȃ�
	{
		cdelete = 0;//�J�E���g�̏�����
		for (k = 1; k < 11; k++)
		{
			if (field[count][k] == 1)//�u���b�N�̒��g�̏�����
			{
				field[count][k] = 0;
			}
		}
        Drop(count);
	}

}
//�����ꂽ�ꍇ�A�ς�ł���u���b�N�����ɗ��Ƃ�����
void Block::Drop(int count)
{
    for( i = count; i >0; i-- )
        for( j = 1; j < 11; j++ )
        {
            if( field[ i ][ j ] == 1 ) {
                field[ i + 1 ][ j ] = field[ i ][ j ];
                field[ i ][ j ] =field[ i - 1 ][ j ];
            }
    }
}

//������邩�ǂ���
bool Block::can_fall()
{
	if (field[i + 1][j] == 99 || field[i + 1][j] == 1)
	{
		return false;
	}
	else {
		return true;
		field[i][j] == 1;

	}
}

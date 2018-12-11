#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down,
    None,
    B
};
//�萔




//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y =173L;//�u���b�N���W
    position_.x =511L;
    plus =25.0F;
    Animation_counter = 0;
    move_ = false;
    count = 0;
    flag = false;
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
    {
        for( j = 0; j < 12; j++ )
        {
            block[ i ][ j ] = 0;

            if( i == 0 || i == 21 || j ==11 )//�Փ˔���̂���ꏊ��99����
            {
                block[ i ][ j ] = 99;
            }
        }
        block[ 1 ][ 0 ] = 1;
    }
    return true;
}


//�X�V
void Block::update()
{
    Keyboard::State key = Key::getKeyState();
    int i, j;
  

    
   if( position_.y <= 670 ) {


        if( key.Left )
        {
            key_state = Left;
            Animation();
        }
        else if( key.Right )
        {
            key_state = Right;
            Animation();
        }
        else if( key.Up )
        {
            key_state = Up;
            Animation();
        }
        else if( key.Down )
        {
            key_state = Down;
            Animation();
        }
        else
            key_state = None;
        Animation();
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
  
   
    
    
}

//�j��
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}

//�A�j���[�V��������
void Block::Animation()
{

    //�A�j���[�V��������
    if( ++count >= 10) {
        switch( key_state ) {
        case Left: position_.x -= plus; break;
        case Right: position_.x += plus; break;
        case Down: position_.y += plus; break;
        case Up:position_.y -= plus; break;
        case None:position_.y += plus; break;
        case B:position_.y += plus; break;
        }
        count = 0;
    }
}

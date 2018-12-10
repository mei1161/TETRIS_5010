#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down,
    None
};
//�萔




//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y = 173L;//�u���b�N���W
    position_.x = 635L;
    plus =25.0F;
    Animation_counter = 0;
    move_ = false;
    count = 0;
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
    return true;




}


//�X�V
void Block::update()
{
    Keyboard::State key = Key::getKeyState();
    
    
    if( position_.y <= 670&&position_.x<=721&&position_.x>=512) {
        if( key.Left )
        {
            key_state = Left;
        }
        else if( key.Right )
        {
            key_state = Right;
        }
        else if( key.Up )
        {
            key_state = Up;
        }
        else if( key.Down )
        {
            key_state = Down;
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
    if( ++count >= 25 ) {
        switch( key_state ) {
        case Left: position_.x -= plus; break;
        case Right: position_.x += plus; break;
        case Down: position_.y += plus; break;
        case Up:position_.y -= plus; break;
        case None:position_.y += plus; break;
        }
        count = 0;

    }
}
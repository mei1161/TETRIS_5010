#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down
};
//�萔




//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y = 173L;//�u���b�N���W
    position_.x = 635L;
    plus =2.5F;
    Animation_counter = 0;
    move_ = false;
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
    
    if( position_.y <= 670 ) {
        if( key.Left )
        {
            move_ = true;
            key_state = Left;

        }
        else if( key.Right)
        {
            move_ = true;
            key_state = Right;
        }
        else if( key.Up )
        {
            move_ = true;
            key_state = Up;
        }
        else if( key.Down )
        {
            move_ = true;
            key_state = Down;

        }
        else
        {
            move_ = true;
            key_state = Down;
        }

 
        
 
                switch( key_state ) {
                case Left: position_.x -= plus; break;
                case Right: position_.x +=plus; break;
                case Down: position_.y += plus; break;
                case Up:position_.y -= plus; break;
                }
            
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

}
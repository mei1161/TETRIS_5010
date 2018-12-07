#include"block.h"

enum
{
    Left,
    Right,
    Up,
    Down
};




//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y = 173L;
    position_.x = 635L;
    plus =2.5F;

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
    int count = 0;
    Keyboard::State key = Key::getKeyState();
  

   
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
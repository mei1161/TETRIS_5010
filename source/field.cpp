#include"field.h"

//���O���
using namespace DirectX;
using namespace SimpleMath;


//�R���X�g���N�^
Field::Field()
{
    texture_ = NULL;
    width_ = 720;//��
    height_ = 1280;//�c
}


//������
bool Field::init()
{
    //�e�N�X�`���ǂݍ���
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // �G���[
        Error::showDialog( "Tetris11_SingleT.png���J���܂���ł���" );
        return false;
    }
    return true;
    }

    



//�`��
void Field::draw()
{
    // �`��͈͂̐ݒ�
    RECT rect;
    rect.top = 0L;//�e�N�X�`�����[(y)
    rect.left = 0L;//�e�N�X�`�����[(x)
    rect.right = height_;//�e�N�X�`���E�[(x)
    rect.bottom = width_;//�e�N�X�`���E�[(y)


    Sprite::draw( texture_, Vector2::Zero, &rect );//�`��


}

//�j��
void Field::destroy()
{
    SAFE_RELEASE( texture_ );//�e�N�X�`���̔j��
   
}
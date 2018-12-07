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
    int i;//���[�v�J�E���^
    int j;
    for( i = 0; i < 22; i++ )
    {
        for( j = 0; j < 12; j++ )
        {
            if( i == 0 || i == 21 || j == 11 )
            {
                field[ i ][ j ] = 9;
            }
        }
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
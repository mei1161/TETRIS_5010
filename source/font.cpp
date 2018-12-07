#include "font.h"

////////////////////////////////////
// ���̂̐錾
////////////////////////////////////
SpriteFont* Font::font_;

////////////////////////////////////
// ������
////////////////////////////////////
bool Font::init()
{
    // �X�v���C�g�t�H���g�̃��������m��
    font_ = new SpriteFont( Direct3D::getDevice(), L"font_cica.spritefont" );

    // �������m�ۃ`�F�b�N
    if( !font_ )
    {
        // �G���[
        Error::showDialog( "�X�v���C�g�t�H���g�̃������m�ۂɎ��s���܂����B" );
        return false;
    }

    return true;

}


////////////////////////////////////
// �`��
////////////////////////////////////
void Font::draw( const wchar_t* String, const Vector2& Position, XMVECTOR Clors )
{
    font_->DrawString( Sprite::getSprite(), // �`��ɕK�v
        String,              // �`�悷�镶����
        Position,            // �`�悷��ꏊ
        Clors );             // �`��F
}


////////////////////////////////////
// �j��
////////////////////////////////////
void Font::destroy()
{
    // �m�ۂ����������̉��
    SAFE_DELETE_ARRAY( font_ );
}
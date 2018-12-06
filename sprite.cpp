////////////////////////////////////
// Include
////////////////////////////////////
#include "sprite.h"
#include "direct3d.h"
#include "common.h"

////////////////////////////////////
// �����o�ϐ��̎��̂�錾
////////////////////////////////////
SpriteBatch* Sprite::sprite_;

////////////////////////////////////
// ������
////////////////////////////////////
bool Sprite::init()
{
    // SpriteBatch�N���X�̃��������m��(new���Z�q�Ŋm��)
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    // �������m�ۃ`�F�b�N
    if( !sprite_ )
    {
        // �G���[
        return false;
    }

    return true;
}

////////////////////////////////////
// �`��J�n�֐�
////////////////////////////////////
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getCommon()->NonPremultiplied() );
    // sprite�̑O��֌W�̐ݒ�@// ���̏ꍇ�͌ォ�痈�����̂���
}

////////////////////////////////////
// �`��֐�
////////////////////////////////////
void Sprite::draw(
    ID3D11ShaderResourceView* Texture, const Vector2& Position, const RECT* Rect,
    const float Rotation, const Vector2& Scale, const Vector2& Origin,
    const SpriteEffects Effect, const float Depth )
{
    sprite_->Draw(
        Texture,                // �e�N�X�`��
        Position,               // ���W
        Rect,                   // �`��͈�
        Colors::White,          // �J���[
        Rotation,               // ��]�l
        Origin,                 // �A���J�[�|�C���g(���_)
        Scale,                  // �g�k
        Effect,                 // �G�t�F�N�g
        Depth                   // �[�x�l
    );
}
////////////////////////////////////
// Include
////////////////////////////////////
#include "common.h"
#include "direct3d.h"

////////////////////////////////////
// �����o�ϐ��̎��̂�錾
// ::��������Q�Ƃ��Ă�����
CommonStates* Common::state_;
////////////////////////////////////

////////////////////////////////////
// ������
////////////////////////////////////
bool Common::init()
{
    // CommonStates�N���X�̃������̊m��
    state_ = new CommonStates( Direct3D::getDevice() );

    // �������m�ۃ`�F�b�N
    if( !state_ )
    {
        // �G���[
        return false;
    }
    return true;
}
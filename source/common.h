#pragma once
////////////////////////////////////
// include
////////////////////////////////////
#include <CommonStates.h>
#include "release.h"

////////////////////////////////////
// ���O���
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Common
{
private:
    static CommonStates* state_;        // CommonStates�N���X�|�C���^

public:
    static bool init();                     // ������
    static void destroy() { SAFE_DELETE_ARRAY( state_ ); }// �j��

    // �C���^�[�t�F�C�X�̎擾
    // CommonState�|�C���^��Ԃ�
    static CommonStates* getCommon() { return state_; }
};

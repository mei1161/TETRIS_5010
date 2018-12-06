#pragma once
////////////////////////////////////
// include
////////////////////////////////////
#include <d3d11.h>
#include <Keyboard.h>
#include "release.h"


////////////////////////////////////
// ���O���
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Key
{
private:
    static Keyboard* key_;                   // Keyclass�|�C���^
    static Keyboard::State state_;

public:
    static bool init();                      // ������
    static void update();                    // �X�V
    static void destroy() { SAFE_DELETE_ARRAY( key_ ); }   // �j��

    // �C���^�[�t�F�C�X�̎擾
    // Keyboard �̃|�C���^��Ԃ�
    static Keyboard::State& getKeyState() { return state_; }
};
#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <GamePad.h>


////////////////////////////////////
// ���O���
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Pad
{
private:
    static GamePad pad_;            // �Q�[���p�b�h�N���X
    static GamePad::State state_;   // ���͊i�[�\����

public:
    static void update();           // �X�V����

    // ���͍\���̂�Ԃ�
    static const GamePad::State& getState() { return state_; }

};
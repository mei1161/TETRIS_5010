#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <Windows.h>

////////////////////////////////////
// class
////////////////////////////////////
class Error
{
public:
    static void showDialog( const char* Message )   // �G���[���b�Z�[�W
    {
        MessageBox(
            NULL,
            Message,                // �\��������������
            "Error",                // �^�C�g��
            MB_OK | MB_ICONERROR ); // �{�b�N�X�̃f�U�C��
    }
};
#pragma once
#include"keyboard.h"
#include <cstdio>
#include "direct3d.h"
#include "sprite.h"
#include "texture.h"
#include"font.h"
#include "keyboard.h"
#include "pad.h"
#include "error.h"
#include "release.h"
#include"pad.h"
class Button
{
private:
    ID3D11ShaderResourceView* texture_;//�e�N�X�`��
    int pattern;//�\���L�[�p�^�[��
    int Bpattern;//�{�^���p�^�[��
    Vector2 position;
    int sizetop;
    int sizeleft;//�摜��
    bool abutton;//A�{�^��
    Vector2 Aposition;//A�{�^�����W
    int Asize;//A�{�^���T�C�Y
    bool bbutton;//B�{�^��
    Vector2 Bposition;//B�{�^�����W
    int Bsize;
    bool lbbutton;//LB�{�^��
    int LBsize;
    Vector2 LBposition;
    bool pausebutton;//�|�[�Y�{�^��
    int pausesize;
    Vector2 Pposition;
public:
    Button();//�R���X�g���N�^
    bool init();//������
    void update();//�X�V
    void draw();//�`��
    void range();//�`��͈�
    void destroy();//�j��


};
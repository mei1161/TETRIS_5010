#pragma once
#include"sprite.h"
#include"texture.h"
#include"pad.h"
#include"block.h"

using namespace DirectX;
using namespace SimpleMath;



class Score
{
private:

public:
    bool init();//������
    void update();//�X�V�i���邩�킩��Ȃ��j
    void calculate();//�`����W�̌v�Z
    void draw();//�`��
    void destroy();//�j��
};
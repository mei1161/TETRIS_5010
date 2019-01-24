#pragma once
#include"sprite.h"
#include"texture.h"
#include"block.h"
#include"release.h"
using namespace DirectX;
using namespace SimpleMath;



class Score
{
private:
    ID3D11ShaderResourceView* texture_;
    Vector2 position1;//RECT�v�Z�̂��߂̍��W
    Vector2 position2;
    Vector2 position3;
    Vector2 position4;
    Vector2 position5;
    Vector2 position6;
    int score;//�X�R�A
public:
    Score();
    bool init();//������
    void update();//�X�V�i���邩�킩��Ȃ��j
    void calculate();//�`����W�̌v�Z
    void draw();//�`��
    void destroy();//�j��
};
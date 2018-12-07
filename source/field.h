#pragma once
#include <cstdio>
#include "direct3d.h"
#include "sprite.h"
#include "texture.h"
#include"font.h"
#include "keyboard.h"
#include "pad.h"
#include "error.h"
#include "release.h"


class Field
{
private:
    ID3D11ShaderResourceView* texture_;//�e�N�X�`��
    int width_;//����
    int height_;//�c��
public:
    Field();//�R���X�g���N�^
    bool init();    //������
    void draw();    //�`��
    void destroy(); //�j��
};
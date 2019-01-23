#pragma once
#include <d3d11.h>
#include "release.h"
#include"texture.h"
#include"position.cpp"
#include "pad.h"
#include"keyboard.h"

////////////////////////////////////
// class
////////////////////////////////////
class Title
{
private:
	ID3D11ShaderResourceView* texture_;     // �e�N�X�`��
    int count;
    Vector2 position8;
    Keyboard::KeyboardStateTracker tracker;
    GamePad::ButtonStateTracker Btracker;
public:
	Title() :texture_(NULL) {}              // �R���X�g���N�^
	bool init();                            // ������
	bool update();                          // �X�V
	void draw();                            // �`��
    void move();                            //�ړ�
	void destroy();                         // �j��
};
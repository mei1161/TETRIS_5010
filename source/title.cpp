/*#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "pad.h"
#include"keyboard.h"

////////////////////////////////////
// ������
////////////////////////////////////
bool Title::init()
{
	// �e�N�X�`���̓ǂݍ���
	if (!(texture_ = Texture::load(L"Texture/Tetris10_Title.png")))
	{
		// �G���[
		return false;
	}



	return true;
}


////////////////////////////////////
// !!�X�V
////////////////////////////////////
bool Title::update()
{
	// �R���g���[���̓��͏����擾
	GamePad::State pad = Pad::getState();
	Keyboard::State
	

	return true;
}

////////////////////////////////////
// �`��
////////////////////////////////////
void Title::draw()
{
	Sprite::draw(texture_, Vector2::Zero);
}


////////////////////////////////////
// �j��
////////////////////////////////////
void Title::destroy()
{
	// �e�N�X�`���̉��
	SAFE_RELEASE(texture_);
}*/
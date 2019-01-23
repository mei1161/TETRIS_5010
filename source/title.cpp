#include "title.h"
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

    count = 0;

	return true;
}


////////////////////////////////////
// !!�X�V
////////////////////////////////////
bool Title::update()
{
	// �R���g���[���̓��͏����擾
	GamePad::State pad = Pad::getState();
    Keyboard::State key = Key::getKeyState();
    tracker.Update( key );
    Btracker.Update( pad );
    if( key.A || pad.buttons.a )
    {
        return false;
    }
    if(tracker.pressed.Down||Btracker.dpadDown==GamePad::ButtonStateTracker::PRESSED)
    {
        count++;
    }
    if( tracker.pressed.Up|| Btracker.dpadUp == GamePad::ButtonStateTracker::PRESSED )
    {
        count--;
    }

	return true;
}

////////////////////////////////////
// �`��
////////////////////////////////////
void Title::draw()
{
	Sprite::draw(texture_, Vector2::Zero);

    RECT rect;
    rect.top = 947L;
    rect.left =1201L;
    rect.bottom = rect.top + 35L;
    rect.right = rect.left + 264L;
   
    move();

    Sprite::draw( texture_, position8, &rect );

}
//�ړ����W
void Title::move()
{
    position8.x = 504L;
   
    //���X�g
    switch( count % 6 )
    {
    case 0: position8.y = 322L; break;
    case 1:position8.y = 364L; break;
    case 2:position8.y = 406L; break;
    case 3:position8.y = 448L; break;
    case 4:position8.y = 490L; break;
    case 5:position8.y = 532L; break;
    }
}

////////////////////////////////////
// �j��
////////////////////////////////////
void Title::destroy()
{
	// �e�N�X�`���̉��
	SAFE_RELEASE(texture_);
}
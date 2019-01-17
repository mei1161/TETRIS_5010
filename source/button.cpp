#include"button.h"
#include"release.h"



//�萔
const int Arrowsize = 227;//���L�[1�̃T�C�Y
const int Buttonsize = 128;//A,B,LB�{�^���̃T�C�Y


//�񋓑�
enum
{
    None,
    Up,
    RightUp,
    Right,
    RightDown,
    Down,
    LeftDown,
    Left,
    LeftUp
};

//�R���X�g���N�^
Button::Button()
{
    position.x = 47;
    position.y = 424;
    sizeleft = 0;
    Aposition.x = 1003;
    Aposition.y = 520;
    Asize = 0;
    Bposition.x = 1100;
    Bposition.y = 321;
    Bsize = 0;
    LBposition.x = 39;
    LBposition.y = 231;
    Pposition.x = 1062;
    Pposition.y = 82;
    pausesize = 0;
}


//������
bool Button::init()
{
    //�e�N�X�`���ǂݍ���
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // �G���[
        Error::showDialog( "Tetris11_SingleT.png���J���܂���ł���" );
        return false;
    }
    return true;

}

//�X�V
void Button::update()
{
    Keyboard::State key = Key::getKeyState();//�i�[��
    GamePad::State pad = Pad::getState();

    //�\���L�[
    if( (key.Up&&key.Left) || (pad.dpad.up&&pad.dpad.left) )
    {
        pattern = LeftUp;

    }
    else if( (key.Up&&key.Right) || (pad.dpad.up&&pad.dpad.right) )
    {
        pattern = RightUp;
    }
    else if( (key.Down&&key.Right) || (pad.dpad.down&&pad.dpad.right) )
    {
        pattern = RightDown;
    }
    else if( (key.Down&&key.Left) || (pad.dpad.down&&pad.dpad.left) )
    {
        pattern = LeftDown;
    }
    else if( key.Right || pad.dpad.right )
    {
        pattern = Right;
    }
    else if( key.Left || pad.dpad.left )
    {
        pattern = Left;
    }
    else if( key.Down || pad.dpad.down )
    {
        pattern = Down;
    }
    else if( key.Up || pad.dpad.up )
    {
        pattern = Up;
    }
    else
        pattern = None;


    //A�{�^��
    if( pad.buttons.a || key.A )
    {
        abutton = true;
    }
    else
        abutton = false;
    //B�{�^��
    if( pad.buttons.b || key.Z )
    {
        bbutton = true;
    }
    else
        bbutton = false;
    //LB�{�^��
    if( pad.buttons.leftShoulder || key.Enter )
    {
        lbbutton = true;
    }
    else lbbutton = false;
    //PAUSE�{�^��
    if( pad.buttons.menu || key.Space )
    {
        pausebutton = true;
    }
    else pausebutton = false;


}
//�`��͈͐ݒ�
void Button::range()
{
    //���L�[
    switch( pattern )
    {
    case None:sizeleft = Arrowsize * None; break;
    case Up:sizeleft = Arrowsize * Up; break;
    case RightUp:sizeleft = Arrowsize * RightUp; break;
    case RightDown:sizeleft = Arrowsize * RightDown; break;
    case Right:sizeleft = Arrowsize * Right; break;
    case Left:sizeleft = Arrowsize * Left; break;
    case LeftUp:sizeleft = Arrowsize * LeftUp; break;
    case LeftDown:sizeleft = Arrowsize * LeftDown; break;
    case Down:sizeleft = Arrowsize * Down; break;

    }

    //A�{�^��
    if( !abutton )
    {
        Asize = 0;
    }
    else Asize = Buttonsize;
    //B�{�^��
    if( !bbutton )
    {
        Bsize = 0;
    }
    else Bsize = Buttonsize;
    //LB�{�^��
    if( !lbbutton )
    {
        LBsize = 0;
    }
    else LBsize = Buttonsize;
    //�|�[�Y�{�^��
    if( !pausebutton )
    {
        pausesize = 0;
    }
    else pausesize = 64;
}

//�`��
void Button::draw()
{

    //�\���L�[�`��
    range();
    RECT rect;
    rect.top = 720;
    rect.left = sizeleft;
    rect.right = sizeleft + Arrowsize;
    rect.bottom = rect.top + Arrowsize;

    Sprite::draw( texture_, position, &rect );

    //A�{�^���`��
    RECT Arect;
    Arect.top = 464 + Asize;
    Arect.left = 1536;
    Arect.right = Arect.left + Buttonsize;
    Arect.bottom = Arect.top + Buttonsize;

    Sprite::draw( texture_, Aposition, &Arect );

    RECT Brect;
    Brect.top = 464 + Bsize;
    Brect.left = 1664;
    Brect.right = Brect.left + Buttonsize;
    Brect.bottom = Brect.top + Buttonsize;
    Sprite::draw( texture_, Bposition, &Brect );


    RECT LBrect;
    LBrect.top = 464 + LBsize;
    LBrect.left = 1280;
    LBrect.right = LBrect.left + Buttonsize;
    LBrect.bottom = LBrect.top + Buttonsize;
    Sprite::draw( texture_, LBposition, &LBrect );
    RECT Prect;
    Prect.top = 336 + pausesize;
    Prect.left = 1920;
    Prect.right = Prect.left + 128;
    Prect.bottom = Prect.top + 64;
    Sprite::draw( texture_, Pposition, &Prect );
}




//�j��
void Button::destroy()
{
    SAFE_RELEASE( texture_ );
}
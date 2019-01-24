#include"score.h"

using namespace DirectX;
using namespace SimpleMath;

Score::Score()
{
    texture_ = NULL;
}
//èâä˙âª
bool Score::init()
{
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // ÉGÉâÅ[
        return false;
    }
    score = 0;
    return true;
}
void Score::update()
{

}
//ï`âÊîÕàÕåvéZ
void Score::calculate()
{
   

    
    position1.y = 961;

    switch( score % 10 )
    {
    case 0:position1.x = 0; break;
    case 1:position1.x = 16; break;
    case 2:position1.x = 32; break;
    case 3:position1.x = 48; break;
    case 4:position1.x = 64; break;
    case 5:position1.x = 80; break;
    case 6:position1.x = 96; break;
    case 7:position1.x = 112; break;
    case 8:position1.x = 128; break;
    case 9:position1.x = 144; break;
    }
    position2.y = 961;

    switch( score % 100 )
    {
    case 0:position2.x = 0; break;
    case 1:position2.x = 16; break;
    case 2:position2.x = 32; break;
    case 3:position2.x = 48; break;
    case 4:position2.x = 64; break;
    case 5:position2.x = 80; break;
    case 6:position2.x = 96; break;
    case 7:position2.x = 112; break;
    case 8:position2.x = 128; break;
    case 9:position2.x = 144; break;
    }
    position3.y = 961;

    switch( score % 1000 )
    {
    case 0:position3.x = 0L; break;
    case 1:position3.x = 16; break;
    case 2:position3.x = 32; break;
    case 3:position3.x = 48; break;
    case 4:position3.x = 64; break;
    case 5:position3.x = 80; break;
    case 6:position3.x = 96; break;
    case 7:position3.x = 112; break;
    case 8:position3.x = 128; break;
    case 9:position3.x = 144; break;
    }

    position4.y = 961;
    switch( score % 10000 )
    {
    case 0:position4.x = 0; break;
    case 1:position4.x = 16; break;
    case 2:position4.x = 32; break;
    case 3:position4.x = 48; break;
    case 4:position4.x = 64; break;
    case 5:position4.x = 80; break;
    case 6:position4.x = 96; break;
    case 7:position4.x = 112; break;
    case 8:position4.x = 128; break;
    case 9:position4.x = 144; break;
    }

    position5.y = 961;
    switch( score % 10000 )
    {
    case 0:position5.x = 0; break;
    case 1:position5.x = 16; break;
    case 2:position5.x = 32; break;
    case 3:position5.x = 48; break;
    case 4:position5.x = 64; break;
    case 5:position5.x = 80; break;
    case 6:position5.x = 96; break;
    case 7:position5.x = 112; break;
    case 8:position5.x = 128; break;
    case 9:position5.x = 144; break;
    }
    position6.y = 961;
    switch( score % 1000 )
    {
    case 0:position6.x = 0; break;
    case 1:position6.x = 16; break;
    case 2:position6.x = 32; break;
    case 3:position6.x = 48; break;
    case 4:position6.x = 64; break;
    case 5:position6.x = 80; break;
    case 6:position6.x = 96; break;
    case 7:position6.x = 112; break;
    case 8:position6.x = 128; break;
    case 9:position6.x = 144; break;
    }

}
void Score::draw()
{
    
    calculate();//êÿÇËéÊÇÈîÕàÕÇåvéZ

    Vector2 digit1;//ï`âÊç¿ïW
    digit1.x = 643L;
    digit1.y = 42L;

    RECT rect1;//1ÇÃà 
    rect1.top = position1.y;
    rect1.left = position1.x;
    rect1.bottom = rect1.top + 21L;
    rect1.right = rect1.left+ 16L;
    Sprite::draw( texture_, digit1, &rect1 );
   
    Vector2 digit2;//ï`âÊç¿ïW
    digit2.x = 626L;
    digit2.y = 42L;

    RECT rect2;//1ÇÃà 
    rect2.top = position2.y;
    rect2.left = position2.x;
    rect2.bottom = rect2.top + 21L;
    rect2.right = rect2.left + 16L;
    Sprite::draw( texture_, digit2, &rect2 );

    Vector2 digit3;//ï`âÊç¿ïW
    digit3.x = 609L;
    digit3.y = 42L;


    RECT rect3;
    rect3.top = position3.y;
    rect3.left = position3.x;
    rect3.bottom = rect3.top + 21L;
    rect3.right = rect3.left + 16L;
    Sprite::draw( texture_, digit3, &rect3 );

    Vector2 digit4;//ï`âÊç¿ïW
    digit4.x = 592L;
    digit4.y = 42L;


    RECT rect4;
    rect4.top = position4.y;
    rect4.left = position4.x;
    rect4.bottom = rect4.top + 21L;
    rect4.right = rect4.left + 16L;
    Sprite::draw( texture_, digit4, &rect4 );

    Vector2 digit5;//ï`âÊç¿ïW
    digit5.x = 575L;
    digit5.y = 42L;


    RECT rect5;
    rect5.top = position5.y;
    rect5.left = position5.x;
    rect5.bottom = rect5.top + 21L;
    rect5.right = rect5.left + 16L;
    Sprite::draw( texture_, digit5, &rect5 );

    Vector2 digit6;//ï`âÊç¿ïW
    digit6.x = 558L;
    digit6.y = 42L;


    RECT rect6;
    rect6.top = position6.y;
    rect6.left = position6.x;
    rect6.bottom = rect6.top + 21L;
    rect6.right = rect6.left + 16L;
    Sprite::draw( texture_, digit6, &rect6 );
}
void Score::destroy()
{
    SAFE_RELEASE( texture_ );
}

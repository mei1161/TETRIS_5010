#include"texture.h"
#include"sprite.h"
#include"d3d11.h"


static Vector2 texture_position( int num )
{
    Vector2 position;
    switch( num % 5 )
    {
    case 0:position.x = 504L;
        position.y = 322L;
    }
    return position;
}
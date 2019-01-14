#include"color.h"


static Vector2 get_textureUV_from(int color)
{
	Vector2 position;
	position.x = 956L;
	switch (color) {
	case Lightblue: position.y = 688L; break;
	case Orange: position.y = 713L; break;
	case Green: position.y = 738L; break;
	case Pink: position.y = 763L; break;
	case Blue:position.y = 788L; break;
	case Brown:position.y= 813L; break;
	case Violet:position.y = 838L; break;

	}
	return position;
}
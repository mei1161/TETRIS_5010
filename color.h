#pragma once
#include <d3d11.h>
#include<SimpleMath.h>
using namespace DirectX;
using namespace SimpleMath;
enum Color
{
	Lightblue,
	Orange,
	Green,
	Pink,
	Blue,
	Brown,
	Violet
};


static Vector2 get_textureUV_from(int color);


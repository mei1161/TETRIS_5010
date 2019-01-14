#include"block.h"
#include"color.h"
#include"color.cpp"
enum keyboard
{
    Left,
    Right,
    Up,
    Down,
    None,
};


//�R���X�g���N�^
Block::Block()
{
    texture_ = NULL;
    position_.y =173L;//�u���b�N���W
    position_.x =511L;
	count = 0;
	exist_fallingblock = false;
}

//������
bool Block::init()
{
    // �e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // �G���[
        return false;
    }
	int i, j, k;
	for(i=0;i<4;i++)
		for (j = 0; j < 4; j++)
		{
			falling_block[i][j].index[0] =-1000;
			falling_block[i][j].index[1] = -1000;
			falling_block[i][j].color = -1000;
			falling_block[i][j].is_wall = false;
		}
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++)
		{
			field[i][j].color =-1;//�F��񏉊���
			for (k = 0; k < 2; k++) 
			{
				field[i][j].index[k] = 99;
			}
			if (i == 21 || j == 0 || j == 11)//��
			{
				field[i][j].is_wall = true;
				field[i][j].index[0] = j;//���E�����蔻��ԍ�
				field[i][j].index[1] = i;//�������蔻��z��ԍ�
				field[i][j].color = Orange;
			}
			else//�ǈȊO
			{
				field[i][j].is_wall = false;
			}
		

		}
	}

    return true;
    
}
//�X�V����
void Block::update()
{
	Keyboard::State key = Key::getKeyState();
	GamePad::State pad = Pad::getState();
	int i, j;
	if (exist_fallingblock == false) {
		falling_block[0][0].index[0] = 1;
		falling_block[0][0].index[1] = 0;
		falling_block[0][0].color = Lightblue;
		exist_fallingblock = true;
	}

	count++;
	//��������
	if (count % 60 == 0)
	{
		
		for (i = 0; i < 4; i++) 
			for (j = 0; j < 4; j++) 
			{
				falling_block[i][j].index[1]++;//�z��ԍ�(y���W)�~��
			}
	}
	
}

//�`��
void Block::draw()
{

	int i, j;
	//�Ǖ`��
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			Vector2 texture_UV = get_textureUV_from(field[i][j].color);
			RECT rect;
			rect.top = texture_UV.x;
			rect.left = texture_UV.y;
			rect.right = rect.left + 25L;
			rect.bottom = rect.top + 25L;

			position_.x = (field[i][j].index[0] * 25) + 487;
			position_.y = (field[i][j].index[1] * 25) + 173;

			Sprite::draw(texture_, position_, &rect);
		}
	}

	RECT Arect;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			Vector2 texture_UV = get_textureUV_from(falling_block[i][j].color);
			Arect.top = texture_UV.x;
			Arect.left = texture_UV.y;
			Arect.right = Arect.left + 25L;
			Arect.bottom = Arect.top + 25L;

			position2.x = (falling_block[i][j].index[0] * 25) + 487;
			position2.y = (falling_block[i][j].index[1] * 25) + 173;
			
			Sprite::draw(texture_, position2, &Arect);
		}

		
}


//������邩�ǂ���
bool Block::can_fall()
{
	return true;
}
//�j��
void Block::destroy()
{
    SAFE_RELEASE( texture_ );
}
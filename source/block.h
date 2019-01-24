#pragma once

#include"sprite.h"
#include"keyboard.h"
#include"texture.h"
#include"pad.h"
#include"stdlib.h"


//���O���
using namespace DirectX;
using namespace SimpleMath;

//�\����
typedef struct
{
	int index[2];//�z��ԍ�//0��X���W�E�Ej�A�P��Y���W�E�Ei
	int color;//�F���
	bool is_empty;//�󂩂ǂ���
}block;

class Block
{
private:
    
	ID3D11ShaderResourceView* texture_;//�e�N�X�`��
	int key_state;//���̃L�[�������������i�[
	int count;
	block falling_block[4][4];//�������Ă���u���b�N
	block field[22][12];//�Œ�t�B�[���h
	Vector2 position2; //�����Ă�u���b�N�`����W
	Vector2 position_;//�Œ�u���b�N�`����W
	bool exist_fallingblock;//�u���b�N�����p�t���O
	int old_color;//1�O�ɕ\����������
	int old_form;//1�O�ɕ\�������`
	Keyboard::KeyboardStateTracker tracker;
	GamePad::ButtonStateTracker Btracker;
	block next_block[3][4][2];//�l�N�X�g�u���b�N��3���̕\��
	Vector2 position3;//�l�N�X�g�u���b�N�`����W
	Vector2 position4;
	Vector2 position5;
	int next[6];//�l�N�X�g�̔z��
	bool r_flag;//�����_���t���O
    int score;//�X�R�A
public:
	Block();   //�R���X�g���N�^
	bool init();    //������
	void update();  //�X�V
	void draw();    //�`��    
	void destroy(); //�j��
	bool can_move(int direction);//������邩�ǂ���
	void Copy_fallingblock_in_field();//fallingblock���t�B�[���h�ɃR�s�[����
	void Delete_fieldblock(int num);//�t�B�[���h�̂�������u���b�N����������
	bool move_down();//���̏ꍇ�̏���(�����������܂ށj
	void Drop_fieldblock(int no);//�u���b�N����������ɁA�c���Ă���u���b�N�����ɗ��Ƃ�����
	void Make_fallingblock();//������u���b�N�����
	void init_fallingblock();//������u���b�N�̏�����
	void  Game_over();//�Q�[���I�[�o�[
	bool init_field();//�ǈȊO�̏�����
	bool Rotate(int pattern, int form);//��]����
	bool can_rotate(block copy[4][4]);//���݂̍��W�ŉ�]�ł���̂�
	void Create_next_block();//�l�N�X�g�u���b�N�̐���
	void init_next_block();//�l�N�X�g�u���b�N�̏�����
	void move_up();//�Y�������J��グ��
	void init_next();//�l�N�X�g�̏�����

    int get_score() { return score; };//�X�R�A��Ԃ�
};

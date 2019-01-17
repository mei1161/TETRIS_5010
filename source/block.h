#include"sprite.h"
#include"keyboard.h"
#include"texture.h"
#include"pad.h"

//���O���
using namespace DirectX;
using namespace SimpleMath;

//�\����
typedef struct
{
    int index[ 2 ];//�z��ԍ�//0��X���W�E�Ej�A�P��Y���W�E�Ei
    int color;//�F���
    bool is_wall;//�ǂ��ǂ���
}block;

class Block
{
private:

    ID3D11ShaderResourceView* texture_;//�e�N�X�`��

    int key_state;//���̃L�[�������������i�[
    int count;
    block falling_block[ 4 ][ 4 ];//�������Ă���u���b�N
    block field[ 22 ][ 12 ];//�Œ�t�B�[���h
    Vector2 position2; //�����Ă�u���b�N�`����W
    Vector2 position_;//�Œ�u���b�N�`����W
    bool exist_fallingblock;//�u���b�N�����p�t���O
   

public:
    Block();   //�R���X�g���N�^
    bool init();    //������
    void update();  //�X�V
    void draw();    //�`��    
    void destroy(); //�j��
    bool can_move( int direction );//������邩�ǂ���
    void Copy_fallingblock_in_field();//fallingblock���t�B�[���h�ɃR�s�[����
    void Delete_fieldblock( int num );//�t�B�[���h�̂�������u���b�N����������
    void move_down();//���̏ꍇ�̏���(�����������܂ށj
    void Drop_fieldblock( int no );//�u���b�N����������ɁA�c���Ă���u���b�N�����ɗ��Ƃ�����
    void Make_fallingblock();//������u���b�N�����
    void init_fallingblock();//������u���b�N�̏�����
    void  Game_over();//�Q�[���I�[�o�[
    bool init_field();
};
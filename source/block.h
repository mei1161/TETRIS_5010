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
	int index[2];//�z��ԍ�
	int color;//�F���
	bool is_wall;//�ǂ��ǂ���
}block;

class Block
{
private:

    ID3D11ShaderResourceView* texture_;//�e�N�X�`��
    Vector2 position_;//�u���b�N�`����W
    int key_state;//���̃L�[�������������i�[
	int count;
	block falling_block[4][4];//�������Ă���u���b�N
    block field[ 22 ][ 12 ];//�Œ�t�B�[���h
    Vector2 position2;
    Vector2 sposition_;//�����|�W�V����
    Vector2 Aposition_;
	bool exist_fallingblock;
    
public:
    Block();   //�R���X�g���N�^
    bool init();    //������
    void update();  //�X�V
    void draw();    //�`��    
    void destroy(); //�j��
	bool can_fall();//������邩�ǂ���
	


};
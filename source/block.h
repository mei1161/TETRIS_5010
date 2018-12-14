#include"sprite.h"
#include"keyboard.h"
#include"texture.h"
#include"pad.h"
//���O���
using namespace DirectX;
using namespace SimpleMath;


class Block
{
private:

    ID3D11ShaderResourceView* texture_;//�e�N�X�`��
    Vector2 position_;//�u���b�N�`����W
    float plus;         //�ړ���
    bool move_;//�����邩�ǂ���������t���O
    int key_state;//���̃L�[�������������i�[
    int Animation_counter;//�A�j���[�V�����J�E���^
    int kAnimationSpeed;
    int count;
    int block[ 22 ][ 12 ];
    bool flag;
    Vector2 position2;
    bool r_flag;//���Z�b�g�t���O
    Vector2 sposition_;//�����|�W�V����
    Vector2 Aposition_;
    int i;
    int j;//�|�W�V��������z��ԍ������߂鎞�̊i�[�ϐ�
    int cdelete;
public:
    Block();   //�R���X�g���N�^
    bool init();    //������
    void update();  //�X�V
    void draw();    //�`��    
    void destroy(); //�j��
    void Animation();//�A�j���[�V��������
    void Collusion();//�����蔻��
    void Storing();//�z��Ɋi�[
    void Delete();//����
    void Load();//�ς�
};
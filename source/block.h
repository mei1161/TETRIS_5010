#include"sprite.h"
#include"keyboard.h"
#include"texture.h"
#include"pad.h"
//名前空間
using namespace DirectX;
using namespace SimpleMath;


class Block
{
private:

    ID3D11ShaderResourceView* texture_;//テクスチャ
    Vector2 position_;//ブロック描画座標
    float plus;         //移動量
    bool move_;//動けるかどうかを見るフラグ
    int key_state;//何のキーを押したかを格納
    int Animation_counter;//アニメーションカウンタ
    int kAnimationSpeed;
    int count;
    int block[ 22 ][ 12 ];
    bool flag;
    Vector2 position2;
    bool r_flag;//リセットフラグ
    Vector2 sposition_;//初期ポジション
    Vector2 Aposition_;
    int i;
    int j;//ポジションから配列番号を求める時の格納変数
    int cdelete;
public:
    Block();   //コンストラクタ
    bool init();    //初期化
    void update();  //更新
    void draw();    //描画    
    void destroy(); //破棄
    void Animation();//アニメーション処理
    void Collusion();//当たり判定
    void Storing();//配列に格納
    void Delete();//消す
    void Load();//積む
};
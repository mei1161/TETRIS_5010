#include"sprite.h"
#include"keyboard.h"
#include"texture.h"

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
public:
    Block();   //コンストラクタ
    bool init();    //初期化
    void update();  //更新
    void draw();    //描画    
    void destroy(); //破棄



};
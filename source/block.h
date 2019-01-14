#include"sprite.h"
#include"keyboard.h"
#include"texture.h"
#include"pad.h"
//名前空間
using namespace DirectX;
using namespace SimpleMath;

//構造体
typedef struct
{
	int index[2];//配列番号
	int color;//色情報
	bool is_wall;//壁かどうか
}block;

class Block
{
private:

    ID3D11ShaderResourceView* texture_;//テクスチャ
    Vector2 position_;//ブロック描画座標
    int key_state;//何のキーを押したかを格納
	int count;
	block falling_block[4][4];//今落ちているブロック
    block field[ 22 ][ 12 ];//固定フィールド
    Vector2 position2;
    Vector2 sposition_;//初期ポジション
    Vector2 Aposition_;
	bool exist_fallingblock;
    
public:
    Block();   //コンストラクタ
    bool init();    //初期化
    void update();  //更新
    void draw();    //描画    
    void destroy(); //破棄
	bool can_fall();//落ちれるかどうか
	


};
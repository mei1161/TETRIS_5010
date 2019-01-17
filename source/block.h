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
    int index[ 2 ];//配列番号//0がX座標・・j、１がY座標・・i
    int color;//色情報
    bool is_wall;//壁かどうか
}block;

class Block
{
private:

    ID3D11ShaderResourceView* texture_;//テクスチャ

    int key_state;//何のキーを押したかを格納
    int count;
    block falling_block[ 4 ][ 4 ];//今落ちているブロック
    block field[ 22 ][ 12 ];//固定フィールド
    Vector2 position2; //動いてるブロック描画座標
    Vector2 position_;//固定ブロック描画座標
    bool exist_fallingblock;//ブロック生成用フラグ
   

public:
    Block();   //コンストラクタ
    bool init();    //初期化
    void update();  //更新
    void draw();    //描画    
    void destroy(); //破棄
    bool can_move( int direction );//落ちれるかどうか
    void Copy_fallingblock_in_field();//fallingblockをフィールドにコピーする
    void Delete_fieldblock( int num );//フィールドのそろったブロックを消す処理
    void move_down();//下の場合の処理(自動落下も含む）
    void Drop_fieldblock( int no );//ブロックが消えた後に、残っているブロックを下に落とす処理
    void Make_fallingblock();//落ちるブロックを作る
    void init_fallingblock();//落ちるブロックの初期化
    void  Game_over();//ゲームオーバー
    bool init_field();
};
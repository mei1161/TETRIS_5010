#include"field.h"

//名前空間
using namespace DirectX;
using namespace SimpleMath;


//コンストラクタ
Field::Field()
{
    texture_ = NULL;
    width_ = 720;//横
    height_ = 1280;//縦
}


//初期化
bool Field::init()
{
    //テクスチャ読み込み
    if( !(texture_ = Texture::load( L"Texture/Tetris11_SingleT.png" )) )
    {
        // エラー
        Error::showDialog( "Tetris11_SingleT.pngが開けませんでした" );
        return false;
    }
    int i;//ループカウンタ
    int j;
    for( i = 0; i < 22; i++ )
    {
        for( j = 0; j < 12; j++ )
        {
            if( i == 0 || i == 21 || j == 11 )
            {
                field[ i ][ j ] = 9;
            }
        }
    }



    return true;
}


//描画
void Field::draw()
{
    // 描画範囲の設定
    RECT rect;
    rect.top = 0L;//テクスチャ左端(y)
    rect.left = 0L;//テクスチャ左端(x)
    rect.right = height_;//テクスチャ右端(x)
    rect.bottom = width_;//テクスチャ右端(y)


    Sprite::draw( texture_, Vector2::Zero, &rect );//描画


}

//破棄
void Field::destroy()
{
    SAFE_RELEASE( texture_ );//テクスチャの破棄
   
}
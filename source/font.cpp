#include "font.h"

////////////////////////////////////
// 実体の宣言
////////////////////////////////////
SpriteFont* Font::font_;

////////////////////////////////////
// 初期化
////////////////////////////////////
bool Font::init()
{
    // スプライトフォントのメモリを確保
    font_ = new SpriteFont( Direct3D::getDevice(), L"font_cica.spritefont" );

    // メモリ確保チェック
    if( !font_ )
    {
        // エラー
        Error::showDialog( "スプライトフォントのメモリ確保に失敗しました。" );
        return false;
    }

    return true;

}


////////////////////////////////////
// 描画
////////////////////////////////////
void Font::draw( const wchar_t* String, const Vector2& Position, XMVECTOR Clors )
{
    font_->DrawString( Sprite::getSprite(), // 描画に必要
        String,              // 描画する文字列
        Position,            // 描画する場所
        Clors );             // 描画色
}


////////////////////////////////////
// 破棄
////////////////////////////////////
void Font::destroy()
{
    // 確保したメモリの解放
    SAFE_DELETE_ARRAY( font_ );
}
////////////////////////////////////
// Include
////////////////////////////////////
#include "adx.h"

////////////////////////////////////
// 実体の宣言
////////////////////////////////////
CriAtomExVoicePoolHn Adx::voice_pool_;
CriAtomExAcbHn       Adx::acb_;
CriAtomExPlayerHn    Adx::player_;


////////////////////////////////////
// プロトタイプ宣言
////////////////////////////////////
void* user_alloc_func( void* obj, CriUint32 size );
void  user_free_func( void* obj, void* ptr );


////////////////////////////////////
// 初期化
////////////////////////////////////
bool Adx::init( const CriChar8* acfFilePath )
{
    // エラーコールバック関数の登場
    criErr_SetCallback( userErrorCallback );

    // メモリアロケータ関数の登録
    criAtomEx_SetUserAllocator( user_alloc_func, user_free_func, NULL );

    // ライブラリの初期化
    criAtomEx_Initialize_WASAPI( NULL, NULL, 0 );

    // ストリーミング用バッファの作成
    CriAtomDbasId dbas = criAtomDbas_Create( NULL, NULL, 0 );

    // 全体設定ファイルの登録
    if( !criAtomEx_RegisterAcfFile( NULL, acfFilePath, NULL, 0 ) )
    {
        // エラー
        return false;
    }

    // DSPバス設定の登録
    criAtomEx_AttachDspBusSetting( "DspBusSetting_0", NULL, 0 );

    // ボイスプール構造体の作成
    CriAtomExStandardVoicePoolConfig vpconfig;

    // デフォルト値を設定
    criAtomExVoicePool_SetDefaultConfigForStandardVoicePool( &vpconfig );
    //音の許容数を増やす
    //vpconfig.num_voices = 15;

    // ストリーミング再生有効
    vpconfig.player_config.streaming_flag = CRI_TRUE;

    // ボイスプールの作成
    voice_pool_ = criAtomExVoicePool_AllocateStandardVoicePool( &vpconfig, NULL, 0 );

    // プレイヤーハンドルの作成
    player_ = criAtomExPlayer_Create( NULL, NULL, 0 );

    return true;
}


////////////////////////////////////
// 読み込み
////////////////////////////////////
bool Adx::load( const CriChar8* acbFilePath, CriChar8* awbFilePath )
{
    // acbファイルの読み込み
    acb_ = criAtomExAcb_LoadAcbFile( NULL, acbFilePath, NULL, awbFilePath, NULL, 0 );

    return true;
}


////////////////////////////////////
// 再生
////////////////////////////////////
void Adx::play( CriAtomExCueId id )
{
    // ACBハンドル
    criAtomExPlayer_SetCueId( player_, acb_, id );

    // キューの再生
    criAtomExPlayer_Start( player_ );
}


////////////////////////////////////
// 破棄a
////////////////////////////////////
void Adx::destroy()
{
    // 確保した逆の順番で解放a
    criAtomExPlayer_Destroy( player_ );
    criAtomExAcb_Release( acb_ );
    criAtomExVoicePool_Free( voice_pool_ );
    criAtomEx_UnregisterAcf();
    criAtomEx_Finalize_WASAPI();
}


////////////////////////////////////
// コールバック関数
////////////////////////////////////
void Adx::userErrorCallback( const CriChar8* ErrorId, CriUint32 P1, CriUint32 P2, CriUint32* pArray )
{
    const CriChar8* msg;
    msg = criErr_ConvertIdToMessage( ErrorId, P1, P2 ); // エラーした際文字列を作成してくれる
    OutputDebugString( msg );                           // デバック時にエラーが起きたら出力ウィンドウに文字列を表示

}


////////////////////////////////////
// メモリ確保関数の実装
////////////////////////////////////
void* user_alloc_func( void* obj, CriUint32 size )
{
    void* ptr = static_cast<void*>(new char[ size ]);
    return ptr;
}


////////////////////////////////////
// メモリ解放関数の実装
////////////////////////////////////
void user_free_func( void* obj, void* ptr )
{
    SAFE_DELETE_ARRAY( ptr );
}
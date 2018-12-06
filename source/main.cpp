////////////////////////////////////
// Include
////////////////////////////////////
#include <windows.h>
#include <d3d11.h>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <ctime>

#include "direct3d.h"
#include"game.h"
#include "sprite.h"
#include "common.h"
#include "pad.h"
#include "keyboard.h"
#include "title.h"
#include "result.h"
#include "adx.h"



////////////////////////////////////
// 名前空間
////////////////////////////////////
using namespace DirectX;
using namespace SimpleMath;


////////////////////////////////////
// 列挙体
////////////////////////////////////
// シーン追加(ed等)によってenumの中の変数を追加
enum
{
    kTitleInit,     // タイトル画面初期化
    kTitleUpdate,   // タイトル画面更新(描画)
    kTutorialInit,  // チュートリアル画面初期化
    kTutorialUpdate,// チュートリアル画面更新(描画)
    kGameInit,      // ゲーム画面初期化
    kGameUpdate,    // ゲーム画面更新(描画)
    kResultInit,    // リザルト画面初期化
    kResultUpdate,  // リザルト画面更新(描画)
};


////////////////////////////////////
// プロトタイプ宣言
////////////////////////////////////
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

////////////////////////////////////
// WINMAIN
////////////////////////////////////
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    // 乱数初期化(一度だけ呼び出す)
    srand( time( NULL ) );

    // ウィンドウクラスの作成
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );                               // 構造体サイズ
    wnd.style = CS_HREDRAW | CS_VREDRAW;                             // スタイル
    wnd.hInstance = hInstance;                                       // アプリケーションインストール
    wnd.lpszClassName = "ClassName";                                 // クラス名
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );                     // カーソル形状読み込み
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // ウィンドウカラー
    wnd.lpfnWndProc = WinProc;                                       // ウィンドウプロシージャへの関数ポインタ

    // 登録
    if( !RegisterClassEx( &wnd ) )
    {
        // エラー(上記の関数で0が返ってきたとき)
        return 0;
    }

    // ウィンドウサイズを決定
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );// ウィンドウのサイズの座標のズレを回避するための関数

    //ウィンドウの作成
    const HWND hWnd = CreateWindowEx(
        ex_style,               // 拡張ウィンドウスタイル
        "ClassName",            // クラス名
        "Title",                // ウィンドウタイトル
        style,                  // ウィンドウスタイル
        CW_USEDEFAULT,          // 表示座標Ｘ 
        CW_USEDEFAULT,          // 表示座標Ｙ
        rect.right - rect.left, // ウィンドウ横幅
        rect.bottom - rect.top, // ウィンドウ縦幅
        NULL,                   // 親メニューへのハンドル 
        NULL,                   // メニューハンドル
        hInstance,              // アプリケーションインスタンス
        NULL                    // ウィンドウ作成データ
    );

    // NULLチェック
    if( hWnd == NULL )
    {
        //エラー
        return 0;
    }

    // Direct3D初期化
    if( !Direct3D::init( hWnd ) )
    {
        // エラー
        return 0;
    }

    // COMライブラリの初期化
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // エラー
        return 0;
    }

    // SpriteBatchクラスの初期化
    if( !Sprite::init() )
    {
        // エラー
        return 0;
    }

    // CommonStatesクラスの初期化
    if( !Common::init() )
    {
        // エラー
        return 0;
    }

    /* // fieldクラス変数
     Field field;

     // プレイヤークラス
     Player player;*/



     // Keyboardクラスの初期化
    if( !Key::init() )
    {
        // エラー
        return 0;
    }

    /* // Fontクラスの初期化
     if( !Font::init() )
     {
         // エラー
         return 0;
     }*/

     // CRIADXの初期化
    /* if( !Adx::init( "FlowerGameBGM.acf" ) )
     {
         // エラー
         return 0;
     }*/

     // サウンドの読み込み
    // Adx::load( "CueSheet_0.acb", NULL );

     // ウィンドウの表示
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // メインループ
    MSG msg = { NULL };

    //時間計測
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();


    // 現在の作業番号
 //   int work_no = kTitleInit;

   /* // シーンクラス変数
    Title title;
    Tutorial tutorial;
    Result result;


    Game game;*/

    while( msg.message != WM_QUIT )
    {
        float x = static_cast<float>(0.1);

        // メッセージ処理　// DXlibでのProcessMessage()
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // フレームレート制御
            t1 = timeGetTime();     // 現在の時間
            dt = (t1 - t2) + t3;    // 前回の更新からの差分を計算

            // 約16ミリ秒経過していたら処理を行う
            // 10000/1ミリ秒/60fps=16.666...
            if( dt > 16 )
            {
                t2 = t1;            // 今の時間を前回の時間とする
                t3 = dt % 16;       // 誤差分を吸収   // 前の余り
                // ---------- 更新処理 ----------
                Pad::update();      // コントローラー更新
                Key::update();      // キーボード更新
           //     Adx::update();      // サウンド更新

                /////// !! 後で修正 !! /////////////
                // シーン処理
            /*    switch( work_no )
                {
                case kTitleInit:
                    // タイトルクラス初期化
                    if( !title.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }
                    // 次の処理へ
                    work_no = kTitleUpdate;
                    break;
                case kTitleUpdate:
                    // タイトルクラス更新処理
                    if( !title.update() )
                    {
                        // falseが返ってきたら次のシーンへ
                        title.destroy();
                        work_no = kTutorialInit;
                    }
                    break;
                case kTutorialInit:
                    //チュートリアルクラス初期化
                    if( !tutorial.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }
                    // 次の処理へ
                    work_no = kTutorialUpdate;
                    break;
                case kTutorialUpdate:
                    // チュートリアルクラス更新処理
                    if( !tutorial.update() )
                    {
                        // falseが返ってきたら次のシーンへ
                        tutorial.destroy();
                        work_no = kGameInit;
                    }
                    break;
                case kGameInit:
                    // ゲームクラス初期化
                    if( !game.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }
                    // 次の処理へ
                    work_no = kGameUpdate;
                    break;
                case kGameUpdate:
                    // falseが返ってきたら次のシーンへ
                    // ゲームクラス更新
                    if( !game.update() )
                    {
                        game.destroy();
                        work_no = kResultInit;
                    }
                    break;
                case kResultInit:
                    // リザルトクラス初期化
                    if( !result.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }
                    // 次の処理へ
                    work_no = kResultUpdate;
                    break;
                case kResultUpdate:
                    // リザルトクラス更新
                    if( !result.update( game.getScoreTrue() ) )
                    {
                        // falseが返ってきたら次のシーンへ
                        result.destroy();
                        work_no = kTitleInit;
                    }
                    break;
                }*/

                /////////////////////////////////////

                // ---------- 描画 ----------
                Direct3D::clear();  // 画面クリア
                Sprite::begin();    // スプライト描画開始

                ///////// !!　Title !! ///////////
             /*   switch( work_no )
                {
                case kTitleUpdate:
                    title.draw();
                    break;
                case kTutorialUpdate:
                    tutorial.draw();
                    break;
                case kGameUpdate:
                    game.draw();

                    break;
                case kResultUpdate:
                    result.draw();

                    break;
                }*/
                /////////////////////////////////////　


                Sprite::end();      // スプライト描画終了
                Direct3D::present();// 画面更新
            }
        }
    }
    // COMライブラリの初期化
    CoUninitialize();

    // 全てのインターフェイスの解
   // result.destroy();
  //  tutorial.destroy();
  //  title.destroy();
  //  game.destroy();
    Key::destroy();
    //   Font::destroy();
    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();
    Adx::destroy();

    return 0;
}


////////////////////////////////////
// CALLBACK
////////////////////////////////////
// スイッチ文内の指定のキーが押されたら実行される関数 CALLBACK
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;

        // アプリケーションが起動した時
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

        // 押されているか、離された瞬間、何回のみなど
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;


    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        // 何かのキーが押されたら入る
        switch( wParam )
        {
        case VK_ESCAPE:
            // ESCが押したらループを終了する
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;
        }
        break;

    case WM_DESTROY:
        // プログラムが終了した時に呼び出されるメッセージ
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
    // DefWindowProc...プログラマが書いたもの以外の動き（基本的な動き）を自動で処理してくれる関数
    //                 書かないとプログラムが動かない
}
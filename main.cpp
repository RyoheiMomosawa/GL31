/******************************************************************************
** 	タイトル  :
** 	ファイル名:
** 	作成者    : AT-13B-284 出席番号 14 木村 祥貴
** 	作成日    : //
******************************************************************************/

/******************************************************************************
**	更新内容
**
**
**
******************************************************************************/


/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "main.h"
#include "wndproc.h"
#include "Manager.h"
#include "resource.h"

#include <time.h>
#include <tchar.h>
#include <stdio.h>
#include <crtdbg.h>
/******************************************************************************
**	マクロ定義
******************************************************************************/

/**** 背景色 ****/
#define BGCOLOR_R ( 0 )
#define BGCOLOR_G ( 0 )
#define BGCOLOR_B ( 0 )
#define BGCOLOR_A ( 100 )


/**** FPS関連 ****/

/* FPS値 */
#define FPS ( 60 )

/* FPS表示文字数 */
#define STR_FPS ( 256 )

/* 表示文字カラー */
#define TEXTCOLOR_FPS_R ( 255 )
#define TEXTCOLOR_FPS_G ( 255 )
#define TEXTCOLOR_FPS_B ( 255 )
#define TEXTCOLOR_FPS_A ( 255 )

/* 表示位置 */
#define POS_FPS_X ( 0 )
#define POS_FPS_Y ( 0 )


/******************************************************************************
**	プロトタイプ宣言
******************************************************************************/

/* 初期化、終了処理 */
HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
int Uninit();

/* 更新、描画処理 */
void Update( void );
void Draw( void );

/* FPS表示 */
void DrawFPS( void );



/******************************************************************************
**	グローバル変数
******************************************************************************/

/* FPSカウンタ */
int g_nCountFPS;

/* インスタンス */
HINSTANCE g_hInstance;

/* ウィンドウ */
HWND g_hWnd;

/* RendererGL */
Manager *g_pManager;


/******************************************************************************
** 	関数名: WinMain
** 		関数の概要
** 	引数  :
** 	戻り値:
** 	説明  :
******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPerInstance, LPSTR lpCmdLine, int nCmdShow )
{
	/**** メモリリーク検出 ****/
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 85 );

	/**** インスタンスをコピー ****/
	g_hInstance = hInstance;


	/**** 変数宣言 ****/

	/* ウィンドウ生成 */
	// 親ウィンドウ
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ), // メモリサイズの指定
		CS_CLASSDC, // ウィンドウのスタイルを指定
		WndProc, // ウィンドウプロシーシャのアドレス(関数名)を指定
		0, // 使用しない
		0, // 使用しない
		hInstance, // インスタンスのハンドルを設定
		NULL, // 使用するアイコンを指定
		LoadCursor( NULL , IDC_ARROW ), // マウスカーソルを指定
		( HBRUSH )( COLOR_WINDOW + 1 ), // クライアント領域の背景色を設定
		MAKEINTRESOURCE( IDR_MENU1 ) , // メニューを追加したい時に設定
		WNDCLS_NAME, // ウィンドウクラスの名前を設定
		NULL, // 小さいアイコンの情報を設定

	};

	/* ウィンドウハンドル */
	HWND hWnd;

	/* メッセージ */
	MSG msg;

	/* ウィンドウの幅(クライアント領域) */
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };


	/* FPSに必要な変数 */
	DWORD dwFrameCount; // 更新・描画した回数
	DWORD dwCurrentTime; // 現在の時間
	DWORD dwExecLastTime; // 更新・描画処理をした最後の時間
	DWORD dwFPSLastTime; // FPSの数値を取得した最後の時間


	/**** ウィンドウ生成 ****/

	// 親ウィンドウの生成
	// クライアント領域の確保
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false ); // falseの部分は、メニューがある場合にはtrueにする

	// ウィンドウクラスの登録
	RegisterClassEx( &wcex );
	hWnd = CreateWindowEx( 0,
		WNDCLS_NAME, // ウィンドウ クラスの名前
		WND_NAME, // ウィンドウの名前
		WS_OVERLAPPEDWINDOW, // ウィンドウの種類
		CW_USEDEFAULT, // ウィンドウ表示位置 X座標
		CW_USEDEFAULT, //         〃         Y
		rect.right - rect.left, // 幅
		rect.bottom - rect.top, // 高さ
		NULL, // 親ウィンドウのハンドル
		NULL, // メニューハンドル または 子ウィンドウID
		hInstance,
		NULL ); // ウィンドウ作成データ


	/**** DirectX初期化処理 ****/
	if( FAILED( Init( hInstance, hWnd, TRUE ) ) )
	{
		return -1;

	}


	/**** ウィンドウの表示 ****/
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );


	/**** FPS開始位置 ****/

	/* 分解能 */
	timeBeginPeriod( 1 );

	/* FPS変数の初期化*/
	dwFrameCount =
		dwCurrentTime = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();


	/**** ゲーム処理 ****/
	while( 1 )
	{
		/*** ゲーム終了処理 ***/
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			/* メッセージが終了ならプログラム終了 */
			if( msg.message == WM_QUIT )
			{
				break;

			}
			else
			{
				/* メッセージの翻訳と送出 */
				TranslateMessage( &msg );
				DispatchMessage( &msg );

			}

		}
		/* DirectX(ゲーム)処理 */
		else
		{
			/*** FPS処理 ***/
			dwCurrentTime = timeGetTime(); // 現在の時間を取得

										   /* FPS算出 **** 500ms毎にFPSの値を更新 */
			if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;

			}

			/* 1/60毎の更新・描画処理 */
			if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / FPS ) )
			{
				/* 更新・描画処理をした時間を最後の時間として保管 */
				dwExecLastTime = dwCurrentTime;

				/* 更新・描画処理 */
				Update();
				Draw();

				/* 一定回数内に更新・描画処理した回数をカウント */
				dwFrameCount++;

			}

		}

	}


	/**** ウィンドウ削除 ****/
	UnregisterClass( WNDCLS_NAME, wcex.hInstance ); // ( ウィンドウクラス名 )


	/**** 終了処理 ****/
	Uninit();


	/**** 分解能 ****/
	timeEndPeriod( 1 );

	return ( int )msg.wParam;

}


/******************************************************************************
** 	関数名: 初期化処理 Init
** 		関数の概要
** 	引数  : ハンドルインスタンス、ハンドルウィンドウ、s初期画面の大きさ(bool)
** 	戻り値: HRESULT
** 	説明  : 初期化処理
******************************************************************************/
HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	/* レンダラの生成 */
	g_pManager = new Manager;

	// レンダラの初期化
	g_pManager->Init( hInstance, hWnd, bWindow );

	return S_OK;

}


/******************************************************************************
** 	関数名: 終了処理 Uninit
** 		関数の概要
** 	引数  : void
** 	戻り値: void
** 	説明  :
******************************************************************************/
int Uninit()
{
	// レンダラの削除
	g_pManager->Uninit();
	delete g_pManager;
	g_pManager = nullptr;


	/**** 終了処理成功時、0を返す ****/
	return 0;

}


/******************************************************************************
** 	関数名: 更新処理 Update
** 		関数の概要
** 	引数  : void
** 	戻り値: void
** 	説明  :
******************************************************************************/
void Update( void )
{
	// レンダラ
	g_pManager->Update();

}


/******************************************************************************
** 	関数名: 描画処理 Draw
** 		関数の概要
** 	引数  : void
** 	戻り値: void
** 	説明  :
******************************************************************************/
void Draw( void )
{
	// レンダラ
	g_pManager->Draw();

}


/******************************************************************************
** 関数名: インスタンスの情報を取得 GetInstance
** 関数の概要
** 引数  : void
** 戻り値: デバイスポインタ LPDIRECT3DDEVICE9
** 説明  :
******************************************************************************/
HINSTANCE GetInstance( void )
{
	return g_hInstance;

}


/******************************************************************************
** 	関数名: FPS表示 void DrawFPS( void )
** 		関数の概要
** 	引数  : void
** 	戻り値: void
** 	説明  :
******************************************************************************/
void DrawFPS( void )
{

}



/******************************************************************************
** 関数名: ウィンドウのハンドルを取得 GetHWND
** 関数の概要
** 引数  : void
** 戻り値: HWND
** 説明  :
******************************************************************************/
HWND GetHWND( void )
{
	return g_hWnd;

}


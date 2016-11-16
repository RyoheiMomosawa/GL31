/******************************************************************************
**	タイトル  :
**	ファイル名: wndproc.cpp
**	作成者    : AT-12A-244 出席番号 16 木村 祥貴
**	作成日    : 2015/5/10
**　修正日　　: 2016/2/9
******************************************************************************/

/******************************************************************************
**	更新内容
**
******************************************************************************/


/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "wndproc.h"
#include "resource.h"
#include "Manager.h"
#include "RendererGL.h"
#include "Color.h"
#include "Dialog.h"


/******************************************************************************
**	マクロ定義
******************************************************************************/


/******************************************************************************
**	プロトタイプ宣言
******************************************************************************/


/******************************************************************************
**	グローバル変数
******************************************************************************/

/* ポジション表示ダイアログ */
HWND g_PosDialog;

/* カメラ表示ダイアログ */
HWND g_CameraDialog;


/* ステータスバー */
HWND g_hStatusBar;
BOOL g_bStatusBar = FALSE;


/******************************************************************************
** 	関数名: LRESULT CALLBACK WndProc
** 		関数の概要
** 	引数  : 親ハンドル、メッセージ、
** 	戻り値: 引数と同じ
** 	説明  : メッセージの各判定処理
******************************************************************************/
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	/**** 変数宣言 ****/
	int nID; // メッセージボックス戻り値
	static HWND hWndButton; // ボタン
	static HWND hWndChild; // 子ウィンドウのポインタ
	static RECT rectChild; // 子ウィンドウの大きさ
	PAINTSTRUCT ps; // クライアント領域を描画する際に必要
	HINSTANCE hInstance = GetInstance();

	/* オブジェクトの移動量 */
	static int nPosX = 380;
	static int nPosY = 300;

	/* クライアント領域 */
	const RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };

	/* 親ウィンドウの大きさを取得 */
	RECT PrntWndRect;


	/* チェックボックス */
	static DWORD dwCheckMenu = 0;

	/* カラーダイアログ */
	static CHOOSECOLOR cc;
	static COLORREF CustColors[ 16 ];


	/**** メッセージ判定処理 ****/
	switch( uMsg )
	{
		case WM_DESTROY: // ×ボタンが押されたら
			PostQuitMessage( 0 );

			break;

		case WM_PAINT: // 描画・再描画する

			break;

		case WM_KEYDOWN: // キーが入力されたら
			switch( wParam )
			{
				case VK_ESCAPE: // エスケープ
					/* 終了確認ボックス */
					nID = MessageBox( hWnd, "ゲームを終了しますか？", "終了確認", MB_YESNO + MB_ICONQUESTION );
					if( nID == IDYES )
					{
						DestroyWindow( hWnd );

					}

					break;

			}

			break;

		case WM_CREATE: // ウィンドウが生成されたら
		{
			// モードレスダイアログ生成
			g_PosDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_DIALOG1 ), hWnd, PosDlgProc );
			g_CameraDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_DIALOG2 ), hWnd, CameraDlgProc );


			// カラーダイアログ生成
			Color col = RendererGL::GetBgColor();
			COLORREF cr = RGB( ( int )( col.r * 255.0f ), ( int )( col.g * 255.0f ), ( int )( col.b * 255.0f ) );
			ZeroMemory( &cc, sizeof CHOOSECOLOR );
			cc.lStructSize = sizeof CHOOSECOLOR;
			cc.hwndOwner = hWnd;
			cc.rgbResult = cr;
			cc.lpCustColors = CustColors;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;


			// ステータスバーの生成
			InitCommonControls();
			g_hStatusBar = CreateWindowEx(
				0, // 拡張スタイル
				STATUSCLASSNAME, // ウィンドウクラス
				NULL, // タイトル
				WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM, // ウィンドウ設定
				0, 0, 0, 0, // 座標、大きさ
				hWnd, // 親ウィンドウ
				( HMENU )ID_STATUSBAR, // ステータスバーID
				hInstance, // インスタンスハンドル
				NULL );
			SetWindowPos( g_hStatusBar, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

		}


		break;

		case WM_MOVE:

			break;

		case WM_COMMAND: // 生成したボタンが押されたら
			switch( LOWORD( wParam ) )
			{
				// **********************************************************************************************************
				// **		ファイル
				// **********************************************************************************************************
				case ID_CLOSE:
					DestroyWindow( hWnd );

					break;


				// **********************************************************************************************************
				// **		表示
				// **********************************************************************************************************


			// ------------------------------------------------

				case ID_WIRERFRAME:
				{
					HMENU hMenu = GetMenu( hWnd );

					// チェックの有無
					// チェック済み
					if( GetMenuState( hMenu, ID_WIRERFRAME, MF_BYCOMMAND ) & ( MF_BYCOMMAND | MFS_CHECKED ) )
					{
						// チェックを外し、ワイヤーフレームを解除
						dwCheckMenu = MF_BYCOMMAND | MFS_UNCHECKED;
						RendererGL::SetRenderMode( GLRS_FILLMODE, GLFILL_SOLID );

					}
					// チェック無し
					else
					{
						// チェックを付け、ワイヤーフレーム適用
						dwCheckMenu = MF_BYCOMMAND | MFS_CHECKED;
						RendererGL::SetRenderMode( GLRS_FILLMODE, GLFILL_WIREFRAME );

					}

					// チェックの反映
					CheckMenuItem( hMenu, ID_WIRERFRAME, dwCheckMenu );


					break;

				}


				case ID_STATUSBAR:
				{
					HMENU hMenu = GetMenu( hWnd );

					// チェックの有無
					// チェック済み
					if( GetMenuState( hMenu, ID_STATUSBAR, MF_BYCOMMAND ) & ( MF_BYCOMMAND | MFS_CHECKED ) )
					{
						// チェックを外し、ステータスバーを非表示
						dwCheckMenu = MF_BYCOMMAND | MFS_UNCHECKED;
						ShowWindow( g_hStatusBar, SW_HIDE );
						g_bStatusBar = FALSE;

					}
					// チェック無し
					else
					{
						// チェックを付け、ステータスバーを表示
						dwCheckMenu = MF_BYCOMMAND | MFS_CHECKED;
						ShowWindow( g_hStatusBar, SW_SHOW );
						SendMessage( g_hStatusBar, SB_SIMPLE, TRUE, 0L );
						g_bStatusBar = TRUE;

					}

					// チェックの反映
					CheckMenuItem( hMenu, ID_STATUSBAR, dwCheckMenu );

				}

					break;


				// **********************************************************************************************************
				// **		設定
				// **********************************************************************************************************

				case ID_BGCOLOR:
					if( ChooseColor( &cc ) )
					{
						RendererGL::SetBgColor( cc.rgbResult );

					}

					break;


				// **********************************************************************************************************
				// **		ヘルプ
				// **********************************************************************************************************

				case ID_HELP:

					break;


				case ID_VERSION:
					MessageBoxA( hWnd, "template ver 0.1", "バージョン情報", MB_OK );

					break;


				default:

					break;

			}

			break;

	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );

}


/******************************************************************************
** 	関数名: GetPosDialog
** 	関数の概要
** 	引数  : void
** 	戻り値: HWND
** 	説明  :
******************************************************************************/
HWND GetPosDialog()
{
	return g_PosDialog;

}


/******************************************************************************
** 	関数名: GetCameraDialog
** 	関数の概要
** 	引数  : void
** 	戻り値: HWND
** 	説明  :
******************************************************************************/
HWND GetCameraDialog()
{
	return g_CameraDialog;

}


/******************************************************************************
** 	関数名: UpdateStatusBar
** 	関数の概要
** 	引数  : void
** 	戻り値: void
** 	説明  :
******************************************************************************/
void UpdateStatusBar()
{
	if( g_bStatusBar )
	{
		SendMessage( g_hStatusBar, SB_SETTEXT, 255 | 0, ( LPARAM )"" );

	}

}


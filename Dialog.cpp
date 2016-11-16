/******************************************************************************
**	タイトル  :
**	ファイル名: Dialog.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/15
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "Dialog.h"


/******************************************************************************
**	グローバル変数
******************************************************************************/


/******************************************************************************
** 	関数名: CALLBACK PosDlgProc
** 	関数の概要
** 	引数  : ダイアログのデータ、メッセージ、パラメータ2つ
** 	戻り値: bool
** 	説明  : ダイアログの各判定処理
******************************************************************************/
BOOL CALLBACK PosDlgProc( HWND Dialog, UINT Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
	{
		case WM_INITDIALOG:

			return TRUE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( Dialog, 0 );

					break;

				default:

					break;

			}

			return TRUE;

		default:

			break;

	}

	return FALSE;

}


/******************************************************************************
** 	関数名: CALLBACK AboutDlgProc
** 	関数の概要
** 	引数  : ダイアログのデータ、メッセージ、パラメータ2つ
** 	戻り値: bool
** 	説明  : ダイアログの各判定処理
******************************************************************************/
BOOL CALLBACK CameraDlgProc( HWND Dialog, UINT Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
	{
		case WM_INITDIALOG:

			return TRUE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( Dialog, 0 );

					break;

				default:

					break;

			}

			return TRUE;

		default:

			break;

	}

	return FALSE;

}


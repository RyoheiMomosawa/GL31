#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: MousePointer.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/14
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include <Windows.h>


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/


/******************************************************************************
**	プロトタイプ宣言
******************************************************************************/

POINT GetMousePointer( HWND hWnd );
void GetMousePointer( HWND hWnd, POINT *po );



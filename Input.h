#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Input.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/5/9
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
#include <windows.h>
#include <string.h>

// DirectX
#include "d3dx9.h"
#define DIRECTINPUT_VERSION ( 0x0800 ) // エラー的なものの回避
#include "dinput.h" // 入力に必要
#include "xaudio2.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/

/* 描画処理に必要 */
#pragma comment ( lib , "d3d9.lib" )

/* DirectX9の拡張ライブラリ */
#pragma comment ( lib , "d3dx9.lib" )

/* DirectXコンポーネントに必要 */
#pragma comment ( lib , "dxguid.lib" )

/* 音の再生に必要なコンポーネント(FPSなどにも使用) */
#pragma comment ( lib , "winmm.lib" )

/* ボタン、キーボードの入力 */
#pragma comment ( lib , "dinput8.lib" )


/******************************************************************************
**	マクロ定義
******************************************************************************/

/**** マジックナンバー ****/

/* リピート開始時間 */
#define REPEAT_TIME ( 30 )

/* マウス動作設定 */
//#define COOPERRATIONLEBEL_MOUSE ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) // アクセス権限 フォアグラウンドのスクロール入力を許可しない
#define COOPERRATIONLEBEL_MOUSE ( DISCL_EXCLUSIVE | DISCL_BACKGROUND ) // アクセス権限 フォアグラウンドのスクロール入力を許可しない

/* コントローラ動作設定 */
#define COOPERRATIONLEBEL_JOYPAD ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) // アクセス権限 フォアグラウンドのスクロール入力を許可しない


// Z軸範囲
#define PROPRANGE_MIN ( -1000 )
#define PROPRANGE_MAM ( 1000 )

/* 十字キー各方向 */
#define POVSTATE_UP ( 0 )
#define POVSTATE_UPRIGHT ( 4500 )
#define POVSTATE_RIGHT ( 9000 )
#define POVSTATE_DOWNRIGHT ( 13500 )
#define POVSTATE_DOWN ( 18000 )
#define POVSTATE_DOWNLEFT ( 22500 )
#define POVSTATE_LEFT ( 27000 )
#define POVSTATE_UPLEFT ( 31500 )

/* マウス入力 */
enum MOUSEBUTTON
{
	MOUSEBUTTON_LEFT = 0,
	MOUSEBUTTON_RIGHT,
	MOUSEBUTTON_CENTER,
	MOUSEBUTTON_3,
#ifdef _SET_DIMOUSESTATE2_
	MOUSEBUTTON_4,
	MOUSEBUTTON_5,
	MOUSEBUTTON_6,
	MOUSEBUTTON_7,

#endif // _SET_DIMOUSESTATE2_

	MOUSEBUTTON_MAX

};

/* マウスステート */
#ifdef _SET_DIMOUSESTATE2_
typedef DIMOUSESTATE2 MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 8 )

#elif _SET_DIMOUSESTATE_
typedef DIMOUSESTATE MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 4 )

#else
typedef DIMOUSESTATE MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 4 )

#endif // SET MOUSESTATE

/* ジョイパッドステート */
#ifdef _SET_DIJOYSTATE2_
typedef DIJOYSTATE2 JOYPAD_STATE;

#elif _SET_DIJOYSTATE_
typedef DIJOYSTATE JOYPAD_STATE;

#else
typedef DIJOYSTATE JOYPAD_STATE;

#endif // SET JOYSTATE


/******************************************************************************
**	名前空間定義
******************************************************************************/
namespace input
{
	class Input
	{
		public:
		Input();
		~Input();

		// DirectInputオブジェクトの初期化、削除処理
		static HRESULT Init( HINSTANCE hInstance, HWND hWnd );
		static int Release();

		// DirectInputオブジェクト
		static LPDIRECTINPUT8 lpDirectInput;

		protected:

	};

}

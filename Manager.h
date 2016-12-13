#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Manager.h
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

// システム関連
#include <Windows.h>
#include "DIKeyboard.h"
#include "DIMouse.h"
#include "SoundAL.h"
#include "WindowsSocketService.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/

// サウンド関連
#define SOURCE_MAX ( 5 )
#define BUFFER_MAX ( 2 )


/******************************************************************************
**	クラス定義
******************************************************************************/
class RendererGL;
class SceneGL;
class Mode;
class Fade;
class Server;
class Client;
class Manager
{
public:
	Manager();
	virtual ~Manager();


	// メソッド
	static HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	static int Uninit();
	static void Update();
	static void Draw();


	// Set,Get
	static input::DirectInput *GetKeyboard();
	static input::DIMouse *GetMouse();
	static void SetMode( Mode *Mode );
	static Client *GetClient();


	// メンバ変数
private:
	/// システム関連
	// レンダラ
	static RendererGL *m_pRenderer;
	// シーンクラス
	static SceneGL *m_pScene;
	// ハードウェア
	static input::DirectInput *m_pKeyboard;
	static input::DIMouse *m_Mouse;
	// サウンド
	static SoundAL *m_pSound;
	// モード管理
	static Mode *m_pMode;
	// フェード
	static Fade *m_pFade;


	// BGMデータ
	static ALuint m_bgm001ID;

	static Client *m_pReceive;
	static HANDLE m_hClient;
	static unsigned int m_thClient;

};


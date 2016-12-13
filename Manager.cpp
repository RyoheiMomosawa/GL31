/******************************************************************************
**	タイトル  :
**	ファイル名: Mnager.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/5/9
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "Manager.h"


// オブジェクト
#include "SceneGL.h"
#include "Scene2DGL.h"
#include "Mode.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Fade.h"
#include "SceneGLTimer.h"


// ネットワーク
#include "Server.h"
#include "Client.h"


// システム
#include "wndproc.h"
#include "main.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
RendererGL *Manager::m_pRenderer;
SceneGL *Manager::m_pScene;
input::DirectInput *Manager::m_pKeyboard;
input::DIMouse *Manager::m_Mouse;
SoundAL *Manager::m_pSound;
Mode *Manager::m_pMode;
Fade *Manager::m_pFade;
ALuint Manager::m_bgm001ID;

Client *Manager::m_pReceive;
HANDLE Manager::m_hClient;
unsigned int Manager::m_thClient;


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Manager::Manager()
{
}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Manager::~Manager()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT Manager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// ネットワークの初期化
	WindowsSocketService::Init();
	m_pReceive = new Client;
	m_pReceive->SetIPAdress( "172.29.9.74" );
	m_pReceive->SetPortNo( 11451 );
	m_pReceive->SetBufferSize( MAX_PATH );
	m_pReceive->Init();
	m_hClient = ( HANDLE )_beginthreadex( NULL, 0, m_pReceive->Send, NULL, 0, &m_thClient );

	// レンダラーの作成
	m_pRenderer = new RendererGL;
	if( FAILED( m_pRenderer->Init( hInstance, hWnd, bWindow ) ) )
	{
		return E_FAIL;

	}

	// キーボード
	input::Input::Init( hInstance, hWnd );
	m_pKeyboard = new input::DIKeyboard;
	m_pKeyboard->Init( hWnd );

	// マウス
	m_Mouse = new input::DIMouse;
	m_Mouse->Init( hWnd );


	// サウンド
	m_pSound = new SoundAL;
	m_pSound->Init();
	m_pSound->CreateSource( SOURCE_MAX );
	m_pSound->CreateBuffer( BUFFER_MAX );
	m_pSound->CreateBufferData( "./data/BGM/bgm001.wav", &m_bgm001ID, AL_TRUE );
	m_pSound->SetBuffer( m_bgm001ID );
	m_pSound->PauseSoundAll();


	// モードの作成 //////////////////////
	m_pFade = new Fade;
	m_pFade->Init();
	Fade::Set( new Game );


	/**** 処理終了時にS_OKを返す ****/
	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
int Manager::Uninit()
{
	// モードの削除 
	SetMode( NULL );
	m_pFade->Uninit();
	delete m_pFade;
	m_pFade = NULL;


	// ネットワークの終了
	CloseHandle( m_hClient );
	delete m_pReceive;
	WindowsSocketService::Uninit();


	// サウンド
	m_pSound->Uninit();
	delete m_pSound;
	m_pSound = NULL;


	// コントローラ
	m_pKeyboard->Uninit();
	delete m_pKeyboard;
	m_pKeyboard = NULL;

	
	// マウス
	m_Mouse->Uninit();
	delete m_Mouse;
	m_Mouse = NULL;


	// Inputのリリース
	input::Input::Release();


	// レンダラー
	delete m_pRenderer;
	m_pRenderer = NULL;


	/**** 終了処理成功時、0を返す ****/
	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Manager::Update()
{
	m_pKeyboard->Update();
	m_Mouse->Update();
	m_pSound->Update();
	m_pFade->Update();
	m_pMode->Update();

}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Manager::Draw()
{
	// 描画準備
	if( !m_pRenderer->BeginDraw() )
	{
		return;

	}

	///////////////////////////////////////////////
	// 描画開始
	//////////////////////////////////////////////

	// 各モード、オブジェクト
	m_pMode->Draw();

	// フェード
	m_pFade->Draw();


	/////////////////////////////////////////////
	// 描画終了
	/////////////////////////////////////////////

	// 描画終了
	m_pRenderer->EndDraw();


	// ステータスバーの更新
	UpdateStatusBar();

	// サウンド再生
//	m_pSound->PlaySoundAll();

}


/******************************************************************************
**	関数名: GetKeyboard
**	関数の概要
**	引数  : void
**	戻り値: input::DirectInput *
**	説明  :
******************************************************************************/
input::DirectInput *Manager::GetKeyboard()
{
	return m_pKeyboard;

}


/******************************************************************************
**	関数名: GetMouse
**	関数の概要
**	引数  : void
**	戻り値: input::DirectInput *
**	説明  :
******************************************************************************/
input::DIMouse *Manager::GetMouse()
{
	return m_Mouse;

}


/******************************************************************************
**	関数名: SetMode
**	関数の概要
**	引数  : Mode *Mode
**	戻り値: void
**	説明  :
******************************************************************************/
void Manager::SetMode( Mode *Mode )
{
	// 終了処理
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;

	}

	// 初期化処理
	if( m_pMode == NULL && Mode != NULL )
	{
		m_pMode = Mode;
		m_pMode->Init();

	}

}


/******************************************************************************
**	関数名: GetClient
**	関数の概要
**	引数  : void
**	戻り値: Client *
**	説明  :
******************************************************************************/
Client *Manager::GetClient()
{
	return m_pReceive;

}


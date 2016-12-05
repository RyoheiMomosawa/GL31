/******************************************************************************
**	タイトル  :
**	ファイル名: Game.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/19
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "Game.h"

// システム
#include "main.h"
#include "Result.h"
#include "Manager.h"
#include "Fade.h"
#include "wndproc.h"


// ネットワーク
#include "WindowsSocketService.h"
#include "Server.h"
#include "Client.h"


// ゲームオブジェクト
#include "SceneGL.h"
#include "Scene2DGL.h"
#include "DIKeyboard.h"
#include "SceneGLTimer.h"


// デバッグ処理
#include "WndProcDbgManager.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
SceneGLTimer *Game::m_pTimer;


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Game::Game()
{
}


/******************************************************************************
**	関数名: ~
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Game::~Game()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void Game::Init()
{
	// ネットワークの初期化
	WindowsSocketService::Init();

	// シーンの作成
	// 背景
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/bg001.tga" );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	// オブジェクト
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/runningman101.tga" );
	m_pScene->SetAnimation( 5, 5, 2 );
	m_pScene->SetParam( &Vector3( 100.0f, 100.0f, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	// タイマー
	m_pTimer = SceneGLTimer::Create();
	m_pTimer->SetTexture( "./data/TEXTURE/number000.tga" );
	m_pTimer->SetColor( &Color( 0.8f, 0.5f, 0.125f, 1.0f ) );
	m_pTimer->SetDigit( 3 );
	m_pTimer->SetTimer( 123 );
	//m_pTimer->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, 80.0f, 0.0f ), SCENEPARAM_POS );
	m_pTimer->SetParam( &Vector3( 150.0f, 80.0f, 0.0f ), SCENEPARAM_POS );
	m_pTimer->SetParam( &Vector3( 50.0f, 70.0f, 0.0f ), SCENEPARAM_SIZE );
	m_pTimer->Reset();

	m_pScene->InitAll();

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void Game::Uninit()
{
	/* シーンの削除 */
	m_pScene->UninitAll();

	// ネットワークの終了
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Game::Update()
{
	// シーンの更新
	m_pScene->UpdateAll();


	// モード切り替え
	if( Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) && !m_bModeFlag )
	{
		Fade::Set( new Result );
		m_bModeFlag = true;

	}

}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Game::Draw()
{
	// シーンの描画
	m_pScene->DrawAll();

}


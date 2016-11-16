/******************************************************************************
**	タイトル  :
**	ファイル名: Result.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/19
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "Result.h"

// オブジェクト
#include "Scene2DGL.h"

// システム
#include "Manager.h"
#include "Title.h"
#include "main.h"
#include "Fade.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	関数名: Result
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Result::Result()
{
	m_pScene = NULL;

}


/******************************************************************************
**	関数名: ~Result
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Result::~Result()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void Result::Init()
{
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/bg002.tga" );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	m_pScene->InitAll();

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void Result::Uninit()
{
	m_pScene->UninitAll();
	m_pScene = NULL;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Result::Update()
{
	m_pScene->UpdateAll();

	// モードの切り替え
	if( Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) && !m_bModeFlag )
	{
		Fade::Set( new Title );
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
void Result::Draw()
{
	m_pScene->DrawAll();

}

/******************************************************************************
**	タイトル  :
**	ファイル名: CharaSelect.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/19
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "CharaSelect.h"


// オブジェクト
#include "Scene2DGL.h"


// システム
#include "Manager.h"
#include "Game.h"
#include "main.h"
#include "Fade.h"

using namespace std;

namespace
{
	static const string jobNameFilePass[] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string xActNameFileNames[] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string aActNameFileNames[] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};
}


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	関数名: CharaSelect
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
CharaSelect::CharaSelect()
{
	m_pBg = NULL;

}


/******************************************************************************
**	関数名: ~CharaSelect
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
CharaSelect::~CharaSelect()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void CharaSelect::Init()
{
	m_pBg = Scene2DGL::Create();
	m_pBg->SetTexture( "./data/TEXTURE/backGround.tga" );
	m_pBg->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pBg->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );






	m_pBg->InitAll();
}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void CharaSelect::Uninit()
{
	m_pBg->UninitAll();
	m_pBg = NULL;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void CharaSelect::Update()
{
	//m_pBg->AddTexU(0.001f);

	m_pBg->UpdateAll();

	// モードの切り替え
	if( //Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) 
		input::is_each_trigger(input::DECIDE) || input::is_each_trigger(input::PAUSE)
		&& !m_bModeFlag)
	{
		Fade::Set( new Game );
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
void CharaSelect::Draw()
{
	m_pBg->DrawAll();

}

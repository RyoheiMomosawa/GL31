/******************************************************************************
**	タイトル  :
**	ファイル名: PlayerSamurai.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/19
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "PlayerSamurai.h"


// オブジェクト
#include "Scene2DGL.h"

// システム
#include "Manager.h"
#include "main.h"
#include "Fade.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	関数名: PlayerSamurai
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
PlayerSamurai::PlayerSamurai()
{
	m_pScene = NULL;
	m_Hp = 100;
	m_Forward_direction = 0.0f;
}


/******************************************************************************
**	関数名: ~PlayerSamurai
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
PlayerSamurai::~PlayerSamurai()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void PlayerSamurai::Init(int id)
{
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/str_samurai.tga" );

	if(id)
	{
		m_pScene->SetParam(&Vector3(100.0f, 50.0f, 0.0f), SCENEPARAM_POS);
	}
	else
	{
		m_pScene->SetParam(&Vector3(300.0f, 150.0f, 0.0f), SCENEPARAM_POS);
	}


	m_pScene->SetParam(&Vector3(30.0f, 50.0f, 0.0f), SCENEPARAM_SIZE);
}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void PlayerSamurai::Uninit()
{
}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void PlayerSamurai::Update()
{
	Move();
	Attack0();
	Attack1();
}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void PlayerSamurai::Draw()
{
}

void PlayerSamurai::Attack0()
{
	//TODO　攻撃出来ないなら抜ける
	if(0)
	{
		return;
	}

	//攻撃ボタン0
	if(Manager::GetKeyboard()->GetTrigger(DIK_K))
	{
		MessageBox(nullptr, "斬撃！！", "test", MB_OK);
	}
}

void PlayerSamurai::Attack1()
{
	//TODO　攻撃出来ないなら抜ける
	if(0)
	{
		return;
	}

	//攻撃ボタン1
	if(Manager::GetKeyboard()->GetTrigger(DIK_L))
	{
		MessageBox(nullptr, "攻撃を弾く", "test", MB_OK);
	}
}

void PlayerSamurai::Move()
{
	//TODO　移動出来ないなら抜ける
	if(0)
	{
		return;
	}

	if(Manager::GetKeyboard()->GetPress(DIK_A))
	{
		m_Forward_direction = 3.14 * -0.5f;
		m_pScene->AddPos(-2, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_D))
	{
		m_Forward_direction = 3.14 * 0.5f;
		m_pScene->AddPos(2, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_W))
	{
		m_Forward_direction = 3.14 * 1.0f;
		m_pScene->AddPos(0, -2);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_S))
	{
		m_Forward_direction = 3.14 * 0.0f;
		m_pScene->AddPos(0, 2);
	}
}

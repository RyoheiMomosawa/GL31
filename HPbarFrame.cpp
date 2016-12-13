/******************************************************************************
**	タイトル  :
**	ファイル名: HPbarFrame.cpp
**	作成者    : AT-13B-284 出席番号 5 稲垣雄大
**	作成日    : 2016/11/28
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "HPbarFrame.h"


// オブジェクト
#include "Scene2DGL.h"


// システム
#include "Manager.h"
#include "Game.h"
#include "main.h"
#include "HPbarFrame.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
int cntID = 0;
static ID m_ID;

/******************************************************************************
**	関数名: HPbarFrame
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
HPbarFrame::HPbarFrame()
{
	m_pHPbarFrame = NULL;

}


/******************************************************************************
**	関数名: ~HPbarFrame
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
HPbarFrame::~HPbarFrame()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void HPbarFrame::Init()
{
	cntID++;
	if (cntID == 0)
	{
		m_ID = ID_0;
	}
	else if (cntID == 1)
	{
		m_ID = ID_1;
	}
	else
	{
		cntID = 0;
		m_ID = ID_0;
	}

	if (m_ID == 0)
	{//プレイヤー１の生成
		m_pHPbarFrame = Scene2DGL::Create();
		m_pHPbarFrame->SetTexture("./data/TEXTURE/hp_back.tga");
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_WIDTH, (float)HPBARFRAME_HEIGHT, 0.0f), SCENEPARAM_SIZE);
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_POSX, (float)HPBARFRAME_POSY, 0.0f), SCENEPARAM_POS);
	}
	else if (m_ID == 1)
	{//プレイヤー２の生成
		m_pHPbarFrame = Scene2DGL::Create();
		m_pHPbarFrame->SetTexture("./data/TEXTURE/hp_back.tga");
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_WIDTH, (float)HPBARFRAME_HEIGHT, 0.0f), SCENEPARAM_SIZE);
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_POSX_2, (float)HPBARFRAME_POSY,  0.0f), SCENEPARAM_POS);
	}

	/*m_pHPbarFrame = Scene2DGL::Create();
	m_pHPbarFrame->SetTexture("./data/TEXTURE/bg000.tga");
	m_pHPbarFrame->SetParam(&Vector3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f), SCENEPARAM_SIZE); 
	m_pHPbarFrame->SetParam(&Vector3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), SCENEPARAM_POS);*/

	m_pHPbarFrame->InitAll();

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void HPbarFrame::Uninit()
{
	m_pHPbarFrame->UninitAll();
	m_pHPbarFrame = NULL;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void HPbarFrame::Update()
{
	m_pHPbarFrame->UpdateAll();

}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void HPbarFrame::Draw()
{
	m_pHPbarFrame->DrawAll();

}

/******************************************************************************
**	関数名: Create
**		関数の概要
**	引数  : void
**	戻り値: HPbarFrame *
**	説明  : 生成成功時 Scene2Dポインタ、失敗時 NULL
******************************************************************************/
HPbarFrame *HPbarFrame::Create()
{
	HPbarFrame *p;
	p = new HPbarFrame;
	p->Init();
	return p;
}



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
	static const int JOB_NUM = 3;

	static const string jobNameFilePass[JOB_NUM] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string xActNameFileNames[JOB_NUM] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string aActNameFileNames[JOB_NUM] =
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

	switch(m_state)
	{
	case SELECT:	UpdateSelectCheck();	break;
	case ASK:		UpdateAskToBattle();	break;
	}

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

//キャラクターセレクト
//引数　プレイヤーID
void CharaSelect::UpdateSelectCharactor(int id)
{
	//右キー
	if(input::is_trigger(RIGHT, id))
	{
		//カーソルを下へ(循環型)
		++m_selectId[id] %= JOB_NUM;

		////カーソル移動音
		//sound::play_se("data/se/ザ・マッチメイカァズ/cursor_select.wav", 1.0f, 0.625f);

		//カーソルの移動　と　説明の変更
		m_pJobName[id]->SetTexture(jobNameFilePass[m_selectId[id]].c_str());
		m_pActName[id][X_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
		m_pActName[id][A_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
	}

	//左キー
	if(input::is_trigger(LEFT, id))
	{
		//カーソルを上へ(循環型)
		m_selectId[id] = (m_selectId[id] + JOB_NUM - 1) % JOB_NUM;

		////カーソル移動音
		//sound::play_se("data/se/ザ・マッチメイカァズ/cursor_select.wav", 1.0f, 0.625f);

		//カーソルの移動　と　説明の変更
		m_pJobName[id]->SetTexture(jobNameFilePass[m_selectId[id]].c_str());
		m_pActName[id][X_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
		m_pActName[id][A_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
	}

	//決定ボタンが押されたら
	if(input::is_trigger(DECIDE, id))
	{
		//決定フラグON　決定文字表示
		m_isDecide[id] = true;
		m_pDecide[id]->GetObject3D()->bDraw = true;
	}

	//キャンセルボタンが押されたら
	if(input::is_trigger(CANSEL, id))
	{
		//決定フラグOFF　決定文字非表示
		m_isDecide[id] = false;
		m_pDecide[id]->GetObject3D()->bDraw = false;
	}
}

//セレクトのチェック
void CharaSelect::UpdateSelectCheck()
{
	//両プレイヤーのセレクト処理
	UpdateSelectCharactor(0);
	UpdateSelectCharactor(1);

	//両プレイヤー共に選択が終われば
	if(m_isDecide[0] && m_isDecide[1])
	{
		m_state = State::ASK;

		//勝負開始　確認画面を表示する
		m_pDecideMask->GetObject3D()->bDraw		= true;
		m_pAskMask->GetObject3D()->bDraw		= true;
		m_pAskToStart->GetObject3D()->bDraw		= true;
		m_pYes->GetObject3D()->bDraw			= true;
		m_pNo->GetObject3D()->bDraw				= true;
	}
}

//バトル移行確認
void CharaSelect::UpdateAskToBattle()
{
	//決定ボタンが押されたら
	if(input::is_each_trigger(DECIDE)
		&& !m_bModeFlag)
	{
		//バトル開始OKなら　ゲームへ
		if(m_isStartBattle)
		{
			Fade::Set(new Game);
			m_bModeFlag = true;
		}
		else
		{
			//両プレイヤーとも　未決定状態に戻す
			for(int id = 0; id < 2; ++id)
			{
				//決定フラグOFF　決定文字非表示
				m_isDecide[id] = false;
				m_pDecide[id]->GetObject3D()->bDraw = false;
			}

			//選択状態へ戻す
			m_state = State::SELECT;

			//勝負開始　確認画面を非表示に
			m_pDecideMask->GetObject3D()->bDraw		= false;
			m_pAskMask->GetObject3D()->bDraw		= false;
			m_pAskToStart->GetObject3D()->bDraw		= false;
			m_pYes->GetObject3D()->bDraw			= false;
			m_pNo->GetObject3D()->bDraw				= false;
		}
	}

	//キャンセルボタンが押されたら
	if(input::is_each_trigger(CANSEL))
	{
		//両プレイヤーとも　未決定状態に戻す
		for(int id = 0; id < 2; ++id)
		{
			//決定フラグOFF　決定文字非表示
			m_isDecide[id] = false;
			m_pDecide[id]->GetObject3D()->bDraw = false;
		}

		//選択状態へ戻す
		m_state = State::SELECT;

		//勝負開始　確認画面を非表示に
		m_pDecideMask->GetObject3D()->bDraw		= false;
		m_pAskMask->GetObject3D()->bDraw		= false;
		m_pAskToStart->GetObject3D()->bDraw		= false;
		m_pYes->GetObject3D()->bDraw			= false;
		m_pNo->GetObject3D()->bDraw				= false;
	}
}

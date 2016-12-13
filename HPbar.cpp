/******************************************************************************
**	タイトル  :
**	ファイル名: HPbar.cpp
**	作成者    : AT-13B-284 出席番号 5 稲垣雄大
**	作成日    : 2016/11/30
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "HPbar.h"


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
int cntID2 = 0;
static ID m_ID;

/******************************************************************************
**	関数名: HPbar
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
HPbar::HPbar()
{
	m_pHPbar = NULL;

}


/******************************************************************************
**	関数名: ~HPbar
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
HPbar::~HPbar()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
void HPbar::Init()
{
	cntID2++;
	if (cntID2 == 1)
	{
		m_ID = ID_0;
	}
	else
	{
		cntID2 = 0;
		m_ID = ID_1;
	}

	int onigiriSpaceX = 0;
	int onigiriSpaceY = 0;

	if (m_ID == 0)
	{//プレイヤー１の生成
		for (int cnt = 0; cnt < ONIGIRI_COUNT; cnt ++)
		{
			onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));//設置位置をずらす（Ｙ軸）
			m_pHPbar = Scene2DGL::Create();
			m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
			onigiriSpaceX += ONIGIRI_SPACE_X;//設置位置をずらす（Ｘ軸）
			
		}
		
	}
	else if (m_ID == 1)
	{//プレイヤー２の生成
		for (int cnt = 0; cnt < ONIGIRI_COUNT; cnt++)
		{
			onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));//設置位置をずらす（Ｙ軸）
			m_pHPbar = Scene2DGL::Create();
			m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
			m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH + ONIGIRI_SIZE + ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
			onigiriSpaceX += ONIGIRI_SPACE_X;//設置位置をずらす（Ｘ軸）
		}
	}

	m_pHPbar->InitAll();

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
void HPbar::Uninit()
{
	m_pHPbar->UninitAll();
	m_pHPbar = NULL;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void HPbar::Update()
{
	cntID2++;
	if (cntID2 == 1)
	{
		m_ID = ID_0;
	}
	else
	{
		cntID2 = 0;
		m_ID = ID_1;
	}

	static int HP1 = 10;
	static int HP2 = 10;
	static int HP1_old = 0;
	static int HP2_old = 0;
	HP1_old = HP1;
	HP2_old = HP2;

	//CScene *scene = CScene::GetList(DRAWTYPE_OBJ);		// リスト取得
	//while (scene)
	//{
	//	// プレイヤー同士の当たり判定
	//	if (scene->GetObjType() == OBJTYPE_PLAYER)
	//	{
	//		// クラスのキャスト
	//		CPlayer *Player = dynamic_cast< CPlayer* >(scene);
	//		if (Player->GetLabel() == PLAYER_LABEL_01)
	//		{
	//			HP1 = Player->GetHp();
	//		}
	//		else
	//		{
	//			HP2 = Player->GetHp();
	//		}
	//	}
	//	scene = scene->GetNext();
	//}

	//テスト/////////////////////////////////////////////////////////////////////////
	//if (Manager::GetKeyboard()->GetTrigger(DIK_UP))
	//{
	//	HP1++;
	//	HP2++;
	//}
	//else if (Manager::GetKeyboard()->GetTrigger(DIK_DOWN))
	//{
	//	HP1--;
	//	HP2--;
	//}
	
	//更新//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int onigiriSpaceX = 0;
	int onigiriSpaceY = 0;
	if (m_ID == 0)
	{//プレイヤー１の生成
		if (HP1_old != HP1)
		{
			for (int cnt = 0; cnt < ONIGIRI_COUNT - HP1; cnt++)
			{
				onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));
				m_pHPbar = Scene2DGL::Create();
				m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
				onigiriSpaceX += ONIGIRI_SPACE_X;

			}
		}

	}
	else if (m_ID == 1)
	{//プレイヤー２の生成
		if (HP2_old != HP2)
		{
			for (int cnt = 0; cnt < ONIGIRI_COUNT - HP2; cnt++)
			{
				onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));
				m_pHPbar = Scene2DGL::Create();
				m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
				m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH + ONIGIRI_SIZE + ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
				onigiriSpaceX += ONIGIRI_SPACE_X;
			}
		}
	}
	
	

	m_pHPbar->UpdateAll();

}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void HPbar::Draw()
{
	m_pHPbar->DrawAll();
}

/******************************************************************************
**	関数名: Create
**		関数の概要
**	引数  : void
**	戻り値: HPbarFrame *
**	説明  : 生成成功時 Scene2Dポインタ、失敗時 NULL
******************************************************************************/
HPbar *HPbar::Create()
{
	HPbar *p;
	p = new HPbar;
	p->Init();
	return p;
}




































///******************************************************************************
//**	タイトル  :
//**	ファイル名: HPbar.cpp
//**	作成者    : AT-13B-284 出席番号 5 稲垣雄大
//**	作成日    : 2016/11/30
//**	修正日	　: //
//********************************************************************************/
//
///******************************************************************************
//**	インクルードファイル
//******************************************************************************/
//
//// 自身ヘッダ
//#include "HPbar.h"
//
//
//// オブジェクト
//#include "Scene2DGL.h"
//
//
//// システム
//#include "Manager.h"
//#include "Game.h"
//#include "main.h"
//#include "HPbarFrame.h"
//
//
///******************************************************************************
//**	静的メンバ変数
//******************************************************************************/
//int cntID2 = 0;
//static ID m_ID;
//HP hp[2] =
//{
//	{ 0, 0, 0, 0 },
//	{ 0, 0, 0, 0 },
//};
//
///******************************************************************************
//**	関数名: HPbar
//**		関数の概要
//**	引数  : void
//**	戻り値: void
//**	説明  : コンストラクタ
//******************************************************************************/
//HPbar::HPbar()
//{
//	m_pHPbar = NULL;
//
//}
//
//
///******************************************************************************
//**	関数名: ~HPbar
//**		関数の概要
//**	引数  : void
//**	戻り値: void
//**	説明  : デストラクタ
//******************************************************************************/
//HPbar::~HPbar()
//{
//}
//
//
///******************************************************************************
//**	関数名: 初期化処理 Init
//**		関数の概要
//**	引数  :
//**	戻り値: HRESULT
//**	説明  : 初期化処理
//******************************************************************************/
//void HPbar::Init()
//{
//	//変数
//	hp[0].posX = 0;
//	hp[0].colR = 0;
//	hp[0].colG = 0;
//	hp[0].colB = 0;
//
//	//変数
//	hp[1].posX = 0;
//	hp[1].colR = 0;
//	hp[1].colG = 0;
//	hp[1].colB = 0;
//	
//	m_pHPbar->InitAll();
//
//}
//
//
///******************************************************************************
//**	関数名: 終了処理 Uninit
//**		関数の概要
//**	引数  : void
//**	戻り値: int
//**	説明  :
//******************************************************************************/
//void HPbar::Uninit()
//{
//	m_pHPbar->UninitAll();
//	m_pHPbar = NULL;
//
//}
//
//
///******************************************************************************
//**	関数名: 更新処理 Update
//**		関数の概要
//**	引数  : void
//**	戻り値: void
//**	説明  :
//******************************************************************************/
//void HPbar::Update()
//{
//	cntID2++;
//	if (cntID2 == 1)
//	{
//		m_ID = ID_0;
//	}
//	else
//	{
//		cntID2 = 0;
//		m_ID = ID_1;
//	}
//
//	static int HP1 = 0;
//	static int HP2 = 0;
//
//	//CScene *scene = CScene::GetList(DRAWTYPE_OBJ);		// リスト取得
//	//while (scene)
//	//{
//	//	// プレイヤー同士の当たり判定
//	//	if (scene->GetObjType() == OBJTYPE_PLAYER)
//	//	{
//	//		// クラスのキャスト
//	//		CPlayer *Player = dynamic_cast< CPlayer* >(scene);
//	//		if (Player->GetLabel() == PLAYER_LABEL_01)
//	//		{
//	//			HP1 = Player->GetHp();
//	//		}
//	//		else
//	//		{
//	//			HP2 = Player->GetHp();
//	//		}
//	//	}
//	//	scene = scene->GetNext();
//	//}
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	if (m_ID == 0)
//	{
//		hp[0].posX++;
//		if (HP_X_Left + hp[0].posX == HP_X_Right)
//		{
//			hp[0].posX = 0;
//		}
//		////ＨＰバーの位置変更
//		//hp[0].posX = (HP_MAX - HP1) * (HPBAR_WIDTH / HP_MAX);
//
//		//ＨＰバーの色変更
//		if (hp[0].posX < (HP_X_Right / 2))
//		{
//			hp[0].colR = 0;
//			hp[0].colG = 200;
//			hp[0].colB = 100;
//		}
//		else if (hp[0].posX >= (HP_X_Right / 2) && hp[0].posX < (HP_X_Right / 3))
//		{
//			hp[0].colR = 255;
//			hp[0].colG = 255;
//			hp[0].colB = 0;
//		}
//		else
//		{
//			hp[0].colR = 255;
//			hp[0].colG = 0;
//			hp[0].colB = 0;
//		}
//
//		/*m_pHPbar = Scene2DGL::Create();
//		m_pHPbar->SetTexture("./data/TEXTURE/HPb.tga");
//		m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH, (float)HPBAR_HEIGHT, 0.0f), SCENEPARAM_SIZE);
//		m_pHPbar->SetParam(&Vector3((float)HPBAR_POSX, (float)HPBAR_POSY, 0.0f), SCENEPARAM_POS);
//		m_pHPbar->SetColor(&Color(hp[0].colR, hp[0].colG, hp[0].colB, 255));*/
//
//		//VERTEX_2D *pVtx;
//
//		//m_VertexBuffer->Lock(                 //頂点情報へのポインタを取得 ＝ ロック
//		//	0,
//		//	0,
//		//	(void**)&pVtx,
//		//	0);
//
//
//		//pVtx[0].pos = D3DXVECTOR3(HP_X_Left + hp[0].posX, HP_Y_Left, 0.0f);						//頂点座標（Ｘ、Ｙ、Ｚ）
//		//pVtx[1].pos = D3DXVECTOR3(HP_X_Right, HP_Y_Left, 0.0f);
//		//pVtx[2].pos = D3DXVECTOR3(HP_X_Left + hp[0].posX, HP_Y_Right, 0.0f);
//		//pVtx[3].pos = D3DXVECTOR3(HP_X_Right, HP_Y_Right, 0.0f);
//
//		//pVtx[0].rhw = 1.0f;												//座標変換用係数
//		//pVtx[1].rhw = 1.0f;
//		//pVtx[2].rhw = 1.0f;
//		//pVtx[3].rhw = 1.0f;
//
//		//pVtx[0].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);				//頂点カラー（Ｒ，Ｇ，Ｂ，Ａ）
//		//pVtx[1].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		//pVtx[2].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		//pVtx[3].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//
//		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);							//テクスチャのＵＶ座標（Ｕ，Ｖ）
//		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		//m_VertexBuffer->Unlock();              //ロックの解除
//
//	}
//
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	else if (m_ID == 1)
//	{
//		////ＨＰバーの位置変更
//		hp[1].posX = (HP_MAX - HP1) * (HPBAR_WIDTH / HP_MAX);
//
//		//ＨＰバーの色変更
//		if (hp[1].posX < (HPBAR_WIDTH / 2))
//		{
//			hp[1].colR = 0;
//			hp[1].colG = 0;
//			hp[1].colB = 255;
//		}
//		else if (hp[1].posX >= (HPBAR_WIDTH / 2) && hp[1].posX < (HPBAR_WIDTH / 3))
//		{
//			hp[1].colR = 0;
//			hp[1].colG = 255;
//			hp[1].colB = 0;
//		}
//		else
//		{
//			hp[1].colR = 255;
//			hp[1].colG = 0;
//			hp[1].colB = 0;
//		}
//
//		//m_pHPbar = Scene2DGL::Create();
//		////m_pHPbar->SetTexture("./data/TEXTURE/HPb.tga");
//		//m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH - hp[0].posX, (float)HPBAR_HEIGHT, 0.0f), SCENEPARAM_SIZE);
//		//m_pHPbar->SetParam(&Vector3((float)HPBAR_POSX, (float)HPBAR_POSY, 0.0f), SCENEPARAM_POS);
//		//m_pHPbar->SetColor(&Color(hp[1].colR, hp[1].colG, hp[1].colB, 255));
//
//
//
//		//VERTEX_2D *pVtx;
//
//		//m_VertexBuffer->Lock(                 //頂点情報へのポインタを取得 ＝ ロック
//		//	0,
//		//	0,
//		//	(void**)&pVtx,
//		//	0);
//
//
//		//pVtx[0].pos = D3DXVECTOR3(HP_X_Left2, HP_Y_Left2, 0.0f);						//頂点座標（Ｘ、Ｙ、Ｚ）
//		//pVtx[1].pos = D3DXVECTOR3(HP_X_Right2 - hp[1].posX, HP_Y_Left2, 0.0f);
//		//pVtx[2].pos = D3DXVECTOR3(HP_X_Left2, HP_Y_Right2, 0.0f);
//		//pVtx[3].pos = D3DXVECTOR3(HP_X_Right2 - hp[1].posX, HP_Y_Right2, 0.0f);
//
//
//		//pVtx[0].rhw = 1.0f;												//座標変換用係数
//		//pVtx[1].rhw = 1.0f;
//		//pVtx[2].rhw = 1.0f;
//		//pVtx[3].rhw = 1.0f;
//
//		//pVtx[0].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);				//頂点カラー（Ｒ，Ｇ，Ｂ，Ａ）
//		//pVtx[1].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		//pVtx[2].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		//pVtx[3].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//
//		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);							//テクスチャのＵＶ座標（Ｕ，Ｖ）
//		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		//m_VertexBuffer->Unlock();              //ロックの解除
//
//	}
//
//		m_pHPbar->UpdateAll();
//
//}
//
//
///******************************************************************************
//**	関数名: 描画処理 Draw
//**		関数の概要
//**	引数  : void
//**	戻り値: void
//**	説明  :
//******************************************************************************/
//void HPbar::Draw()
//{
//
//	cntID2++;
//	if (cntID2 == 1)
//	{
//		m_ID = ID_0;
//	}
//	else
//	{
//		cntID2 = 0;
//		m_ID = ID_1;
//	}
//
//
//	/* マトリックス処理 */
//	// プロジェクション
//	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
//	glLoadIdentity();
//	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);
//
//	// モデルビュー
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glLoadIdentity();
//
//
//	/* 四角形描画 */
//	//// テクスチャ
//	//glEnable(GL_TEXTURE_2D);
//	//glBindTexture(GL_TEXTURE_2D, m_Texture);
//
//	// アルファブレンド設定
//	glEnable(GL_BLEND);
//	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDisable(GL_DEPTH_TEST);
//
//	// ライトの無効化
//	glDisable(GL_LIGHTING);
//
//
//	glBegin(GL_TRIANGLE_STRIP);
//
//	if (m_ID == 0)
//	{
//		glColor4f(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2d(HP_X_Left + hp[0].posX, HP_Y_Left);
//
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2d(HP_X_Right, HP_Y_Left);
//
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2d(HP_X_Left + hp[0].posX, HP_Y_Right);
//
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2d(HP_X_Right, HP_Y_Right);
//	}
//	else if (m_ID == 1)
//	{
//	/*	glColor4f(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2d(HP_X_Left2, HP_Y_Left2);
//
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2d(HP_X_Right2 - hp[1].posX, HP_Y_Left2);
//
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2d(HP_X_Left2, HP_Y_Right2);
//
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2d(HP_X_Right2 - hp[1].posX, HP_Y_Right2);*/
//	}
//
//	glEnd();
//
//	/*glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);*/
//	glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
//
//	/* マトリックスを元に戻す */
//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();
//
//	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();
//
//	m_pHPbar->DrawAll();
//
//}
//
///******************************************************************************
//**	関数名: Create
//**		関数の概要
//**	引数  : void
//**	戻り値: HPbarFrame *
//**	説明  : 生成成功時 Scene2Dポインタ、失敗時 NULL
//******************************************************************************/
//HPbar *HPbar::Create()
//{
//	HPbar *p;
//	p = new HPbar;
//	p->Init();
//	return p;
//}
//
//

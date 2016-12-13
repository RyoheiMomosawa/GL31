/******************************************************************************
**	タイトル  :
**	ファイル名: Object2D.cpp
**	作成者    : AT-13B-284 出席番号 38 桃澤諒平
**	作成日    : 2016/11/21
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**
******************************************************************************/


/******************************************************************************
インクルードファイル
******************************************************************************/
#include "main.h"
#include "Manager.h"
#include "RendererGL.h"

#include "Scene2DGL.h"
#include "ImageTGA.h"

#include "Object2D.h"


/******************************************************************************
**	マクロ定義
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//	静的変数
///////////////////////////////////////////////////////////////////////////////
//	先頭アドレス
CObject2D *CObject2D::m_TopAddress = NULL;
//	現在アドレス
CObject2D *CObject2D::m_CurrentAddress = NULL;
// テクスチャ目録
int CObject2D::m_Texture[CObject2D::TEXTURE_INDEX_MAX] = { NULL };
// テクスチャパス
char *CObject2D::m_pTexPath[CObject2D::TEXTURE_INDEX_MAX] = { NULL };

/******************************************************************************
**	プロトタイプ宣言
******************************************************************************/


/******************************************************************************
**	グローバル変数
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//	関数名	: CObject2D::CObject2D()
//	戻り値	: なし
//	引数	: なし
//	説明	: コンストラクタ
//
///////////////////////////////////////////////////////////////////////////////
CObject2D::CObject2D()
{
	//	最初の時
	if (m_TopAddress == NULL)
	{
		//	トップアドレス更新
		m_TopAddress = this;
		//	現在のアドレス更新
		m_CurrentAddress = this;
		//	前アドレス更新
		m_PreviousAddress = NULL;
		//	次のアドレス更新
		m_NextAddress = NULL;
	}
	//	最初の時以外
	else
	{
		//	現在アドレスの前アドレスの次アドレスに現在アドレスを代入
		m_CurrentAddress->m_NextAddress = this;
		//	前アドレス更新
		m_PreviousAddress = m_CurrentAddress;
		//	現在のアドレス更新
		m_CurrentAddress = this;
		//	次のアドレス更新
		m_NextAddress = NULL;
	}
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: CObject2D::~CObject2D()
//	戻り値	: なし
//	引数	: なし
//	説明	: デストラクタ
//
///////////////////////////////////////////////////////////////////////////////
CObject2D::~CObject2D()
{
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: CObject2D *CObject2D::Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture )
//	戻り値	: CObject2Dのポインタ
//	引数	: 座標, サイズ, テクスチャ目録
//	説明	: 2Dポリゴンの作成
//
///////////////////////////////////////////////////////////////////////////////
CObject2D *CObject2D::Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture )
{
	CObject2D *pObject2D = new CObject2D;
	pObject2D->Init(Position, Size, Texture);
	return pObject2D;
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture)
//	戻り値	: なし
//	引数	: 座標, サイズ, テクスチャ目録
//	説明	: 初期化
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture)
{
	// 代入
	m_Position = *Position;
	m_Size = *Size;
	m_UseTextureIndex = Texture;
	m_Rotation = Vector3(0.0f, 0.0f, 90.0f);
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::Uninit(void)
//	戻り値	: なし
//	引数	: なし
//	説明	: 終了処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Uninit(void)
{
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::UninitAll(void)
//	戻り値	: なし
//	引数	: なし
//	説明	: 全て終了処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::UninitAll(void)
{
	//	アドレスの入れ物
	CObject2D *Address = m_TopAddress;
	CObject2D *Address2 = NULL;

	while (Address != NULL)
	{
		//	アドレスの終了処理を行う
		Address->Uninit();
		//	アドレスの更新
		Address2 = Address->m_NextAddress;
		//	
		delete Address;
		//
		Address = Address2;
	}
	m_TopAddress = NULL;

	// テクスチャ解放
	for (int i = 0; i < TEXTURE_INDEX_MAX; i++)
	{
		if (m_Texture[i] != NULL)
		{
			glDeleteTextures(GL_TEXTURE_2D, (unsigned int *)&m_Texture[i]);
			m_Texture[i] = NULL;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::Update(void)
//	戻り値	: なし
//	引数	: なし
//	説明	: 更新処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Update(void)
{

}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::UpdateAll(void)
//	戻り値	: なし
//	引数	: なし
//	説明	: 全て更新処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::UpdateAll(void)
{
	if (m_TopAddress != NULL)
	{
		//	アドレスの入れ物
		CObject2D *Address = m_TopAddress;
		CObject2D *Address2 = m_TopAddress->m_NextAddress;

		while (Address != NULL)
		{
			Address2 = Address->m_NextAddress;
			//	アドレスの更新処理を行う
			Address->Update();

			//	アドレスの更新
			Address = Address2;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::Draw(void) 
//	戻り値	: なし
//	引数	: なし
//	説明	: 描画処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::Draw(void) 
{
	////////////////////////////////////////////////////////////
	// プロジェクションマトリクス
	////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);		// プロジェクションマトリクス設定宣言
	glPushMatrix();						// 情報の退避
	glLoadIdentity();					// マトリクスクリア
	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);

	/////////////////////////////////////////////////////////////
	//	モデルビューマトリクス
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);		// モデルビューマトリクス設定宣言
	glPushMatrix();						// 情報の退避
	glLoadIdentity();					// マトリクス退避


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture[m_UseTextureIndex]);


	// アルファブレンド設定
	glEnable(GL_BLEND);
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// ライトの無効化
	glDisable(GL_LIGHTING);

	// 移動
	glTranslated(m_Position.x, m_Position.y, m_Position.z);
	// 回転
	glRotatef(m_Rotation.x, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.y, 0.0, 1.0, 0.0);
	glRotatef(m_Rotation.z, 0.0, 0.0, 1.0);

	/////////////////////////////////////////////////////////////
	//	ポリゴン描画
	/////////////////////////////////////////////////////////////
	// 描画ここから
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0xff, 0xff, 0xff, 0x01);	// 色

	glTexCoord2f(0.0f, 0.0f);
	glVertex2d(  -m_Size.x/2.0f, m_Size.y/2.0f);		// 座標

	glTexCoord2f(1.0f, 0.0f);
	glVertex2d(	 m_Size.x / 2.0f, m_Size.y / 2.0f);	// 座標

	glTexCoord2f(0.0f, 1.0f);
	glVertex2d( -m_Size.x / 2.0f, -m_Size.y / 2.0f);	// 座標

	glTexCoord2f(1.0f, 1.0f);
	glVertex2d( m_Size.x / 2.0f, -m_Size.y / 2.0f);	// 座標

	// 描画ここまで
	glEnd();


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	/////////////////////////////////////////////////////////////
	//	プロジェクションマトリクス設定を戻す
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	/////////////////////////////////////////////////////////////
	//	モデルビューマトリクス設定を戻す
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::DrawAll(void)
//	戻り値	: なし
//	引数	: なし
//	説明	: 全て描画処理
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::DrawAll(void)
{
	if (m_TopAddress != NULL)
	{
		//	アドレスの入れ物
		CObject2D *Address = m_TopAddress;

		while (Address != NULL)
		{
			//	アドレスの描画処理を行う
			Address->Draw();
			//	アドレスの更新
			Address = Address->m_NextAddress;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: bool CObject2D::WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index)
//	戻り値	: true, false
//	引数	: ファイルパス, テクスチャ目録
//	説明	: テクスチャ目録にデータを書き込み
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index)
{
	// テクスチャ設定
	if (m_Texture[Index] == NULL)
	{
		ImageTGA cTexture;
		m_Texture[Index] = cTexture.CreateTexture(pFilePath);
	}
	// データが入っている場合は削除してから読み込む
	else
	{
		glDeleteTextures(GL_TEXTURE_2D, (unsigned int *)&m_Texture[Index]);
		m_Texture[Index] = NULL;
		ImageTGA cTexture;
		m_Texture[Index] = cTexture.CreateTexture(pFilePath);
	}

	// ファイルがあるかどうか調べる
	if (m_Texture[Index]!= NULL)
	{
		m_pTexPath[Index] = (char *)pFilePath;
		return true;
	}
	else
	{
		// 無い場合はfalseを返す
		m_pTexPath[Index] = NULL;
		m_Texture[Index] = NULL;
		return false;
	}

}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: bool CObject2D::CollisionDetection(Vector3 *Position)
//	戻り値	: 当たり true, 当ってない false
//	引数	: 当たり判定する座標
//	説明	: 指定した座標の四角形の当たり判定
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::CollisionDetection(Vector3 *Position)
{
	
	VECTOR3 CheckPos = *Position;		// チェックする座標
	if ((m_Position.x - m_Size.x/2.0f <= CheckPos.x) && (m_Position.x + m_Size.x/2.0f >= CheckPos.x) &&
		(m_Position.y - m_Size.y/2.0f <= CheckPos.y) && (m_Position.y + m_Size.y/2.0f >= CheckPos.y))
	{
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: SphereAndSphereDetection
//	戻り値	: 当たり true, 当ってない false
//	引数	: Objct1の座標とサイズ、Objct2の座標とサイズ
//	説明	: 球と球の当たり判定
//
///////////////////////////////////////////////////////////////////////////////
bool CObject2D::SphereAndSphereDetection(Vector3 PositionObj1, Vector3 SizeObj1, Vector3 PositionObj2, Vector3 SizeObj2)
{
	float f_Length1, f_Length2;
	float f_Distance;

	// Obj1の半径の長さ
	f_Length1 = sqrtf(((SizeObj1.x / 2.0f)*(SizeObj1.x / 2.0f)) + ((SizeObj1.y / 2.0f)*(SizeObj1.y / 2.0f)));

	// Obj2の半径の長さ
	f_Length2 = sqrtf(((SizeObj2.x / 2.0f)*(SizeObj2.x / 2.0f)) + ((SizeObj2.y / 2.0f)*(SizeObj2.y / 2.0f)));

	// Obj1とObj2の距離
	f_Distance = sqrtf( (PositionObj1.x - PositionObj2.x)*(PositionObj1.x - PositionObj2.x)
						+ (PositionObj1.y - PositionObj2.y)*(PositionObj1.y - PositionObj2.y));

	// もしObj1とobj2の距離が\長さより短い場合
	if (f_Distance <= f_Length1 + f_Length2)
	{
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
//	関数名	: void CObject2D::SetParameter(Vector3 *parameter)
//	戻り値	: なし
//	引数	: パラメーターのタイプ, パラメーター
//	説明	: パラメーターの変更をする。
//
///////////////////////////////////////////////////////////////////////////////
void CObject2D::SetParameter(PARAMETER_TYPE type, Vector3 *parameter)
{
	switch (type)
	{
	case POSITION:	// 座標
		{
			m_Position = *parameter;
			break;
		}
		case ROTATION:	// 回転
		{
			m_Rotation = *parameter;
			break;
		}
		case SIZE:	// サイズ
		{
			m_Size = *parameter;
			break;
		}

	}
}
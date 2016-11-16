/******************************************************************************
**	タイトル  :
**	ファイル名: Scene2DL.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/2/22
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "Scene2DGL.h"
#include "main.h"
#include "ImageTGA.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Scene2DGL::Scene2DGL( int Priority ) : SceneGL( Priority )
{
}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Scene2DGL::~Scene2DGL()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  : void
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT Scene2DGL::Init()
{

	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int Scene2DGL::Uninit()
{

	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Scene2DGL::Update()
{
}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Scene2DGL::Draw()
{
	// エラー回避
	if( m_Texture == EOF )
	{
		return;

	}

	/* マトリックス処理 */
	// プロジェクション
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0.0, ( GLdouble )SCREEN_WIDTH, ( GLdouble )SCREEN_HEIGHT, 0.0, 0.0, 1.0 );

	// モデルビュー
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();


	/* 四角形描画 */
	// テクスチャ
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Texture );

	// アルファブレンド設定
	glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_DEPTH_TEST );

	// ライトの無効化
	glDisable( GL_LIGHTING );


	glBegin( GL_TRIANGLE_STRIP );

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d( m_Obj3d.pos.x - m_Obj3d.width * 0.5f, m_Obj3d.pos.y + m_Obj3d.height * 0.5f );
	
	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( m_Obj3d.pos.x + m_Obj3d.width * 0.5f, m_Obj3d.pos.y + m_Obj3d.height * 0.5f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d( m_Obj3d.pos.x - m_Obj3d.width * 0.5f, m_Obj3d.pos.y - m_Obj3d.height * 0.5f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( m_Obj3d.pos.x + m_Obj3d.width * 0.5f, m_Obj3d.pos.y - m_Obj3d.height * 0.5f );

	glEnd();

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );

	/* マトリックスを元に戻す */
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

}


/******************************************************************************
**	関数名: Create
**		関数の概要
**	引数  : void
**	戻り値: Scene2DGL *
**	説明  : 生成成功時 Scene2Dポインタ、失敗時 NULL
******************************************************************************/
Scene2DGL *Scene2DGL::Create()
{
	Scene2DGL *p;
	p = new Scene2DGL;

	if FAILED( p->Init() )
	{
		delete p;
		return NULL;

	}

	else return p;

}



/******************************************************************************
**	タイトル  :
**	ファイル名: .cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016//
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "SceneGL.h"

// オブジェクト


// システム
#include "ImageTGA.h"
#include "main.h"
#include <Windows.h>


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
DWORD SceneGL::m_dwCreateCnt = 0;
SceneGL *SceneGL::m_Top[ PRIORITY_MAX ] = {};
SceneGL *SceneGL::m_Last[ PRIORITY_MAX ] = {};


/******************************************************************************
**	関数名:　SceneGL
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
SceneGL::SceneGL( int Priority )
{
	// 初期化
	ZeroMemory( &m_Obj3d, sizeof OBJECT3D );
	m_Obj3d.pos = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.accPos = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.rot = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.scl = Vector3( 1.0f, 1.0f, 1.0f );
	m_Obj3d.normal = Vector3( 0.0f, 1.0f, 0.0f );
	m_Obj3d.col = Color( 1.0f, 1.0f, 1.0f, 1.0f );
	m_Obj3d.width = 0.0f;
	m_Obj3d.height = 0.0f;
	m_Obj3d.depth = 0.0f;
	m_Obj3d.length2D = m_Obj3d.length3D = 0.0f;
	m_Obj3d.bUse = m_Obj3d.bUpdate = m_Obj3d.bDraw = false;
	m_Obj3d.anim.fPattern_X = m_Obj3d.anim.fPattern_Y = 1.0f;
	m_Obj3d.anim.fAnimWidth = m_Obj3d.anim.fAnimHeight = 1.0f;
	m_Obj3d.anim.nChangeTimming = 1;

	m_Obj3d.movestate = MOVESTATE_NONE;
	m_bCreate = false;
	m_pTexPath = NULL;
	m_Texture = EOF;

	// リスト登録
	if( m_Top[ Priority ] == NULL )
	{
		// 初期設定
		m_Top[ Priority ] = m_Last[ Priority ] = this;
		m_Prev = m_Next = NULL;

	}
	else
	{
		m_Prev = m_Last[ Priority ]; // 自分の前ポインタに最後のポインタを代入
		m_Last[ Priority ] = m_Last[ Priority ]->m_Next = this; // 後尾ポインタと前データ->ポインタに自分のポインタを代入
		m_Next = NULL;

	}

	// 生成したらカウント
	m_dwCreateCnt++;

}


/******************************************************************************
**	関数名: ~SceneGL
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
SceneGL::~SceneGL()
{
	if( this != NULL )
	{
		m_dwCreateCnt--;
		this->DeleteTexture();

	}
	else
	{
		// NULLを削除しようとしたら終了する
		MessageBox( GetHWND(), "参照された値がNULLでした", "注意!", MB_OK | MB_ICONERROR );
		PostQuitMessage( 0 );

	}

}


/******************************************************************************
**	関数名: InitAll
**	関数の概要
**	引数  : void
**	戻り値: HRESULT
**	説明  :
******************************************************************************/
HRESULT SceneGL::InitAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];

		while( scene != NULL )
		{
			scene->Init();
			scene = scene->m_Next;

		}

	}

	return S_OK;

}


/******************************************************************************
**	関数名: UninitAll
**	関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int SceneGL::UninitAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];
		SceneGL *next;

		while( scene != NULL )
		{
			next = scene->m_Next;
			scene->Uninit();
			scene->DeleteTexture();
			delete scene;
			scene = next;

		}

		scene = NULL;
		m_Top[ i ] = NULL;
		m_Last[ i ] = NULL;

	}


	return 0;

}


/******************************************************************************
**	関数名: UpdateAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::UpdateAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];
		SceneGL *next;

		while( scene != NULL )
		{
			next = scene->m_Next;
			scene->GetObject3D()->bUse && scene->GetObject3D()->bUpdate ? scene->Update() : false;
			scene = next;

		}

	}


}


/******************************************************************************
**	関数名: DrawAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::DrawAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];

		while( scene != NULL )
		{
			scene->GetObject3D()->bUse && scene->GetObject3D()->bUpdate ? scene->Draw() : false;
			scene = scene->m_Next;

		}

	}

}


/******************************************************************************
**	関数名: Release
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::Release()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		if( this == m_Top[ i ] )
		{
			m_Top[ i ] = m_Next;
			m_Next->m_Prev = NULL;

		}
		else if( this == m_Last[ i ] )
		{
			m_Last[ i ] = m_Prev;
			m_Prev->m_Next = NULL;

		}
		else
		{
			m_Prev->m_Next = m_Next;
			m_Next->m_Prev = m_Prev;

		}

	}

	delete this;

}


/******************************************************************************
**	関数名: GetObject3D
**	関数の概要
**	引数  : void
**	戻り値: OBJECT3D
**	説明  :
******************************************************************************/
OBJECT3D* SceneGL::GetObject3D()
{
	return &this->m_Obj3d;

}


/******************************************************************************
**	関数名: SetObject3D
**	関数の概要
**	引数  : OBJECT3D
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::SetObject3D( OBJECT3D obj3d )
{
	this->m_Obj3d = obj3d;

}


/******************************************************************************
**	関数名: SetTexture
**		関数の概要
**	引数  : const char *
**	戻り値: bool
**	説明  :
******************************************************************************/
bool SceneGL::SetTexture( const char *pFilePath )
{
	// テクスチャ設定
	if( m_Texture == EOF )
	{
		ImageTGA cTexture;
		m_Texture = cTexture.CreateTexture( pFilePath );

	}
	// データが入っている場合は削除してから読み込む
	else
	{
		DeleteTexture();
		ImageTGA cTexture;
		m_Texture = cTexture.CreateTexture( pFilePath );

	}

	// ファイルがあるかどうか調べる
	if( m_Texture != NULL )
	{
		m_pTexPath = ( char * )pFilePath;
		return true;

	}
	else
	{
		// 無い場合はfalseを返す
		m_pTexPath = NULL;
		m_Texture = EOF;
		return false;

	}

}


/******************************************************************************
**	関数名: SetParam
**	関数の概要
**	引数  : float *x, float *y, float *z, SCENEPARAM ParamName
**	戻り値: void
**	説明  : SIZEの場合、x = width, y = height, z = depth となる
******************************************************************************/
void SceneGL::SetParam( float *x, float *y, float *z, SCENEPARAM ParamName )
{
	switch( ParamName )
	{
		// vecがNULL時には処理をしない
		case SCENEPARAM_POS:
			m_Obj3d.pos.x = x == NULL ? m_Obj3d.pos.x : *x;
			m_Obj3d.pos.y = y == NULL ? m_Obj3d.pos.y : *y;
			m_Obj3d.pos.z = z == NULL ? m_Obj3d.pos.z : *z;

			break;

		case SCENEPARAM_ROT:
			m_Obj3d.rot.x = x == NULL ? m_Obj3d.rot.x : *x;
			m_Obj3d.rot.y = y == NULL ? m_Obj3d.rot.y : *y;
			m_Obj3d.rot.z = z == NULL ? m_Obj3d.rot.z : *z;

			break;

		case SCENEPARAM_SCL:
			m_Obj3d.scl.x = x == NULL ? m_Obj3d.scl.x : *x;
			m_Obj3d.scl.y = y == NULL ? m_Obj3d.scl.y : *y;
			m_Obj3d.scl.z = z == NULL ? m_Obj3d.scl.z : *z;

			break;

		case SCENEPARAM_SIZE:
			m_Obj3d.width = x == NULL ? m_Obj3d.width : *x;
			m_Obj3d.height = y == NULL ? m_Obj3d.height : *y;
			m_Obj3d.depth = z == NULL ? m_Obj3d.depth : *z;

			break;

		default:

			break;

	}

}


/******************************************************************************
**	関数名: SetParam
**	関数の概要
**	引数  : D3DXVECTOR3 *, SCENEPARAM ParamName
**	戻り値: void
**	説明  : SIZEの場合、x = width, y = height, z = depth となる
******************************************************************************/
void SceneGL::SetParam( Vector3 *vec, SCENEPARAM ParamName )
{
	// vecがNULL時には処理をしない
	if( vec == NULL ) return;

	switch( ParamName )
	{
		case SCENEPARAM_POS:
			m_Obj3d.pos = *vec;

			break;

		case SCENEPARAM_ROT:
			m_Obj3d.rot = *vec;

			break;

		case SCENEPARAM_SCL:
			m_Obj3d.scl = *vec;

			break;

		case SCENEPARAM_SIZE:
			m_Obj3d.width = vec->x;
			m_Obj3d.height = vec->y;
			m_Obj3d.depth = vec->z;

			break;

		default:

			break;

	}

}


/******************************************************************************
**	関数名: SetColor
**	関数の概要
**	引数  :  float *r, float *g, float *b, float *a
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::SetColor( float *r, float *g, float *b, float *a )
{
	m_Obj3d.col = Color(
		r == nullptr ? m_Obj3d.col.r : *r,
		g == nullptr ? m_Obj3d.col.g : *g,
		b == nullptr ? m_Obj3d.col.b : *b,
		a == nullptr ? m_Obj3d.col.a : *a );

}


/******************************************************************************
**	関数名: SetColor
**	関数の概要
**	引数  :  float *r, float *g, float *b, float *a
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::SetColor( Color *col )
{
	if( col == nullptr ) return;
	m_Obj3d.col = *col;

}


/******************************************************************************
**	関数名: SetAnimation
**	関数の概要
**	引数  : int ChangeTim, float PatternX, float PatternY
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::SetAnimation( int ChangeTim, float PatternX, float PatternY )
{
	m_Obj3d.anim.nChangeTimming = ChangeTim;
	m_Obj3d.anim.fPattern_X = PatternX;
	m_Obj3d.anim.fPattern_Y = PatternY;
	m_Obj3d.anim.fAnimWidth = 1.0f / ( m_Obj3d.anim.fPattern_X / m_Obj3d.anim.fPattern_Y );
	m_Obj3d.anim.fAnimHeight = 1.0f / m_Obj3d.anim.fPattern_Y;

}


/******************************************************************************
**	関数名: DeleteTexture
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGL::DeleteTexture()
{
	glDeleteTextures( GL_TEXTURE_2D, ( unsigned int * )&m_Texture );
	m_Texture = EOF;

}

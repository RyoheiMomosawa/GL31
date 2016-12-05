#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Scene.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/4/22
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "RendererGL.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/



/******************************************************************************
**	マクロ定義
******************************************************************************/

// シーンのデータ
typedef enum
{
	SCENEPARAM_POS = 0,
	SCENEPARAM_ROT,
	SCENEPARAM_SCL,
	SCENEPARAM_SIZE, // x = width, y = height, z = depth
	SCENEPARAM_MAX,

}SCENEPARAM;


// シーンの種類
typedef enum
{
	SCENETYPE_NONE = 0,
	SCENETYPE_2D,
	SCENETYPE_3D,
	SCENETYPE_MODEL,
	SCENETYPE_PLAYER,
	SCENETYPE_ENEMY,
	SCENETYPE_SPHIRE,
	SCENETYPE_MESHFIELD,
	SCENETYPE_MESHDOME,
	SCENETYPE_LIVE2D_2D,
	SCENETYPE_LIVE2D_3D,
	SCENETYPE_MAX

}SCENETYPE;


/* プライオリティ */
typedef enum
{
	PRIORITY_3D = 0,
	PRIORITY_MODEL,
	PRIORITY_LIVE2D,
	PRIORITY_2D,
	PRIORITY_MAX

}PRIORITY;


/******************************************************************************
**	クラス定義
******************************************************************************/
class SceneGL
{
	public:
	SceneGL( int Priority = 0 );
	virtual ~SceneGL();

	// メソッド
	virtual HRESULT Init() = 0;
	virtual int Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static HRESULT InitAll();
	static int UninitAll();
	static void UpdateAll();
	static void DrawAll();
	void Release();


	// get,set
	OBJECT3D* GetObject3D();
	void SetObject3D( OBJECT3D );
	bool SetTexture( const char *pFilePath );
	virtual void SetParam( float *x, float *y, float *z, SCENEPARAM ParamName );
	virtual void SetParam( Vector3 *, SCENEPARAM ParamName );
	void SetColor( float *r, float *g, float *b, float *a );
	void SetColor( Color * );
	void SetAnimation( int ChangeTim, float PatternX, float PatternY );


	// Delete
	void DeleteTexture();


protected:
	static DWORD m_dwCreateCnt; // 生成数
	static SceneGL *m_Top[ PRIORITY_MAX ]; // 先頭アドレス
	static SceneGL *m_Last[ PRIORITY_MAX ]; // 現在ポインタ
	SceneGL *m_Prev; // 前ポインタ
	SceneGL *m_Next; // 次ポインタ
	OBJECT3D m_Obj3d; // オブジェクト3D
	int m_Texture;
	char *m_pTexPath;
	bool m_bCreate;

};


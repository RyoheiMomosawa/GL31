#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Sprite.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/5/23
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
#include "Vector3.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/

/* インデックスバッファ */
typedef struct tagMESHDATA
{
	unsigned int nLabel; // 管理番号
	unsigned int *lpIdxBuff; // インデックスバッファの先頭アドレス
	unsigned long dIdxSize; // インデックス数
	Vector3 *pVtx; // 頂点情報
	//Vec2 *pVtxTex; // テクスチャ座標
	unsigned long dVtxSize; // 頂点数
	Vector3 *pNor; // 法線
	unsigned long dNorSize; // 法線数
	int NorFormat;

}MESHDATA, *LPMESHDATA;


/******************************************************************************
**	名前空間定義
******************************************************************************/
namespace SpriteLib
{
	/* メッシュデータ */
	static LPMESHDATA g_lpMeshData = NULL;

	/* メッシュデータの数 */
	static unsigned g_lMeshDataNum = 0;

	/* インデックスバッファ関連 */
	void CreateIndexBuffer( unsigned int *nLabel, unsigned int *lpIdxBuff, unsigned long size );
	bool CreateVtxBuffer( unsigned int nLabel, Vector3 *pVtx, unsigned long size );
	bool CreateNorBuffer( unsigned int nLabel, Vector3 *pNor, unsigned long size, int format );
	//bool CreateVtxTexture( unsigned int nLabel, Vec2 *pVexTexture );
	void DrawIndex( unsigned int nLabel );
	void DrawIndex( unsigned int nLabel, Vector3 *pos );
	void DeleteIndex( void );

}

/******************************************************************************
**	タイトル  :
**	ファイル名: Sprite.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/5/23
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "Sprite.h"
#include "RendererGL.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/


/******************************************************************************
**	インデックスバッファのセット
**
**	使用方法
**	unsigned int nLabel・・・管理番号格納先アドレス 描画字にこの番号を指定することで描画できる
**	void lpIdxBuff・・・インデックスを格納している配列の先頭ポインタ
**	unsigned long size・・・インデックスの個数、大きさ
******************************************************************************/
void SpriteLib::CreateIndexBuffer( unsigned int *nLabel, unsigned int *lpIdxBuff, unsigned long size )
{
	/* インデックスバッファの保存領域生成 */
	// データが1つもなかったら生成した後にそのまま引数をコピー
	*nLabel = g_lMeshDataNum;
	if( g_lMeshDataNum == 0 )
	{
		// メッシュデータ生成
		g_lpMeshData = new MESHDATA;

		// 引数のデータをコピー
		g_lpMeshData[ 0 ].nLabel = *nLabel;
		g_lpMeshData[ 0 ].lpIdxBuff = lpIdxBuff;
		g_lpMeshData[ 0 ].dIdxSize = size;

		// 登録数カウントアップ
		g_lMeshDataNum++;

	}
	else if( g_lMeshDataNum > 0 )
	{
		// 作業領域の確保 コピー領域
		LPMESHDATA lpMeshData = new MESHDATA[ g_lMeshDataNum ];

		// 登録数カウントアップ
		g_lMeshDataNum++;

		// 元のデータをコピーした後にデータを挿入する
		for( unsigned long nCntMesh = 0; nCntMesh < g_lMeshDataNum - 1; nCntMesh++ )
		{
			lpMeshData[ nCntMesh ] = g_lpMeshData[ nCntMesh ];

		}

		// データを削除後、新たに生成
		delete[] g_lpMeshData;
		g_lpMeshData = new MESHDATA[ g_lMeshDataNum ];

		// 元データを移し変え
		for( unsigned long nCntMesh = 0; nCntMesh < g_lMeshDataNum - 1; nCntMesh++ )
		{
			g_lpMeshData[ nCntMesh ] = lpMeshData[ nCntMesh ];

		}

		// 新しいデータを挿入
		g_lpMeshData[ g_lMeshDataNum - 1 ].nLabel = *nLabel;
		g_lpMeshData[ g_lMeshDataNum - 1 ].lpIdxBuff = lpIdxBuff;
		g_lpMeshData[ g_lMeshDataNum - 1 ].dIdxSize = size;

		// 作業領域を削除
		delete[] lpMeshData;

	}

}


/******************************************************************************
**	頂点バッファの登録
**
**	使用方法
**	unsigned int nLabel・・・変更したい管理番号
**	Vector3 *pVtx・・・頂点情報を格納している配列の先頭ポインタ
**	unsigned long size・・・頂点数
******************************************************************************/
bool SpriteLib::CreateVtxBuffer( unsigned int nLabel, Vector3 *pVtx, unsigned long size )
{
	// 管理番号の検索
	for( unsigned long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
	{
		// 該当の管理番号があったらコピー処理をする
		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
		{
			g_lpMeshData[ nCntLabel ].pVtx = pVtx;
			g_lpMeshData[ nCntLabel ].dVtxSize = size;

			// コピーに成功したらtrueを返す
			return true;

		}

	}

	// 該当の管理番号がなかったらfalseを返す
	return false;

}


/******************************************************************************
**	法線バッファの登録
**
**	使用方法
**	unsigned int nLabel・・・変更したい管理番号
**	Vector3 *pVtx・・・頂点情報を格納している配列の先頭ポインタ
**	unsigned long size・・・法線数
******************************************************************************/
bool SpriteLib::CreateNorBuffer( unsigned int nLabel, Vector3 *pNor, unsigned long size, int format )
{
	// 管理番号の検索
	for( unsigned long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
	{
		// 該当の管理番号があったらコピー処理をする
		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
		{
			g_lpMeshData[ nCntLabel ].pNor = pNor;
			g_lpMeshData[ nCntLabel ].dNorSize = size;
			g_lpMeshData[ nCntLabel ].NorFormat = format;

			// コピーに成功したらtrueを返す
			return true;

		}

	}

	// 該当の管理番号がなかったらfalseを返す
	return false;

}


/******************************************************************************
**	テクスチャ座標の登録
**
**	使用方法
**	unsigned int nLabel・・・変更したい管理番号
**	Vec2 *pVexTexture・・・テクスチャ座標を格納している配列の先頭ポインタ
******************************************************************************/
//bool SpriteLib::CreateVtxTexture( unsigned int nLabel, Vec2 *pVexTexture )
//{
//	// 管理番号の検索
//	for( long nCntLabel = 0; nCntLabel < g_lMeshDataNum; nCntLabel++ )
//	{
//		// 該当の管理番号があったらコピー処理をする
//		if( g_lpMeshData[ nCntLabel ].nLabel == nLabel )
//		{
//			g_lpMeshData[ nCntLabel ].pVtxTex = pVexTexture;
//
//			// コピーに成功したらtrueを返す
//			return true;
//
//		}
//
//	}
//
//	// 該当の管理番号がなかったらfalseを返す
//	return false;
//
//}


/******************************************************************************
**	メッシュフィールドの描画(ポジション一定位置)
**
**	使用方法
**	unsigned int nLabel・・・描画したい管理番号
******************************************************************************/
void SpriteLib::DrawIndex( unsigned int nLabel )
{
	// モデルビューの退避
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	/* マトリックス処理 */


	/* 描画開始 */
	unsigned int *p = g_lpMeshData[ nLabel ].lpIdxBuff;
	glBegin( GL_TRIANGLE_STRIP );
	int NorFmtCnt = -1;
	for( unsigned int nCntDraw = 0; nCntDraw < g_lpMeshData[ nLabel ].dIdxSize; nCntDraw++ )
	{
		// 法線設定
		NorFmtCnt += 0 + ( nCntDraw % g_lpMeshData[ nLabel ].NorFormat == 0 );
		glNormal3f(
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].x,
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].y,
			g_lpMeshData[ nLabel ].pNor[ NorFmtCnt ].z );

		// 色設定
		glColor4f( 1.0f, 1.0f, 0.2f, 1.0f );

		// 座標設定
		glVertex3d(
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].x,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].y,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].z );

	}
	glEnd();


	/* マトリックスを元に戻す */
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

}


/******************************************************************************
**	メッシュフィールドの描画(ポジション可変可能)
**
**	使用方法
**	unsigned int nLabel・・・描画したい管理番号
**	Vec pos・・・描画位置
******************************************************************************/
void SpriteLib::DrawIndex( unsigned int nLabel, Vector3 *pos )
{
	/* 描画開始 */
	unsigned int *p = g_lpMeshData[ nLabel ].lpIdxBuff;
	glBegin( GL_TRIANGLE_STRIP );
	glColor4f( 1.0f, 1.0f, 0.2f, 1.0f );
	int NorFmtCnt = 0;
	for( unsigned int nCntDraw = 0; nCntDraw < g_lpMeshData[ nLabel ].dIdxSize; nCntDraw++ )
	{
		// 法線設定
		NorFmtCnt += ( g_lpMeshData[ nLabel ].NorFormat % nCntDraw == 0 );
		glNormal3f(
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].x,
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].y,
			g_lpMeshData[ nLabel ].pNor[ p[ NorFmtCnt ] ].z );

		// 座標設定
		glVertex3d(
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].x + pos->x,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].y + pos->y,
			g_lpMeshData[ nLabel ].pVtx[ p[ nCntDraw ] ].z + pos->z );

	}
	glEnd();

}


/******************************************************************************
**	削除関数
**
******************************************************************************/
void SpriteLib::DeleteIndex( void )
{
	// データがある場合は削除
	if( g_lpMeshData != NULL )
	{
		delete[] g_lpMeshData;
	}

	// アドレス参照されないようNULLを挿入
	g_lpMeshData = NULL;
	g_lMeshDataNum = 0;

}
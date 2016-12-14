#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Object2D.h
**	作成者    : AT-13B-284 出席番号 38 桃澤諒平
**	作成日    : 2016/11/21
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**	
**		
**		
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/



/******************************************************************************
**	クラス定義
******************************************************************************/
class CObject2D
{
	public :
		///////////////////////////////////////////////////////////////////////////
		// テクスチャ目録
		///////////////////////////////////////////////////////////////////////////
			typedef enum
			{
				TEXTURE_INDEX_0 = 0,
				TEXTURE_INDEX_1,
				TEXTURE_INDEX_MAX		// テクスチャ目録最大数
			}TEXTURE_INDEX;	// テクスチャ目録
		///////////////////////////////////////////////////////////////////////////
		// パラメータータイプ 
		///////////////////////////////////////////////////////////////////////////
			typedef enum
			{
				POSITION = 0,			// 座標
				ROTATION,				// 回転
				SIZE,					// サイズ
				PARAMETER_TPEY_MAX_NUM	// パラメータータイプ最大数
			}PARAMETER_TYPE; 

		CObject2D();	// コンストラクタ
		~CObject2D();	// デストラクタ

		// テクスチャ目録にデータを書き込み
		static bool WritingTextureIndex(const char *pFilePath, TEXTURE_INDEX Index);
		// 作成
		static CObject2D *Create(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture);

		// 初期化
		void Init(Vector3 *Position, Vector3 *Size, TEXTURE_INDEX Texture);
		// 終了処理
		void Uninit(void);
		// 更新処理
		void Update(void);
		// 描画処理
		void Draw(void);

		// 全て終了処理
		static void UninitAll(void);
		// 全て更新処理
		static void UpdateAll(void);
		// 全て描画処理
		static void DrawAll(void);

		//////////////////////////////////////////////////////////////////////////////
		//	当たり判定
		//////////////////////////////////////////////////////////////////////////////
			// 指定した座標の四角形の当たり判定
			bool CollisionDetection( Vector3 *Position );
			// 球と球の当たり判定
			bool SphereAndSphereDetection(Vector3 PositionObj1, Vector3 SizeObj1, Vector3 PositionObj2, Vector3 SizeObj2);
			// 
			VECTOR3 ReturnVector(Vector3 Position, Vector3 PositionOld);

		//////////////////////////////////////////////////////////////////////////////
		//	パラメーター設定
		//////////////////////////////////////////////////////////////////////////////
			// パラメーター設定
			void SetParameter( PARAMETER_TYPE type, Vector3 *parameter);
			// パラメーター取得
			VECTOR3 GetParameter(PARAMETER_TYPE type);

	private:
		static CObject2D *m_TopAddress;		// 先頭アドレス
		static CObject2D *m_CurrentAddress;	// 現在アドレス
		CObject2D *m_PreviousAddress;		// 前アドレス
		CObject2D *m_NextAddress;			// 次アドレス

		VECTOR3 m_Position;					// 座標
		VECTOR3 m_Rotation;					// 回転
		VECTOR3 m_Size;						// サイズ

		TEXTURE_INDEX m_UseTextureIndex;			// 使うテクスチャ目録
		static char *m_pTexPath[TEXTURE_INDEX_MAX];	// テクスチャパス
		static int m_Texture[TEXTURE_INDEX_MAX];	// テクスチャ
};

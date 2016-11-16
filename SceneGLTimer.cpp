/******************************************************************************
**	タイトル  :
**	ファイル名: SceneTimer.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/22
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "SceneGLTimer.h"
#include "Manager.h"


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
SceneGLTimer::SceneGLTimer( int Priority ) : SceneGL( Priority )
{
	m_pNumber = NULL;
	m_Time = 0;
	m_nDigit = 0;
	
}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
SceneGLTimer::~SceneGLTimer()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT SceneGLTimer::Init()
{
	// 生成済みなら処理しない
	if( m_bCreate ) return S_OK;

	int time = m_Time;
	int digit;


	// 高解像度タイマーの初期化
	if( FAILED( m_QPCntr.Init() ) )
	{
		// 初期化に失敗
		return E_FAIL;

	}
	m_QPCntr.SetTimmerMs( 60, CHECKMETHOD_REPETITION );



	// 生成済み
	m_bCreate = true;


	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int SceneGLTimer::Uninit()
{
	for( int i = 0; i < m_nDigit; i++ )
	{
		m_pNumber[ i ].Uninit();

	}
	delete[] m_pNumber;

	m_QPCntr.ResetTimmer();
	m_Time = 0;

	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGLTimer::Update()
{
	int time = m_Time;
	int s;

	// タイマーオン
	if( m_QPCntr.c_bRanTimmer == false )
	{
		m_QPCntr.StartTimmer();

	}

	// タイマーが「0」になったらストップ
	if( m_Time <= 0 )
	{
		m_QPCntr.StopTimmer();

	}

#ifdef _DEBUG
	if( Manager::GetKeyboard()->GetRepeat( DIK_0 ) )
	{
		m_Time++;

	}
	else if( Manager::GetKeyboard()->GetRepeat( DIK_9 ) )
	{
		m_Time--;

	}

#endif // _DEBUG

	// タイマーの減算
	if( m_QPCntr.CheckTimmer() )
	{
		m_Time--;

	}

	// 数値のセット
	for( int i = 0; i < m_nDigit; i++ )
	{
		// 数値のセット
		s = powl( 10, ( m_nDigit - i - 1 ) );
		m_pNumber[ i ].SetNumber( time / s );
		time = time % s;
		m_pNumber[ i ].Update();

	}


}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGLTimer::Draw()
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

	// 数値の描画
	for( int i = 0; i < m_nDigit; i++ )
	{
		m_pNumber[ i ].Draw();

	}

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
**	関数の概要
**	引数  : void 
**	戻り値: SceneGLTimer *
**	説明  :
******************************************************************************/
SceneGLTimer *SceneGLTimer::Create()
{
	SceneGLTimer *p;
	p = new SceneGLTimer;

	if FAILED( p->Init() )
	{
		delete p;
		return NULL;

	}

	else return p;

}


/******************************************************************************
**	関数名: GetTimer
**	関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int SceneGLTimer::GetTimer()
{
	return m_Time;

}


/******************************************************************************
**	関数名: SetTimer
**	関数の概要
**	引数  : int time
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGLTimer::SetTimer( int time )
{
	m_Time = time;

}



/******************************************************************************
**	関数名: SetDigit
**	関数の概要
**	引数  : int num
**	戻り値: void
**	説明  :
******************************************************************************/
void SceneGLTimer::SetDigit( int num )
{
	m_nDigit = num;

}


/******************************************************************************
**	関数名: Reset
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
HRESULT SceneGLTimer::Reset()
{
	// タイマーが未生成なら生成する
	if( m_pNumber == NULL )
	{
		m_pNumber = new Number[ m_nDigit ];
		for( int i = 0; i < m_nDigit; i++ )
		{
			if( FAILED( m_pNumber[ i ].Init() ) )
			{
				return E_FAIL;

			}

		}

	}
	// 削除してから生成
	else
	{
		for( int i = 0; i < m_nDigit; i++ )
		{
			m_pNumber[ i ].Uninit();

		}
		delete[] m_pNumber;

		// 再生性
		m_pNumber = new Number[ m_nDigit ];
		for( int i = 0; i < m_nDigit; i++ )
		{
			if( FAILED( m_pNumber[ i ].Init() ) )
			{
				return E_FAIL;

			}

		}

	}


	// パラメータ準備
	int time = m_Time;
	int digit;
	float width = m_Obj3d.width * 0.5f;
	Vector3 pos;
	pos = m_Obj3d.pos;
	pos.x = m_Obj3d.pos.x - width * ( m_nDigit - 1 );
	for( int i = 0; i < m_nDigit; i++ )
	{
		// 各種パラメータ設定
		// 位置
		m_pNumber[ i ].SetPos( &pos );
		// 幅
		m_pNumber[ i ].SetSize( m_Obj3d.width, m_Obj3d.height );
		// 色
		m_pNumber[ i ].SetColor( &m_Obj3d.col );
		// 桁
		digit = powl( 10, ( m_nDigit - i - 1 ) );
		m_pNumber[ i ].SetNumber( time / digit );
		time = time % digit;

		// 次桁の位置更新
		pos.x += width * 2.0f;

	}


	return S_OK;

}

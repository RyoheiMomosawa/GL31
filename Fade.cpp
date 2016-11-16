/******************************************************************************
**	タイトル  :
**	ファイル名:  Fade.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/7/19
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "Fade.h"

// システム
#include "Mode.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "main.h"
#include "Manager.h"

// オブジェクト
#include "Color.h"


/******************************************************************************
**	マクロ定義
******************************************************************************/


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
unsigned int Fade::m_Texture;
Color Fade::m_color;
FADE Fade::m_fade;
Mode *Fade::m_pModeNext;
int Fade::m_FadeTimeCount;
float Fade::m_Width;
float Fade::m_Height;


/******************************************************************************
**	関数名: Fade
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Fade::Fade()
{
}


/******************************************************************************
**	関数名: ~Fade
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Fade::~Fade()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT Fade::Init()
{
	// フェード色・フェード・モード設定
	m_color = Color( FADE_R, FADE_G, FADE_B, FADE_A );
	m_fade = FADE_IN;

	// 各種パラメータ設定
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;


	// カウント
	m_FadeTimeCount = 0;


	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int Fade::Uninit()
{
	// 画像削除
	glDeleteTextures( GL_TEXTURE_2D, &m_Texture );
	
	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Fade::Update()
{
	/* フェードイン */
	if( m_fade == FADE_IN )
	{
		if( m_FadeTimeCount > 30 )
		{
			/* α値減算 */
			m_color.a -= 0.05f;

			// α値が0.0f以下でフェードノーンに切り替え
			if( m_color.a <= 0.0f )
			{
				m_fade = FADE_NONE;

				// α値の設定
				m_color.a = 0.0f;

			}

		}
		else
		{
			m_FadeTimeCount++;

		}

	}
	// フェードアウト
	else if( m_fade == FADE_OUT )
	{
		// α値加算
		m_color.a += 0.02f;

		// α値が1.0f以上になったら画面切り替え
		if( m_color.a >= 1.0f )
		{
			// α値を戻す
			m_color.a = 1.0f;

			// フェードイン
			m_fade = FADE_IN;

			// 画面遷移切り替え
			Manager::SetMode( m_pModeNext );

		}

	}

}


/******************************************************************************
**	関数名: 描画処理 Draw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Fade::Draw()
{
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

	glColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d( 0.0f, 0.0f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( m_Width, 0.0f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d( 0.0f, m_Height );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( m_Width, m_Height );

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
**	関数名: Set
**	関数の概要
**	引数  : Mode *next
**	戻り値: void
**	説明  :
******************************************************************************/
void Fade::Set( Mode *next )
{
	/* フェード・モードの切り替え */
	m_fade = FADE_OUT;
	m_pModeNext = next;
	m_FadeTimeCount = 0;

}


/******************************************************************************
**	関数名: Get
**	関数の概要
**	引数  : void
**	戻り値: FADE
**	説明  :
******************************************************************************/
FADE Fade::Get()
{
	return m_fade;

}

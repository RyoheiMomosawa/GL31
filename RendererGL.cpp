/******************************************************************************
**	タイトル  :
**	ファイル名: Renderer.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/4/22
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "RendererGL.h"


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
HDC RendererGL::m_hDC;
HGLRC RendererGL::m_hGLRC;
Color RendererGL::m_BgCol;


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
RendererGL::RendererGL()
{
}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
RendererGL::~RendererGL()
{
}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT RendererGL::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// デバイスコンテキストの取得
	m_hDC = GetDC( hWnd );

	// ピクセルフォーマット(OpenGLの初期データ)
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof PIXELFORMATDESCRIPTOR , // pfdのサイズ
		1 , // バージョン
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER , // 描画設定
		PFD_TYPE_RGBA , // 描画方法の色指定
		32 , // 色のバッファサイズ
		0 ,0 ,0 ,0 ,0, 0 ,0, 0, // RGBAのバッファサイズとシフト(?)
		0, 0, 0, 0, 0, // RGBA AccumBits
		24, // 奥行きバッファ
		8, // ステンシルバッファ
		0, // オーディオバッファ
		PFD_MAIN_PLANE, // レイヤータイプ
		0, // Reserved
		0, 0, 0 // レイヤー、ビジブル、ダメージ マスク

	};

	/* OpenGL Init */
	// ピクセル、カレントコンテクストの設定
	m_nFormat = ChoosePixelFormat( m_hDC, &pfd );
	if( m_nFormat == NULL )
	{
		// 0が帰ってきたらエラーを返す
		return E_FAIL;

	}
	if( !SetPixelFormat( m_hDC, m_nFormat, &pfd ) )
	{
		// セット失敗時にエラーを返す
		return E_FAIL;

	}
	m_hGLRC = wglCreateContext( m_hDC );
	wglMakeCurrent( m_hDC, m_hGLRC );


	/* 奥行描画判定処理 */
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	

	/* 色 */
	m_BgCol = Color( BGCOLOR_R, BGCOLOR_G, BGCOLOR_B, BGCOLOR_A );


	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
int RendererGL::Uninit()
{
	// カレントコンテキストの無効化
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hGLRC );

	// DCを削除
	DeleteDC( m_hDC );


	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::Update()
{
}


/******************************************************************************
**	関数名: BeginDraw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
bool RendererGL::BeginDraw()
{
	/* 画面のクリア */
	glClearColor( m_BgCol.r, m_BgCol.g, m_BgCol.b, m_BgCol.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	wglMakeCurrent( m_hDC, m_hGLRC );

	return true;

}


/******************************************************************************
**	関数名: EndDraw
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::EndDraw()
{
	// 描画処理
	glFlush();
	SwapBuffers( m_hDC );

}


/******************************************************************************
**	関数名: GetHDC
**	関数の概要
**	引数  : void
**	戻り値: HDC
**	説明  : デバイスコンテキストの取得
******************************************************************************/
HDC RendererGL::GetHDC()
{
	return m_hDC;
}


/******************************************************************************
**	関数名: GetHGLRC
**	関数の概要
**	引数  : void
**	戻り値: HGLRC
**	説明  : OpenGLのデバイスを取得
******************************************************************************/
HGLRC RendererGL::GetHGLRC()
{
	return m_hGLRC;
}


/******************************************************************************
**	関数名: SetRenderMode
**	関数の概要
**	引数  : GLRENDERSTATE glrs, DWORD value
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::SetRenderMode( GLRENDERSTATE glrs, DWORD value )
{
	DWORD set;

	switch( glrs )
	{
		case GLRS_FILLMODE:
			switch( value )
			{
				case GLFILL_POINT:
					set = GL_POINT;

					break;


				case GLFILL_WIREFRAME:
					set = GL_LINE;

					break;


				case GLFILL_SOLID:
					set = GL_FILL;

					break;


				default:
					
					break;


			}
			glPolygonMode( GL_FRONT_AND_BACK, set );

			break;


		default:
			
			break;


	}

}


/******************************************************************************
**	関数名: SetRenderMode
**	関数の概要
**	引数  : DWORD glrs, GLboolean value
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::SetRenderMode( DWORD glrs, GLboolean value )
{
}


/******************************************************************************
**	関数名: SetBgColor
**	関数の概要
**	引数  : float r, float g, float b, float a
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::SetBgColor( float r, float g, float b, float a )
{
	m_BgCol = Color( r, g, b, a );

}


/******************************************************************************
**	関数名: SetBgColor
**	関数の概要
**	引数  : Color *col
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::SetBgColor( Color *col )
{
	m_BgCol = *col;

}


/******************************************************************************
**	関数名: SetBgColor
**	関数の概要
**	引数  : unsigned long col
**	戻り値: void
**	説明  :
******************************************************************************/
void RendererGL::SetBgColor( unsigned long col )
{
	m_BgCol = col;

}


/******************************************************************************
**	関数名: GetBgColor
**	関数の概要
**	引数  : void
**	戻り値: Color
**	説明  :
******************************************************************************/
Color RendererGL::GetBgColor()
{
	return m_BgCol;

}





/******************************************************************************
**	タイトル  :
**	ファイル名: DIKeyboard.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/5/10
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "DIKeyboard.h"


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
input::DIKeyboard::DIKeyboard()
{
	// 初期化
	lpdid = NULL;
	m_State = NULL;
	m_StateTrigger = NULL;
	m_StateRelese = NULL;
	m_StateRepeat = NULL;
	m_StateRepeatCount = NULL;
	m_RepeatSpeed = 30;
	
	
	// 入力ワークのメモリ動的確保
	m_State = new BYTE[ 256 ];
	m_StateTrigger = new BYTE[ 256 ];
	m_StateRelese = new BYTE[ 256 ];
	m_StateRepeat = new BYTE[ 256 ];
	m_StateRepeatCount = new unsigned int[ 256 ];

	// ゼロクリア
	ZeroMemory( m_State, sizeof BYTE * 256 );
	ZeroMemory( m_StateTrigger, sizeof BYTE * 256 );
	ZeroMemory( m_StateRelese, sizeof BYTE * 256 );
	ZeroMemory( m_StateRepeat, sizeof BYTE * 256 );
	ZeroMemory( m_StateRepeatCount, sizeof( unsigned int ) * 256 );

}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
input::DIKeyboard::~DIKeyboard()
{
	// 入力ワークの解放
	delete[] m_State;
	m_State = NULL;

	delete[] m_StateTrigger;
	m_StateTrigger = NULL;

	delete[] m_StateRelese;
	m_StateRelese = NULL;

	delete[] m_StateRepeat;
	m_StateRepeat = NULL;

	delete[] m_StateRepeatCount;
	m_StateRepeatCount = NULL;

}


/******************************************************************************
**	関数名: 初期化処理 Init
**		関数の概要
**	引数  :
**	戻り値: HRESULT
**	説明  : 初期化処理
******************************************************************************/
HRESULT input::DIKeyboard::Init( HWND hWnd )
{
	/* デバイスの生成 */
	if( FAILED( Input::lpDirectInput->CreateDevice( GUID_SysKeyboard, &lpdid, NULL ) ) )
	{
		return E_FAIL;

	}

	/* データフォーマットの設定 */
	if( FAILED( lpdid->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return E_FAIL;

	}

	/* 協調モードの設定 */
	if( FAILED( lpdid->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return E_FAIL;

	}

	/* キーボードへのアクセス権取得 */
	lpdid->Acquire();

	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
int input::DIKeyboard::Uninit()
{
	if( lpdid != NULL )
	{
		/* キーボードのアクセス権解放 */
		lpdid->Unacquire();

		lpdid->Release();
		lpdid = NULL;

	}

	return 0;

}


/******************************************************************************
**	関数名: 更新処理 Update
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
HRESULT input::DIKeyboard::Update()
{
	/**** 変数宣言 ****/
	BYTE aKeyState[ 256 ]; // キーステータス


	// デバイスからデータを取得
	if( SUCCEEDED( lpdid->GetDeviceState( sizeof( aKeyState ), &aKeyState[ 0 ] ) ) )
	{
		/* 入力情報を代入 */
		for( int nCntKey = 0; nCntKey < 256; nCntKey++ )
		{
			m_StateTrigger[ nCntKey ] = aKeyState[ nCntKey ] ^ m_State[ nCntKey ] & aKeyState[ nCntKey ];
			m_StateRelese[ nCntKey ] = m_State[ nCntKey ] ^ aKeyState[ nCntKey ] & m_State[ nCntKey ];
			m_State[ nCntKey ] = m_StateRepeat[ nCntKey ] = aKeyState[ nCntKey ];

		}

	}
	/* アクセス権がなかったら再取得 */
	else
	{
		return lpdid->Acquire();

	}

	return S_OK;

}

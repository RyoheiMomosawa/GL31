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
#include "DIMouse.h"


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
input::DIMouse::DIMouse()
{
	// 初期化
	lpdid = NULL;
	m_State = NULL;
	m_StateTrigger = NULL;
	m_StateRelese = NULL;
	m_StateRepeat = NULL;
	m_StateRepeatCount = NULL;
	m_RepeatSpeed = 30;
	m_pDevMouse = NULL;
	m_hMouseEvent = NULL;


	// 入力ワークのメモリ動的確保
	m_State = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateTrigger = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRelese = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRepeat = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRepeatCount = new unsigned int[ MOUSE_USE_BOTTON_MAX ];

	// ゼロクリア
	ZeroMemory( m_State, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateTrigger, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRelese, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRepeat, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRepeatCount, sizeof( unsigned int ) * MOUSE_USE_BOTTON_MAX );

}


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
input::DIMouse::~DIMouse()
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
HRESULT input::DIMouse::Init( HWND hWnd )
{
	/* マウスの設定 */
	if( FAILED( Input::lpDirectInput->CreateDevice( GUID_SysMouse, &m_pDevMouse, NULL ) ) )
	{
		return E_FAIL;

	}

	// マウスデータフォーマットの設定
	if( sizeof MOUSE_STATE == sizeof DIMOUSESTATE )
	{
		if( FAILED( m_pDevMouse->SetDataFormat( &c_dfDIMouse ) ) )
		{
			return E_FAIL;

		}

	}
	else if( sizeof MOUSE_STATE == sizeof DIMOUSESTATE2 )
	{
		if( FAILED( m_pDevMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
		{
			return E_FAIL;

		}

	}

	// マウスの動作設定
	if( FAILED( m_pDevMouse->SetCooperativeLevel( hWnd, COOPERRATIONLEBEL_MOUSE ) ) )
	{
		return E_FAIL;

	}

	// マウスイベントの生成
	m_hMouseEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( m_hMouseEvent == NULL )
	{
		return E_FAIL;

	}

	// マウスにイベントのセット
	if( FAILED( m_pDevMouse->SetEventNotification( m_hMouseEvent ) ) )
	{
		return E_FAIL;

	}

	// マウス バッファサイズの指定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof DIPROPDWORD;
	dipdw.diph.dwHeaderSize = sizeof DIPROPHEADER;
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL; // 相対モード

	if( FAILED( m_pDevMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
	{
		return E_FAIL;

	}

	// マウスのアクセス権限を取得
	//g_pDevMouse->Acquire();
	m_pDevMouse->Unacquire();

	return S_OK;

}


/******************************************************************************
**	関数名: 終了処理 Uninit
**		関数の概要
**	引数  : void
**	戻り値: int
**	説明  :
******************************************************************************/
int input::DIMouse::Uninit()
{
	if( m_pDevMouse != NULL )
	{
		/* キーボードのアクセス権解放 */
		m_pDevMouse->Unacquire();

		m_pDevMouse->Release();
		m_pDevMouse = NULL;

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
HRESULT input::DIMouse::Update()
{
	/**** 変数宣言 ****/
	MOUSE_STATE aMouseState; // マウスの状態を取得する構造体変数


	/* デバイスからデータを取得 */
	if( SUCCEEDED( m_pDevMouse->GetDeviceState( sizeof MOUSE_STATE, &aMouseState ) ) )
	{
		/* 入力情報を代入 */
		for( int nCntMouse = 0; nCntMouse < MOUSE_USE_BOTTON_MAX; nCntMouse++ )
		{
			m_StateTrigger[ nCntMouse ] = aMouseState.rgbButtons[ nCntMouse ] ^ m_State[ nCntMouse ] & aMouseState.rgbButtons[ nCntMouse ];
			m_StateRelese[ nCntMouse ] = m_State[ nCntMouse ] ^ aMouseState.rgbButtons[ nCntMouse ] & m_State[ nCntMouse ];
			m_State[ nCntMouse ] = m_StateRepeat[ nCntMouse ] = aMouseState.rgbButtons[ nCntMouse ];

		}

	}
	/* アクセス権がなかったら再取得 */
	else
	{
		m_pDevMouse->Acquire();

	}

	// 取得結果をコピー
	m_MouseState = aMouseState;

	return S_OK;

}


/******************************************************************************
**	関数名: GetMouse
**	関数の概要
**	引数  : void
**	戻り値: MOUSE_STATE *
**	説明  :
******************************************************************************/
MOUSE_STATE * input::DIMouse::GetMouse()
{
	return &m_MouseState;

}


#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: Client.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016//
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
#include <Windows.h>
#include "WindowsSocketService.h"


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/


/******************************************************************************
**	クラス定義
******************************************************************************/
class Client
{
public:
	Client();
	~Client();

	// メソッド
	void Init();
	void Uninit();
	static unsigned int __stdcall Send( void *p );
	void SetIPAdress( char *pStr );
	void SetPortNo( long ip );
	void SetBufferSize( int nSize );
	void SetBroadcast( bool flag );
	void SetMulticast( bool flag );
	void SetSendData( char *pData, int buffer );
	bool EndFlag();

private:
	static char m_Buffer[ MAX_PATH ];
	static char m_IP[ MAX_PATH ];
	static int m_Len;
	static SOCKADDR_IN m_Addrin;
	static SOCKET m_Socket;
	static int m_Protocol;
	static long m_PortNo;
	static int m_BufferSize;	// 送るデータのサイズ
	static bool m_bEndFlag;
	static bool m_bInitFlagIP;
	static bool m_bInitFlagPort;
	static bool bSendingFlag;
	static bool m_bBroadcastFlag;

};



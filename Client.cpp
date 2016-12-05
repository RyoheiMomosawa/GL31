/******************************************************************************
**	タイトル  :
**	ファイル名: Client.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016//
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/

// 自身ヘッダ
#include "Client.h"

// オブジェクト


// システム


// デバッグ


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
char Client::m_Buffer[ MAX_PATH ];
char Client::m_IP[ MAX_PATH ];
int Client::m_Len;
SOCKADDR_IN Client::m_Addrin;
SOCKET Client::m_Socket;
int Client::m_Protocol = 0;
long Client::m_PortNo;
int Client::m_BufferSize;
bool Client::m_bEndFlag = true;
bool Client::m_bInitFlagIP = false;
bool Client::m_bInitFlagPort = false;
bool Client::bSendingFlag = false;
bool Client::m_bBroadcastFlag = false;


/******************************************************************************
**	関数名:
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Client::Client()
{
	ZeroMemory( m_Buffer, MAX_PATH );
	ZeroMemory( m_IP, MAX_PATH );
	m_Len = 0;
	ZeroMemory( &m_Addrin, MAX_PATH );
	ZeroMemory( &m_Socket, MAX_PATH );
	m_Protocol = 0;
	m_PortNo = 0;
	m_BufferSize = 0;
	m_bEndFlag = true;
	m_bInitFlagIP = false;
	m_bInitFlagPort = false;
	bSendingFlag = false;
	m_bBroadcastFlag = false;

}

/******************************************************************************
**	関数名: ~
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Client::~Client()
{
}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::Init()
{
	if( !m_bInitFlagIP || !m_bInitFlagPort )
	{
		return;

	}

	// WSAの初期化
	WindowsSocketService::Init();

	// ソケットの生成
	m_Socket = socket( AF_INET, SOCK_DGRAM, m_Protocol );


	// 送信用アドレスの設定
	m_Addrin.sin_family = AF_INET;
	m_Addrin.sin_addr.S_un.S_addr = inet_addr( m_IP );
	m_Addrin.sin_port = htons( m_PortNo );

	// ブロードキャストの許可
	if( m_bBroadcastFlag )
	{
		int value = 1;
		setsockopt( m_Socket, SOL_SOCKET, SO_BROADCAST, ( char* )&value, sizeof( value ) );

	}

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
unsigned int __stdcall Client::Send( void *p )
{
	// 送信
	int addressLen = 0;
	sockaddr_in addressClient;
	m_bEndFlag = true;
	while(true)
	{
		if( bSendingFlag )
		{

			addressLen = sizeof( sockaddr_in );
			m_Len = strnlen_s( m_Buffer, MAX_PATH );
			sendto( m_Socket, m_Buffer, strlen( m_Buffer ) + 1, 0, ( SOCKADDR* )&m_Addrin, sizeof SOCKADDR_IN );
			//recvfrom( m_Socket, m_Buffer, MAX_PATH, 0, ( sockaddr* )&addressClient, &addressLen );
			//memset( szBufSend, '\0', MAX_PATH );

			bSendingFlag = false;

		}


	}

	return 0;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::Uninit()
{
	// ソケットの解放
	closesocket( m_Socket );

	// WSAの終了
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::SetIPAdress( char *pStr )
{
	strcpy_s( m_IP, MAX_PATH, pStr );
	m_bInitFlagIP = true;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::SetPortNo( long ip )
{
	m_PortNo = ip;
	m_bInitFlagPort = true;

}


/******************************************************************************
**	関数名:SetBufferSize
**	関数の概要
**	引数  :int型 サイズ
**	戻り値:なし
**	説明  :バッファサイズの設定
******************************************************************************/
void Client::SetBufferSize(int nSize)
{
	m_BufferSize = nSize;
}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::SetBroadcast( bool flag )
{
	m_bBroadcastFlag = flag;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::SetMulticast( bool flag )
{
	switch( flag )
	{
		case true:
			m_Protocol = IPPROTO_UDP;

			break;


		case false:
		default:
			m_Protocol = IPPROTO_IP;

			break;


	}

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
void Client::SetSendData( char *pData, int buffer )
{
	memset( m_Buffer, '\0', MAX_PATH );
	memcpy_s( m_Buffer, MAX_PATH, pData, buffer );
	bSendingFlag = true;

}


/******************************************************************************
**	関数名:
**	関数の概要
**	引数  :
**	戻り値:
**	説明  :
******************************************************************************/
bool Client::EndFlag()
{
	return m_bEndFlag;

}

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

// 自身ヘッダ
#include "Server.h"


// オブジェクト


// システム


// デバッグ


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
char Server::m_Buffer[ MAX_PATH ];
char Server::m_IP[ MAX_PATH ];
int Server::m_Len;
int Server::m_Protocol;
SOCKADDR_IN Server::m_Addrin;
SOCKET Server::m_Socket;
long Server::m_PortNo;
bool Server::m_bInitFlagIP;
bool Server::m_bInitFlagPort;
bool Server::m_bMulticastFlag;


/******************************************************************************
**	関数名: Server
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
Server::Server()
{
	ZeroMemory( m_Buffer, MAX_PATH );
	ZeroMemory( m_IP, MAX_PATH );
	m_Len = 0;
	m_Protocol = 0;
	ZeroMemory( &m_Addrin, sizeof SOCKADDR_IN );
	ZeroMemory( &m_Socket, sizeof SOCKET );
	m_PortNo = 0L;
	m_bInitFlagIP = false;
	m_bInitFlagPort = false;
	m_bMulticastFlag = false;

}


/******************************************************************************
**	関数名: ~Server
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
Server::~Server()
{
}



/******************************************************************************
**	関数名: Init
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Server::Init()
{
	if( !m_bInitFlagPort && !m_bInitFlagIP )
	{
		return;

	}

	// WSAの初期化
	WindowsSocketService::Init();

	// ソケットの生成 UDP
	m_Socket = socket( AF_INET, SOCK_DGRAM, m_Protocol );

	// 送信用アドレスの設定
	m_Addrin.sin_family = AF_INET;
	m_Addrin.sin_addr.S_un.S_addr = INADDR_ANY;
	m_Addrin.sin_port = htons( m_PortNo );

	// マルチキャスト設定
	if( m_bMulticastFlag )
	{
		int value = 1;
		setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, ( char* )&value, sizeof( value ) );

	}

	// ソケットのバインド
	bind( m_Socket, ( SOCKADDR * )&m_Addrin, sizeof SOCKADDR_IN );

	// マルチキャストグループへ参加
	if( m_bMulticastFlag )
	{
		ip_mreq mreq;
		memset( &mreq, 0, sizeof( ip_mreq ) );
		mreq.imr_multiaddr.S_un.S_addr = inet_addr( m_IP );
		mreq.imr_interface.S_un.S_addr = INADDR_ANY;
		setsockopt( m_Socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, ( char* )&mreq, sizeof( ip_mreq ) );

	}

}


/******************************************************************************
**	関数名: Receive
**	関数の概要
**	引数  : void *p
**	戻り値: unsigned int __stdcall
**	説明  :
******************************************************************************/
unsigned int __stdcall Server::Receive( void *p )
{
	// 受信
	int addressLen = 0;
	sockaddr_in addressServer;
	char buffer[ MAX_PATH ];
	
	
	while( 1 )
	{
		memset( buffer, '\0', MAX_PATH );
		addressLen = sizeof( sockaddr_in );
		recvfrom( m_Socket, buffer, MAX_PATH, 0, ( sockaddr* )&addressServer, &addressLen );
		if( buffer[ 0 ] != '\0' )
		{
			strcpy_s( m_Buffer, MAX_PATH, buffer );

		}
		

	}

	return 0;

}


/******************************************************************************
**	関数名: Uninit
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
******************************************************************************/
void Server::Uninit()
{
	// ソケットの解放
	closesocket( m_Socket );

	// WSAの終了
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	関数名: SetAddress
**	関数の概要
**	引数  : const char *ip
**	戻り値: void
**	説明  :
******************************************************************************/
void Server::SetAddress( const char *ip )
{
	strcpy_s( m_IP, MAX_PATH, ip );
	m_bInitFlagIP = true;

}


/******************************************************************************
**	関数名: SetPortNo
**	関数の概要
**	引数  : long ip
**	戻り値: void
**	説明  :
******************************************************************************/
void Server::SetPortNo( long ip )
{
	m_PortNo = ip;
	m_bInitFlagPort = true;

}


/******************************************************************************
**	関数名: SetMulticast
**	関数の概要
**	引数  : bool flag
**	戻り値: void
**	説明  :
******************************************************************************/
void Server::SetMulticast( bool flag )
{
	m_bMulticastFlag = flag;
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
**	関数名: GetBufferData
**	関数の概要
**	引数  : char * pOutData, int DataBufferSize
**	戻り値: bool
**	説明  :
******************************************************************************/
bool Server::GetBufferData( char * pOutData, int DataBufferSize )
{
	if( m_Buffer[ 0 ] != NULL )
	{
		strcpy_s( pOutData, DataBufferSize, m_Buffer );
		memset( m_Buffer, 0, MAX_PATH );

		return true;

	}

	return false;

}

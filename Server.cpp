/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: .cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016//
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Server.h"


// �I�u�W�F�N�g


// �V�X�e��


// �f�o�b�O


/******************************************************************************
**	�ÓI�����o�ϐ�
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
**	�֐���: Server
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
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
**	�֐���: ~Server
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Server::~Server()
{
}



/******************************************************************************
**	�֐���: Init
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Server::Init()
{
	if( !m_bInitFlagPort && !m_bInitFlagIP )
	{
		return;

	}

	// WSA�̏�����
	WindowsSocketService::Init();

	// �\�P�b�g�̐��� UDP
	m_Socket = socket( AF_INET, SOCK_DGRAM, m_Protocol );

	// ���M�p�A�h���X�̐ݒ�
	m_Addrin.sin_family = AF_INET;
	m_Addrin.sin_addr.S_un.S_addr = INADDR_ANY;
	m_Addrin.sin_port = htons( m_PortNo );

	// �}���`�L���X�g�ݒ�
	if( m_bMulticastFlag )
	{
		int value = 1;
		setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, ( char* )&value, sizeof( value ) );

	}

	// �\�P�b�g�̃o�C���h
	bind( m_Socket, ( SOCKADDR * )&m_Addrin, sizeof SOCKADDR_IN );

	// �}���`�L���X�g�O���[�v�֎Q��
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
**	�֐���: Receive
**	�֐��̊T�v
**	����  : void *p
**	�߂�l: unsigned int __stdcall
**	����  :
******************************************************************************/
unsigned int __stdcall Server::Receive( void *p )
{
	// ��M
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
**	�֐���: Uninit
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Server::Uninit()
{
	// �\�P�b�g�̉��
	closesocket( m_Socket );

	// WSA�̏I��
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	�֐���: SetAddress
**	�֐��̊T�v
**	����  : const char *ip
**	�߂�l: void
**	����  :
******************************************************************************/
void Server::SetAddress( const char *ip )
{
	strcpy_s( m_IP, MAX_PATH, ip );
	m_bInitFlagIP = true;

}


/******************************************************************************
**	�֐���: SetPortNo
**	�֐��̊T�v
**	����  : long ip
**	�߂�l: void
**	����  :
******************************************************************************/
void Server::SetPortNo( long ip )
{
	m_PortNo = ip;
	m_bInitFlagPort = true;

}


/******************************************************************************
**	�֐���: SetMulticast
**	�֐��̊T�v
**	����  : bool flag
**	�߂�l: void
**	����  :
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
**	�֐���: GetBufferData
**	�֐��̊T�v
**	����  : char * pOutData, int DataBufferSize
**	�߂�l: bool
**	����  :
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

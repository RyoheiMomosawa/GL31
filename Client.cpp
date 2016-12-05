/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Client.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016//
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Client.h"

// �I�u�W�F�N�g


// �V�X�e��


// �f�o�b�O


/******************************************************************************
**	�ÓI�����o�ϐ�
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
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
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
**	�֐���: ~
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Client::~Client()
{
}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::Init()
{
	if( !m_bInitFlagIP || !m_bInitFlagPort )
	{
		return;

	}

	// WSA�̏�����
	WindowsSocketService::Init();

	// �\�P�b�g�̐���
	m_Socket = socket( AF_INET, SOCK_DGRAM, m_Protocol );


	// ���M�p�A�h���X�̐ݒ�
	m_Addrin.sin_family = AF_INET;
	m_Addrin.sin_addr.S_un.S_addr = inet_addr( m_IP );
	m_Addrin.sin_port = htons( m_PortNo );

	// �u���[�h�L���X�g�̋���
	if( m_bBroadcastFlag )
	{
		int value = 1;
		setsockopt( m_Socket, SOL_SOCKET, SO_BROADCAST, ( char* )&value, sizeof( value ) );

	}

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
unsigned int __stdcall Client::Send( void *p )
{
	// ���M
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
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::Uninit()
{
	// �\�P�b�g�̉��
	closesocket( m_Socket );

	// WSA�̏I��
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::SetIPAdress( char *pStr )
{
	strcpy_s( m_IP, MAX_PATH, pStr );
	m_bInitFlagIP = true;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::SetPortNo( long ip )
{
	m_PortNo = ip;
	m_bInitFlagPort = true;

}


/******************************************************************************
**	�֐���:SetBufferSize
**	�֐��̊T�v
**	����  :int�^ �T�C�Y
**	�߂�l:�Ȃ�
**	����  :�o�b�t�@�T�C�Y�̐ݒ�
******************************************************************************/
void Client::SetBufferSize(int nSize)
{
	m_BufferSize = nSize;
}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::SetBroadcast( bool flag )
{
	m_bBroadcastFlag = flag;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
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
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
void Client::SetSendData( char *pData, int buffer )
{
	memset( m_Buffer, '\0', MAX_PATH );
	memcpy_s( m_Buffer, MAX_PATH, pData, buffer );
	bSendingFlag = true;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l:
**	����  :
******************************************************************************/
bool Client::EndFlag()
{
	return m_bEndFlag;

}

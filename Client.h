#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Client.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016//
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**
**
**
******************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include <Windows.h>
#include "WindowsSocketService.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/


/******************************************************************************
**	�N���X��`
******************************************************************************/
class Client
{
public:
	Client();
	~Client();

	// ���\�b�h
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
	static int m_BufferSize;	// ����f�[�^�̃T�C�Y
	static bool m_bEndFlag;
	static bool m_bInitFlagIP;
	static bool m_bInitFlagPort;
	static bool bSendingFlag;
	static bool m_bBroadcastFlag;

};



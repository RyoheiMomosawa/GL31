#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Receive.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/11/30
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
class Server
{
public:
	Server();
	~Server();

	// ���\�b�h
	void Init();
	static unsigned int __stdcall Receive( void *p );
	void Uninit();

	// Set
	void SetAddress( const char *ip );
	void SetPortNo( long ip );
	void SetMulticast( bool flag );

	// Get
	bool GetBufferData( _Out_ char *pOutData, _In_ int DataBufferSize );


private:
	static char m_Buffer[ MAX_PATH ];
	static char m_IP[ MAX_PATH ];
	static int m_Len;
	static int m_Protocol;
	static SOCKADDR_IN m_Addrin;
	static SOCKET m_Socket;
	static long m_PortNo;
	static bool m_bInitFlagIP;
	static bool m_bInitFlagPort;
	static bool m_bMulticastFlag;

};



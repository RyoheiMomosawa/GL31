/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: DIKeyboard.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/10
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "DIKeyboard.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
input::DIKeyboard::DIKeyboard()
{
	// ������
	lpdid = NULL;
	m_State = NULL;
	m_StateTrigger = NULL;
	m_StateRelese = NULL;
	m_StateRepeat = NULL;
	m_StateRepeatCount = NULL;
	m_RepeatSpeed = 30;
	
	
	// ���̓��[�N�̃��������I�m��
	m_State = new BYTE[ 256 ];
	m_StateTrigger = new BYTE[ 256 ];
	m_StateRelese = new BYTE[ 256 ];
	m_StateRepeat = new BYTE[ 256 ];
	m_StateRepeatCount = new unsigned int[ 256 ];

	// �[���N���A
	ZeroMemory( m_State, sizeof BYTE * 256 );
	ZeroMemory( m_StateTrigger, sizeof BYTE * 256 );
	ZeroMemory( m_StateRelese, sizeof BYTE * 256 );
	ZeroMemory( m_StateRepeat, sizeof BYTE * 256 );
	ZeroMemory( m_StateRepeatCount, sizeof( unsigned int ) * 256 );

}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
input::DIKeyboard::~DIKeyboard()
{
	// ���̓��[�N�̉��
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
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT input::DIKeyboard::Init( HWND hWnd )
{
	/* �f�o�C�X�̐��� */
	if( FAILED( Input::lpDirectInput->CreateDevice( GUID_SysKeyboard, &lpdid, NULL ) ) )
	{
		return E_FAIL;

	}

	/* �f�[�^�t�H�[�}�b�g�̐ݒ� */
	if( FAILED( lpdid->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return E_FAIL;

	}

	/* �������[�h�̐ݒ� */
	if( FAILED( lpdid->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return E_FAIL;

	}

	/* �L�[�{�[�h�ւ̃A�N�Z�X���擾 */
	lpdid->Acquire();

	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
int input::DIKeyboard::Uninit()
{
	if( lpdid != NULL )
	{
		/* �L�[�{�[�h�̃A�N�Z�X����� */
		lpdid->Unacquire();

		lpdid->Release();
		lpdid = NULL;

	}

	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
HRESULT input::DIKeyboard::Update()
{
	/**** �ϐ��錾 ****/
	BYTE aKeyState[ 256 ]; // �L�[�X�e�[�^�X


	// �f�o�C�X����f�[�^���擾
	if( SUCCEEDED( lpdid->GetDeviceState( sizeof( aKeyState ), &aKeyState[ 0 ] ) ) )
	{
		/* ���͏����� */
		for( int nCntKey = 0; nCntKey < 256; nCntKey++ )
		{
			m_StateTrigger[ nCntKey ] = aKeyState[ nCntKey ] ^ m_State[ nCntKey ] & aKeyState[ nCntKey ];
			m_StateRelese[ nCntKey ] = m_State[ nCntKey ] ^ aKeyState[ nCntKey ] & m_State[ nCntKey ];
			m_State[ nCntKey ] = m_StateRepeat[ nCntKey ] = aKeyState[ nCntKey ];

		}

	}
	/* �A�N�Z�X�����Ȃ�������Ď擾 */
	else
	{
		return lpdid->Acquire();

	}

	return S_OK;

}

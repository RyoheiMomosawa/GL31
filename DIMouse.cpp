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
#include "DIMouse.h"


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
input::DIMouse::DIMouse()
{
	// ������
	lpdid = NULL;
	m_State = NULL;
	m_StateTrigger = NULL;
	m_StateRelese = NULL;
	m_StateRepeat = NULL;
	m_StateRepeatCount = NULL;
	m_RepeatSpeed = 30;
	m_pDevMouse = NULL;
	m_hMouseEvent = NULL;


	// ���̓��[�N�̃��������I�m��
	m_State = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateTrigger = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRelese = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRepeat = new BYTE[ MOUSE_USE_BOTTON_MAX ];
	m_StateRepeatCount = new unsigned int[ MOUSE_USE_BOTTON_MAX ];

	// �[���N���A
	ZeroMemory( m_State, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateTrigger, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRelese, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRepeat, sizeof BYTE * MOUSE_USE_BOTTON_MAX );
	ZeroMemory( m_StateRepeatCount, sizeof( unsigned int ) * MOUSE_USE_BOTTON_MAX );

}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
input::DIMouse::~DIMouse()
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
HRESULT input::DIMouse::Init( HWND hWnd )
{
	/* �}�E�X�̐ݒ� */
	if( FAILED( Input::lpDirectInput->CreateDevice( GUID_SysMouse, &m_pDevMouse, NULL ) ) )
	{
		return E_FAIL;

	}

	// �}�E�X�f�[�^�t�H�[�}�b�g�̐ݒ�
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

	// �}�E�X�̓���ݒ�
	if( FAILED( m_pDevMouse->SetCooperativeLevel( hWnd, COOPERRATIONLEBEL_MOUSE ) ) )
	{
		return E_FAIL;

	}

	// �}�E�X�C�x���g�̐���
	m_hMouseEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( m_hMouseEvent == NULL )
	{
		return E_FAIL;

	}

	// �}�E�X�ɃC�x���g�̃Z�b�g
	if( FAILED( m_pDevMouse->SetEventNotification( m_hMouseEvent ) ) )
	{
		return E_FAIL;

	}

	// �}�E�X �o�b�t�@�T�C�Y�̎w��
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof DIPROPDWORD;
	dipdw.diph.dwHeaderSize = sizeof DIPROPHEADER;
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL; // ���΃��[�h

	if( FAILED( m_pDevMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
	{
		return E_FAIL;

	}

	// �}�E�X�̃A�N�Z�X�������擾
	//g_pDevMouse->Acquire();
	m_pDevMouse->Unacquire();

	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int input::DIMouse::Uninit()
{
	if( m_pDevMouse != NULL )
	{
		/* �L�[�{�[�h�̃A�N�Z�X����� */
		m_pDevMouse->Unacquire();

		m_pDevMouse->Release();
		m_pDevMouse = NULL;

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
HRESULT input::DIMouse::Update()
{
	/**** �ϐ��錾 ****/
	MOUSE_STATE aMouseState; // �}�E�X�̏�Ԃ��擾����\���̕ϐ�


	/* �f�o�C�X����f�[�^���擾 */
	if( SUCCEEDED( m_pDevMouse->GetDeviceState( sizeof MOUSE_STATE, &aMouseState ) ) )
	{
		/* ���͏����� */
		for( int nCntMouse = 0; nCntMouse < MOUSE_USE_BOTTON_MAX; nCntMouse++ )
		{
			m_StateTrigger[ nCntMouse ] = aMouseState.rgbButtons[ nCntMouse ] ^ m_State[ nCntMouse ] & aMouseState.rgbButtons[ nCntMouse ];
			m_StateRelese[ nCntMouse ] = m_State[ nCntMouse ] ^ aMouseState.rgbButtons[ nCntMouse ] & m_State[ nCntMouse ];
			m_State[ nCntMouse ] = m_StateRepeat[ nCntMouse ] = aMouseState.rgbButtons[ nCntMouse ];

		}

	}
	/* �A�N�Z�X�����Ȃ�������Ď擾 */
	else
	{
		m_pDevMouse->Acquire();

	}

	// �擾���ʂ��R�s�[
	m_MouseState = aMouseState;

	return S_OK;

}


/******************************************************************************
**	�֐���: GetMouse
**	�֐��̊T�v
**	����  : void
**	�߂�l: MOUSE_STATE *
**	����  :
******************************************************************************/
MOUSE_STATE * input::DIMouse::GetMouse()
{
	return &m_MouseState;

}


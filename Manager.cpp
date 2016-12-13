/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Mnager.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/9
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Manager.h"


// �I�u�W�F�N�g
#include "SceneGL.h"
#include "Scene2DGL.h"
#include "Mode.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Fade.h"
#include "SceneGLTimer.h"


// �l�b�g���[�N
#include "Server.h"
#include "Client.h"


// �V�X�e��
#include "wndproc.h"
#include "main.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
RendererGL *Manager::m_pRenderer;
SceneGL *Manager::m_pScene;
input::DirectInput *Manager::m_pKeyboard;
input::DIMouse *Manager::m_Mouse;
SoundAL *Manager::m_pSound;
Mode *Manager::m_pMode;
Fade *Manager::m_pFade;
ALuint Manager::m_bgm001ID;

Client *Manager::m_pReceive;
HANDLE Manager::m_hClient;
unsigned int Manager::m_thClient;


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
Manager::Manager()
{
}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Manager::~Manager()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT Manager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// �l�b�g���[�N�̏�����
	WindowsSocketService::Init();
	m_pReceive = new Client;
	m_pReceive->SetIPAdress( "172.29.9.74" );
	m_pReceive->SetPortNo( 11451 );
	m_pReceive->SetBufferSize( MAX_PATH );
	m_pReceive->Init();
	m_hClient = ( HANDLE )_beginthreadex( NULL, 0, m_pReceive->Send, NULL, 0, &m_thClient );

	// �����_���[�̍쐬
	m_pRenderer = new RendererGL;
	if( FAILED( m_pRenderer->Init( hInstance, hWnd, bWindow ) ) )
	{
		return E_FAIL;

	}

	// �L�[�{�[�h
	input::Input::Init( hInstance, hWnd );
	m_pKeyboard = new input::DIKeyboard;
	m_pKeyboard->Init( hWnd );

	// �}�E�X
	m_Mouse = new input::DIMouse;
	m_Mouse->Init( hWnd );


	// �T�E���h
	m_pSound = new SoundAL;
	m_pSound->Init();
	m_pSound->CreateSource( SOURCE_MAX );
	m_pSound->CreateBuffer( BUFFER_MAX );
	m_pSound->CreateBufferData( "./data/BGM/bgm001.wav", &m_bgm001ID, AL_TRUE );
	m_pSound->SetBuffer( m_bgm001ID );
	m_pSound->PauseSoundAll();


	// ���[�h�̍쐬 //////////////////////
	m_pFade = new Fade;
	m_pFade->Init();
	Fade::Set( new Game );


	/**** �����I������S_OK��Ԃ� ****/
	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
int Manager::Uninit()
{
	// ���[�h�̍폜 
	SetMode( NULL );
	m_pFade->Uninit();
	delete m_pFade;
	m_pFade = NULL;


	// �l�b�g���[�N�̏I��
	CloseHandle( m_hClient );
	delete m_pReceive;
	WindowsSocketService::Uninit();


	// �T�E���h
	m_pSound->Uninit();
	delete m_pSound;
	m_pSound = NULL;


	// �R���g���[��
	m_pKeyboard->Uninit();
	delete m_pKeyboard;
	m_pKeyboard = NULL;

	
	// �}�E�X
	m_Mouse->Uninit();
	delete m_Mouse;
	m_Mouse = NULL;


	// Input�̃����[�X
	input::Input::Release();


	// �����_���[
	delete m_pRenderer;
	m_pRenderer = NULL;


	/**** �I�������������A0��Ԃ� ****/
	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Manager::Update()
{
	m_pKeyboard->Update();
	m_Mouse->Update();
	m_pSound->Update();
	m_pFade->Update();
	m_pMode->Update();

}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Manager::Draw()
{
	// �`�揀��
	if( !m_pRenderer->BeginDraw() )
	{
		return;

	}

	///////////////////////////////////////////////
	// �`��J�n
	//////////////////////////////////////////////

	// �e���[�h�A�I�u�W�F�N�g
	m_pMode->Draw();

	// �t�F�[�h
	m_pFade->Draw();


	/////////////////////////////////////////////
	// �`��I��
	/////////////////////////////////////////////

	// �`��I��
	m_pRenderer->EndDraw();


	// �X�e�[�^�X�o�[�̍X�V
	UpdateStatusBar();

	// �T�E���h�Đ�
//	m_pSound->PlaySoundAll();

}


/******************************************************************************
**	�֐���: GetKeyboard
**	�֐��̊T�v
**	����  : void
**	�߂�l: input::DirectInput *
**	����  :
******************************************************************************/
input::DirectInput *Manager::GetKeyboard()
{
	return m_pKeyboard;

}


/******************************************************************************
**	�֐���: GetMouse
**	�֐��̊T�v
**	����  : void
**	�߂�l: input::DirectInput *
**	����  :
******************************************************************************/
input::DIMouse *Manager::GetMouse()
{
	return m_Mouse;

}


/******************************************************************************
**	�֐���: SetMode
**	�֐��̊T�v
**	����  : Mode *Mode
**	�߂�l: void
**	����  :
******************************************************************************/
void Manager::SetMode( Mode *Mode )
{
	// �I������
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;

	}

	// ����������
	if( m_pMode == NULL && Mode != NULL )
	{
		m_pMode = Mode;
		m_pMode->Init();

	}

}


/******************************************************************************
**	�֐���: GetClient
**	�֐��̊T�v
**	����  : void
**	�߂�l: Client *
**	����  :
******************************************************************************/
Client *Manager::GetClient()
{
	return m_pReceive;

}


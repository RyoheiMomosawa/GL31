/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Game.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Game.h"

// �V�X�e��
#include "main.h"
#include "Result.h"
#include "Manager.h"
#include "Fade.h"
#include "wndproc.h"


// �l�b�g���[�N
#include "WindowsSocketService.h"
#include "Server.h"
#include "Client.h"


// �Q�[���I�u�W�F�N�g
#include "SceneGL.h"
#include "Scene2DGL.h"
#include "DIKeyboard.h"
#include "SceneGLTimer.h"


// �f�o�b�O����
#include "WndProcDbgManager.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
SceneGLTimer *Game::m_pTimer;


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
Game::Game()
{
}


/******************************************************************************
**	�֐���: ~
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Game::~Game()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void Game::Init()
{
	// �l�b�g���[�N�̏�����
	WindowsSocketService::Init();

	// �V�[���̍쐬
	// �w�i
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/bg001.tga" );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	// �I�u�W�F�N�g
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/runningman101.tga" );
	m_pScene->SetAnimation( 5, 5, 2 );
	m_pScene->SetParam( &Vector3( 100.0f, 100.0f, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	// �^�C�}�[
	m_pTimer = SceneGLTimer::Create();
	m_pTimer->SetTexture( "./data/TEXTURE/number000.tga" );
	m_pTimer->SetColor( &Color( 0.8f, 0.5f, 0.125f, 1.0f ) );
	m_pTimer->SetDigit( 3 );
	m_pTimer->SetTimer( 123 );
	//m_pTimer->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, 80.0f, 0.0f ), SCENEPARAM_POS );
	m_pTimer->SetParam( &Vector3( 150.0f, 80.0f, 0.0f ), SCENEPARAM_POS );
	m_pTimer->SetParam( &Vector3( 50.0f, 70.0f, 0.0f ), SCENEPARAM_SIZE );
	m_pTimer->Reset();

	m_pScene->InitAll();

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void Game::Uninit()
{
	/* �V�[���̍폜 */
	m_pScene->UninitAll();

	// �l�b�g���[�N�̏I��
	WindowsSocketService::Uninit();

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Game::Update()
{
	// �V�[���̍X�V
	m_pScene->UpdateAll();


	// ���[�h�؂�ւ�
	if( Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) && !m_bModeFlag )
	{
		Fade::Set( new Result );
		m_bModeFlag = true;

	}

}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Game::Draw()
{
	// �V�[���̕`��
	m_pScene->DrawAll();

}


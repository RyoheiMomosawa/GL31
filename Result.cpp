/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Result.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Result.h"

// �I�u�W�F�N�g
#include "Scene2DGL.h"

// �V�X�e��
#include "Manager.h"
#include "Title.h"
#include "main.h"
#include "Fade.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���: Result
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
Result::Result()
{
	m_pScene = NULL;

}


/******************************************************************************
**	�֐���: ~Result
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Result::~Result()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void Result::Init()
{
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/bg002.tga" );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pScene->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );

	m_pScene->InitAll();

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void Result::Uninit()
{
	m_pScene->UninitAll();
	m_pScene = NULL;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Result::Update()
{
	m_pScene->UpdateAll();

	// ���[�h�̐؂�ւ�
	if( Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) && !m_bModeFlag )
	{
		Fade::Set( new Title );
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
void Result::Draw()
{
	m_pScene->DrawAll();

}
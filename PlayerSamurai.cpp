/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: PlayerSamurai.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "PlayerSamurai.h"


// �I�u�W�F�N�g
#include "Scene2DGL.h"

// �V�X�e��
#include "Manager.h"
#include "main.h"
#include "Fade.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���: PlayerSamurai
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
PlayerSamurai::PlayerSamurai()
{
	m_pScene = NULL;
	m_Hp = 100;
	m_Forward_direction = 0.0f;
}


/******************************************************************************
**	�֐���: ~PlayerSamurai
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
PlayerSamurai::~PlayerSamurai()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void PlayerSamurai::Init(int id)
{
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/str_samurai.tga" );

	if(id)
	{
		m_pScene->SetParam(&Vector3(100.0f, 50.0f, 0.0f), SCENEPARAM_POS);
	}
	else
	{
		m_pScene->SetParam(&Vector3(300.0f, 150.0f, 0.0f), SCENEPARAM_POS);
	}


	m_pScene->SetParam(&Vector3(30.0f, 50.0f, 0.0f), SCENEPARAM_SIZE);
}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void PlayerSamurai::Uninit()
{
}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void PlayerSamurai::Update()
{
	Move();
	Attack0();
	Attack1();
}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void PlayerSamurai::Draw()
{
}

void PlayerSamurai::Attack0()
{
	//TODO�@�U���o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	//�U���{�^��0
	if(Manager::GetKeyboard()->GetTrigger(DIK_K))
	{
		MessageBox(nullptr, "�a���I�I", "test", MB_OK);
	}
}

void PlayerSamurai::Attack1()
{
	//TODO�@�U���o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	//�U���{�^��1
	if(Manager::GetKeyboard()->GetTrigger(DIK_L))
	{
		MessageBox(nullptr, "�U����e��", "test", MB_OK);
	}
}

void PlayerSamurai::Move()
{
	//TODO�@�ړ��o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	if(Manager::GetKeyboard()->GetPress(DIK_A))
	{
		m_Forward_direction = 3.14 * -0.5f;
		m_pScene->AddPos(-2, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_D))
	{
		m_Forward_direction = 3.14 * 0.5f;
		m_pScene->AddPos(2, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_W))
	{
		m_Forward_direction = 3.14 * 1.0f;
		m_pScene->AddPos(0, -2);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_S))
	{
		m_Forward_direction = 3.14 * 0.0f;
		m_pScene->AddPos(0, 2);
	}
}

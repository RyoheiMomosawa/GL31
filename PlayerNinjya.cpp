/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: PlayerNinjya.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "PlayerNinjya.h"


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
**	�֐���: PlayerNinjya
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
PlayerNinjya::PlayerNinjya()
{
	m_pScene = NULL;
	m_hp = 100;
}


/******************************************************************************
**	�֐���: ~PlayerNinjya
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
PlayerNinjya::~PlayerNinjya()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void PlayerNinjya::Init(int id)
{
	m_pScene = Scene2DGL::Create();
	m_pScene->SetTexture( "./data/TEXTURE/str_ninjya.tga" );

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
void PlayerNinjya::Uninit()
{
}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void PlayerNinjya::Update()
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
void PlayerNinjya::Draw()
{
}

void PlayerNinjya::Attack0()
{
	//TODO�@�U���o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	//�U���{�^��0
	if(Manager::GetKeyboard()->GetTrigger(DIK_K))
	{
		MessageBox(nullptr, "�藠�����΂�", "test", MB_OK);
	}
}

void PlayerNinjya::Attack1()
{
	//TODO�@�U���o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	//�U���{�^��1
	if(Manager::GetKeyboard()->GetTrigger(DIK_L))
	{
		MessageBox(nullptr, "�e����", "test", MB_OK);
	}
}

void PlayerNinjya::Move()
{
	//TODO�@�ړ��o���Ȃ��Ȃ甲����
	if(0)
	{
		return;
	}

	if(Manager::GetKeyboard()->GetPress(DIK_A))
	{
		m_pScene->AddPos(-2.5, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_D))
	{
		m_pScene->AddPos(2.5, 0);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_W))
	{
		m_pScene->AddPos(0, -2.5);
	}

	if(Manager::GetKeyboard()->GetPress(DIK_S))
	{
		m_pScene->AddPos(0, 2.5);
	}
}

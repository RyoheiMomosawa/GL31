/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: HPbarFrame.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 5 ��_�Y��
**	�쐬��    : 2016/11/28
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "HPbarFrame.h"


// �I�u�W�F�N�g
#include "Scene2DGL.h"


// �V�X�e��
#include "Manager.h"
#include "Game.h"
#include "main.h"
#include "HPbarFrame.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
int cntID = 0;
static ID m_ID;

/******************************************************************************
**	�֐���: HPbarFrame
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
HPbarFrame::HPbarFrame()
{
	m_pHPbarFrame = NULL;

}


/******************************************************************************
**	�֐���: ~HPbarFrame
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
HPbarFrame::~HPbarFrame()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void HPbarFrame::Init()
{
	cntID++;
	if (cntID == 0)
	{
		m_ID = ID_0;
	}
	else if (cntID == 1)
	{
		m_ID = ID_1;
	}
	else
	{
		cntID = 0;
		m_ID = ID_0;
	}

	if (m_ID == 0)
	{//�v���C���[�P�̐���
		m_pHPbarFrame = Scene2DGL::Create();
		m_pHPbarFrame->SetTexture("./data/TEXTURE/hp_back.tga");
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_WIDTH, (float)HPBARFRAME_HEIGHT, 0.0f), SCENEPARAM_SIZE);
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_POSX, (float)HPBARFRAME_POSY, 0.0f), SCENEPARAM_POS);
	}
	else if (m_ID == 1)
	{//�v���C���[�Q�̐���
		m_pHPbarFrame = Scene2DGL::Create();
		m_pHPbarFrame->SetTexture("./data/TEXTURE/hp_back.tga");
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_WIDTH, (float)HPBARFRAME_HEIGHT, 0.0f), SCENEPARAM_SIZE);
		m_pHPbarFrame->SetParam(&Vector3((float)HPBARFRAME_POSX_2, (float)HPBARFRAME_POSY,  0.0f), SCENEPARAM_POS);
	}

	/*m_pHPbarFrame = Scene2DGL::Create();
	m_pHPbarFrame->SetTexture("./data/TEXTURE/bg000.tga");
	m_pHPbarFrame->SetParam(&Vector3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f), SCENEPARAM_SIZE); 
	m_pHPbarFrame->SetParam(&Vector3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), SCENEPARAM_POS);*/

	m_pHPbarFrame->InitAll();

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void HPbarFrame::Uninit()
{
	m_pHPbarFrame->UninitAll();
	m_pHPbarFrame = NULL;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void HPbarFrame::Update()
{
	m_pHPbarFrame->UpdateAll();

}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void HPbarFrame::Draw()
{
	m_pHPbarFrame->DrawAll();

}

/******************************************************************************
**	�֐���: Create
**		�֐��̊T�v
**	����  : void
**	�߂�l: HPbarFrame *
**	����  : ���������� Scene2D�|�C���^�A���s�� NULL
******************************************************************************/
HPbarFrame *HPbarFrame::Create()
{
	HPbarFrame *p;
	p = new HPbarFrame;
	p->Init();
	return p;
}



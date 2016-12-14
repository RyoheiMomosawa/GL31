/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: CharaSelect.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "CharaSelect.h"


// �I�u�W�F�N�g
#include "Scene2DGL.h"


// �V�X�e��
#include "Manager.h"
#include "Game.h"
#include "main.h"
#include "Fade.h"

using namespace std;

namespace
{
	static const int JOB_NUM = 3;

	static const string jobNameFilePass[JOB_NUM] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string xActNameFileNames[JOB_NUM] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};

	static const string aActNameFileNames[JOB_NUM] =
	{
		"./data/TEXTURE/str_archer.tga",
		"./data/TEXTURE/str_ninjya.tga",
		"./data/TEXTURE/str_samurai.tga",
	};
}


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���: CharaSelect
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
CharaSelect::CharaSelect()
{
	m_pBg = NULL;

}


/******************************************************************************
**	�֐���: ~CharaSelect
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
CharaSelect::~CharaSelect()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void CharaSelect::Init()
{
	m_pBg = Scene2DGL::Create();
	m_pBg->SetTexture( "./data/TEXTURE/backGround.tga" );
	m_pBg->SetParam( &Vector3( ( float )SCREEN_WIDTH, ( float )SCREEN_HEIGHT, 0.0f ), SCENEPARAM_SIZE );
	m_pBg->SetParam( &Vector3( ( float )SCREEN_WIDTH * 0.5f, ( float )SCREEN_HEIGHT * 0.5f, 0.0f ), SCENEPARAM_POS );






	m_pBg->InitAll();
}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void CharaSelect::Uninit()
{
	m_pBg->UninitAll();
	m_pBg = NULL;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void CharaSelect::Update()
{
	//m_pBg->AddTexU(0.001f);

	m_pBg->UpdateAll();

	switch(m_state)
	{
	case SELECT:	UpdateSelectCheck();	break;
	case ASK:		UpdateAskToBattle();	break;
	}

	// ���[�h�̐؂�ւ�
	if( //Manager::GetKeyboard()->GetTrigger( DIK_RETURN ) 
		input::is_each_trigger(input::DECIDE) || input::is_each_trigger(input::PAUSE)
		&& !m_bModeFlag)
	{
		Fade::Set( new Game );
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
void CharaSelect::Draw()
{
	m_pBg->DrawAll();

}

//�L�����N�^�[�Z���N�g
//�����@�v���C���[ID
void CharaSelect::UpdateSelectCharactor(int id)
{
	//�E�L�[
	if(input::is_trigger(RIGHT, id))
	{
		//�J�[�\��������(�z�^)
		++m_selectId[id] %= JOB_NUM;

		////�J�[�\���ړ���
		//sound::play_se("data/se/�U�E�}�b�`���C�J�@�Y/cursor_select.wav", 1.0f, 0.625f);

		//�J�[�\���̈ړ��@�Ɓ@�����̕ύX
		m_pJobName[id]->SetTexture(jobNameFilePass[m_selectId[id]].c_str());
		m_pActName[id][X_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
		m_pActName[id][A_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
	}

	//���L�[
	if(input::is_trigger(LEFT, id))
	{
		//�J�[�\�������(�z�^)
		m_selectId[id] = (m_selectId[id] + JOB_NUM - 1) % JOB_NUM;

		////�J�[�\���ړ���
		//sound::play_se("data/se/�U�E�}�b�`���C�J�@�Y/cursor_select.wav", 1.0f, 0.625f);

		//�J�[�\���̈ړ��@�Ɓ@�����̕ύX
		m_pJobName[id]->SetTexture(jobNameFilePass[m_selectId[id]].c_str());
		m_pActName[id][X_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
		m_pActName[id][A_ACT]->SetTexture(xActNameFileNames[m_selectId[id]].c_str());
	}

	//����{�^���������ꂽ��
	if(input::is_trigger(DECIDE, id))
	{
		//����t���OON�@���蕶���\��
		m_isDecide[id] = true;
		m_pDecide[id]->GetObject3D()->bDraw = true;
	}

	//�L�����Z���{�^���������ꂽ��
	if(input::is_trigger(CANSEL, id))
	{
		//����t���OOFF�@���蕶����\��
		m_isDecide[id] = false;
		m_pDecide[id]->GetObject3D()->bDraw = false;
	}
}

//�Z���N�g�̃`�F�b�N
void CharaSelect::UpdateSelectCheck()
{
	//���v���C���[�̃Z���N�g����
	UpdateSelectCharactor(0);
	UpdateSelectCharactor(1);

	//���v���C���[���ɑI�����I����
	if(m_isDecide[0] && m_isDecide[1])
	{
		m_state = State::ASK;

		//�����J�n�@�m�F��ʂ�\������
		m_pDecideMask->GetObject3D()->bDraw		= true;
		m_pAskMask->GetObject3D()->bDraw		= true;
		m_pAskToStart->GetObject3D()->bDraw		= true;
		m_pYes->GetObject3D()->bDraw			= true;
		m_pNo->GetObject3D()->bDraw				= true;
	}
}

//�o�g���ڍs�m�F
void CharaSelect::UpdateAskToBattle()
{
	//����{�^���������ꂽ��
	if(input::is_each_trigger(DECIDE)
		&& !m_bModeFlag)
	{
		//�o�g���J�nOK�Ȃ�@�Q�[����
		if(m_isStartBattle)
		{
			Fade::Set(new Game);
			m_bModeFlag = true;
		}
		else
		{
			//���v���C���[�Ƃ��@�������Ԃɖ߂�
			for(int id = 0; id < 2; ++id)
			{
				//����t���OOFF�@���蕶����\��
				m_isDecide[id] = false;
				m_pDecide[id]->GetObject3D()->bDraw = false;
			}

			//�I����Ԃ֖߂�
			m_state = State::SELECT;

			//�����J�n�@�m�F��ʂ��\����
			m_pDecideMask->GetObject3D()->bDraw		= false;
			m_pAskMask->GetObject3D()->bDraw		= false;
			m_pAskToStart->GetObject3D()->bDraw		= false;
			m_pYes->GetObject3D()->bDraw			= false;
			m_pNo->GetObject3D()->bDraw				= false;
		}
	}

	//�L�����Z���{�^���������ꂽ��
	if(input::is_each_trigger(CANSEL))
	{
		//���v���C���[�Ƃ��@�������Ԃɖ߂�
		for(int id = 0; id < 2; ++id)
		{
			//����t���OOFF�@���蕶����\��
			m_isDecide[id] = false;
			m_pDecide[id]->GetObject3D()->bDraw = false;
		}

		//�I����Ԃ֖߂�
		m_state = State::SELECT;

		//�����J�n�@�m�F��ʂ��\����
		m_pDecideMask->GetObject3D()->bDraw		= false;
		m_pAskMask->GetObject3D()->bDraw		= false;
		m_pAskToStart->GetObject3D()->bDraw		= false;
		m_pYes->GetObject3D()->bDraw			= false;
		m_pNo->GetObject3D()->bDraw				= false;
	}
}

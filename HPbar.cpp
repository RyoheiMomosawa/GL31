/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: HPbar.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 5 ��_�Y��
**	�쐬��    : 2016/11/30
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "HPbar.h"


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
int cntID2 = 0;
static ID m_ID;

/******************************************************************************
**	�֐���: HPbar
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
HPbar::HPbar()
{
	m_pHPbar = NULL;

}


/******************************************************************************
**	�֐���: ~HPbar
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
HPbar::~HPbar()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
void HPbar::Init()
{
	cntID2++;
	if (cntID2 == 1)
	{
		m_ID = ID_0;
	}
	else
	{
		cntID2 = 0;
		m_ID = ID_1;
	}

	int onigiriSpaceX = 0;
	int onigiriSpaceY = 0;

	if (m_ID == 0)
	{//�v���C���[�P�̐���
		for (int cnt = 0; cnt < ONIGIRI_COUNT; cnt ++)
		{
			onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));//�ݒu�ʒu�����炷�i�x���j
			m_pHPbar = Scene2DGL::Create();
			m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
			onigiriSpaceX += ONIGIRI_SPACE_X;//�ݒu�ʒu�����炷�i�w���j
			
		}
		
	}
	else if (m_ID == 1)
	{//�v���C���[�Q�̐���
		for (int cnt = 0; cnt < ONIGIRI_COUNT; cnt++)
		{
			onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));//�ݒu�ʒu�����炷�i�x���j
			m_pHPbar = Scene2DGL::Create();
			m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
			m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
			m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH + ONIGIRI_SIZE + ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
			onigiriSpaceX += ONIGIRI_SPACE_X;//�ݒu�ʒu�����炷�i�w���j
		}
	}

	m_pHPbar->InitAll();

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
void HPbar::Uninit()
{
	m_pHPbar->UninitAll();
	m_pHPbar = NULL;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void HPbar::Update()
{
	cntID2++;
	if (cntID2 == 1)
	{
		m_ID = ID_0;
	}
	else
	{
		cntID2 = 0;
		m_ID = ID_1;
	}

	static int HP1 = 10;
	static int HP2 = 10;
	static int HP1_old = 0;
	static int HP2_old = 0;
	HP1_old = HP1;
	HP2_old = HP2;

	//CScene *scene = CScene::GetList(DRAWTYPE_OBJ);		// ���X�g�擾
	//while (scene)
	//{
	//	// �v���C���[���m�̓����蔻��
	//	if (scene->GetObjType() == OBJTYPE_PLAYER)
	//	{
	//		// �N���X�̃L���X�g
	//		CPlayer *Player = dynamic_cast< CPlayer* >(scene);
	//		if (Player->GetLabel() == PLAYER_LABEL_01)
	//		{
	//			HP1 = Player->GetHp();
	//		}
	//		else
	//		{
	//			HP2 = Player->GetHp();
	//		}
	//	}
	//	scene = scene->GetNext();
	//}

	//�e�X�g/////////////////////////////////////////////////////////////////////////
	//if (Manager::GetKeyboard()->GetTrigger(DIK_UP))
	//{
	//	HP1++;
	//	HP2++;
	//}
	//else if (Manager::GetKeyboard()->GetTrigger(DIK_DOWN))
	//{
	//	HP1--;
	//	HP2--;
	//}
	
	//�X�V//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int onigiriSpaceX = 0;
	int onigiriSpaceY = 0;
	if (m_ID == 0)
	{//�v���C���[�P�̐���
		if (HP1_old != HP1)
		{
			for (int cnt = 0; cnt < ONIGIRI_COUNT - HP1; cnt++)
			{
				onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));
				m_pHPbar = Scene2DGL::Create();
				m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
				onigiriSpaceX += ONIGIRI_SPACE_X;

			}
		}

	}
	else if (m_ID == 1)
	{//�v���C���[�Q�̐���
		if (HP2_old != HP2)
		{
			for (int cnt = 0; cnt < ONIGIRI_COUNT - HP2; cnt++)
			{
				onigiriSpaceY = (ONIGIRI_SPACE_Y * (cnt & 1));
				m_pHPbar = Scene2DGL::Create();
				m_pHPbar->SetTexture("./data/TEXTURE/hp_onigiri.tga");
				m_pHPbar->SetParam(&Vector3((float)ONIGIRI_SIZE, (float)ONIGIRI_SIZE, 0.0f), SCENEPARAM_SIZE);
				m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH + ONIGIRI_SIZE + ONIGIRI_POS_X + onigiriSpaceX, (float)ONIGIRI_POS_Y + onigiriSpaceY, 0.0f), SCENEPARAM_POS);
				onigiriSpaceX += ONIGIRI_SPACE_X;
			}
		}
	}
	
	

	m_pHPbar->UpdateAll();

}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void HPbar::Draw()
{
	m_pHPbar->DrawAll();
}

/******************************************************************************
**	�֐���: Create
**		�֐��̊T�v
**	����  : void
**	�߂�l: HPbarFrame *
**	����  : ���������� Scene2D�|�C���^�A���s�� NULL
******************************************************************************/
HPbar *HPbar::Create()
{
	HPbar *p;
	p = new HPbar;
	p->Init();
	return p;
}




































///******************************************************************************
//**	�^�C�g��  :
//**	�t�@�C����: HPbar.cpp
//**	�쐬��    : AT-13B-284 �o�Ȕԍ� 5 ��_�Y��
//**	�쐬��    : 2016/11/30
//**	�C����	�@: //
//********************************************************************************/
//
///******************************************************************************
//**	�C���N���[�h�t�@�C��
//******************************************************************************/
//
//// ���g�w�b�_
//#include "HPbar.h"
//
//
//// �I�u�W�F�N�g
//#include "Scene2DGL.h"
//
//
//// �V�X�e��
//#include "Manager.h"
//#include "Game.h"
//#include "main.h"
//#include "HPbarFrame.h"
//
//
///******************************************************************************
//**	�ÓI�����o�ϐ�
//******************************************************************************/
//int cntID2 = 0;
//static ID m_ID;
//HP hp[2] =
//{
//	{ 0, 0, 0, 0 },
//	{ 0, 0, 0, 0 },
//};
//
///******************************************************************************
//**	�֐���: HPbar
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: void
//**	����  : �R���X�g���N�^
//******************************************************************************/
//HPbar::HPbar()
//{
//	m_pHPbar = NULL;
//
//}
//
//
///******************************************************************************
//**	�֐���: ~HPbar
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: void
//**	����  : �f�X�g���N�^
//******************************************************************************/
//HPbar::~HPbar()
//{
//}
//
//
///******************************************************************************
//**	�֐���: ���������� Init
//**		�֐��̊T�v
//**	����  :
//**	�߂�l: HRESULT
//**	����  : ����������
//******************************************************************************/
//void HPbar::Init()
//{
//	//�ϐ�
//	hp[0].posX = 0;
//	hp[0].colR = 0;
//	hp[0].colG = 0;
//	hp[0].colB = 0;
//
//	//�ϐ�
//	hp[1].posX = 0;
//	hp[1].colR = 0;
//	hp[1].colG = 0;
//	hp[1].colB = 0;
//	
//	m_pHPbar->InitAll();
//
//}
//
//
///******************************************************************************
//**	�֐���: �I������ Uninit
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: int
//**	����  :
//******************************************************************************/
//void HPbar::Uninit()
//{
//	m_pHPbar->UninitAll();
//	m_pHPbar = NULL;
//
//}
//
//
///******************************************************************************
//**	�֐���: �X�V���� Update
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: void
//**	����  :
//******************************************************************************/
//void HPbar::Update()
//{
//	cntID2++;
//	if (cntID2 == 1)
//	{
//		m_ID = ID_0;
//	}
//	else
//	{
//		cntID2 = 0;
//		m_ID = ID_1;
//	}
//
//	static int HP1 = 0;
//	static int HP2 = 0;
//
//	//CScene *scene = CScene::GetList(DRAWTYPE_OBJ);		// ���X�g�擾
//	//while (scene)
//	//{
//	//	// �v���C���[���m�̓����蔻��
//	//	if (scene->GetObjType() == OBJTYPE_PLAYER)
//	//	{
//	//		// �N���X�̃L���X�g
//	//		CPlayer *Player = dynamic_cast< CPlayer* >(scene);
//	//		if (Player->GetLabel() == PLAYER_LABEL_01)
//	//		{
//	//			HP1 = Player->GetHp();
//	//		}
//	//		else
//	//		{
//	//			HP2 = Player->GetHp();
//	//		}
//	//	}
//	//	scene = scene->GetNext();
//	//}
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	if (m_ID == 0)
//	{
//		hp[0].posX++;
//		if (HP_X_Left + hp[0].posX == HP_X_Right)
//		{
//			hp[0].posX = 0;
//		}
//		////�g�o�o�[�̈ʒu�ύX
//		//hp[0].posX = (HP_MAX - HP1) * (HPBAR_WIDTH / HP_MAX);
//
//		//�g�o�o�[�̐F�ύX
//		if (hp[0].posX < (HP_X_Right / 2))
//		{
//			hp[0].colR = 0;
//			hp[0].colG = 200;
//			hp[0].colB = 100;
//		}
//		else if (hp[0].posX >= (HP_X_Right / 2) && hp[0].posX < (HP_X_Right / 3))
//		{
//			hp[0].colR = 255;
//			hp[0].colG = 255;
//			hp[0].colB = 0;
//		}
//		else
//		{
//			hp[0].colR = 255;
//			hp[0].colG = 0;
//			hp[0].colB = 0;
//		}
//
//		/*m_pHPbar = Scene2DGL::Create();
//		m_pHPbar->SetTexture("./data/TEXTURE/HPb.tga");
//		m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH, (float)HPBAR_HEIGHT, 0.0f), SCENEPARAM_SIZE);
//		m_pHPbar->SetParam(&Vector3((float)HPBAR_POSX, (float)HPBAR_POSY, 0.0f), SCENEPARAM_POS);
//		m_pHPbar->SetColor(&Color(hp[0].colR, hp[0].colG, hp[0].colB, 255));*/
//
//		//VERTEX_2D *pVtx;
//
//		//m_VertexBuffer->Lock(                 //���_���ւ̃|�C���^���擾 �� ���b�N
//		//	0,
//		//	0,
//		//	(void**)&pVtx,
//		//	0);
//
//
//		//pVtx[0].pos = D3DXVECTOR3(HP_X_Left + hp[0].posX, HP_Y_Left, 0.0f);						//���_���W�i�w�A�x�A�y�j
//		//pVtx[1].pos = D3DXVECTOR3(HP_X_Right, HP_Y_Left, 0.0f);
//		//pVtx[2].pos = D3DXVECTOR3(HP_X_Left + hp[0].posX, HP_Y_Right, 0.0f);
//		//pVtx[3].pos = D3DXVECTOR3(HP_X_Right, HP_Y_Right, 0.0f);
//
//		//pVtx[0].rhw = 1.0f;												//���W�ϊ��p�W��
//		//pVtx[1].rhw = 1.0f;
//		//pVtx[2].rhw = 1.0f;
//		//pVtx[3].rhw = 1.0f;
//
//		//pVtx[0].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);				//���_�J���[�i�q�C�f�C�a�C�`�j
//		//pVtx[1].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		//pVtx[2].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		//pVtx[3].col = D3DCOLOR_RGBA(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//
//		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);							//�e�N�X�`���̂t�u���W�i�t�C�u�j
//		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		//m_VertexBuffer->Unlock();              //���b�N�̉���
//
//	}
//
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	else if (m_ID == 1)
//	{
//		////�g�o�o�[�̈ʒu�ύX
//		hp[1].posX = (HP_MAX - HP1) * (HPBAR_WIDTH / HP_MAX);
//
//		//�g�o�o�[�̐F�ύX
//		if (hp[1].posX < (HPBAR_WIDTH / 2))
//		{
//			hp[1].colR = 0;
//			hp[1].colG = 0;
//			hp[1].colB = 255;
//		}
//		else if (hp[1].posX >= (HPBAR_WIDTH / 2) && hp[1].posX < (HPBAR_WIDTH / 3))
//		{
//			hp[1].colR = 0;
//			hp[1].colG = 255;
//			hp[1].colB = 0;
//		}
//		else
//		{
//			hp[1].colR = 255;
//			hp[1].colG = 0;
//			hp[1].colB = 0;
//		}
//
//		//m_pHPbar = Scene2DGL::Create();
//		////m_pHPbar->SetTexture("./data/TEXTURE/HPb.tga");
//		//m_pHPbar->SetParam(&Vector3((float)HPBAR_WIDTH - hp[0].posX, (float)HPBAR_HEIGHT, 0.0f), SCENEPARAM_SIZE);
//		//m_pHPbar->SetParam(&Vector3((float)HPBAR_POSX, (float)HPBAR_POSY, 0.0f), SCENEPARAM_POS);
//		//m_pHPbar->SetColor(&Color(hp[1].colR, hp[1].colG, hp[1].colB, 255));
//
//
//
//		//VERTEX_2D *pVtx;
//
//		//m_VertexBuffer->Lock(                 //���_���ւ̃|�C���^���擾 �� ���b�N
//		//	0,
//		//	0,
//		//	(void**)&pVtx,
//		//	0);
//
//
//		//pVtx[0].pos = D3DXVECTOR3(HP_X_Left2, HP_Y_Left2, 0.0f);						//���_���W�i�w�A�x�A�y�j
//		//pVtx[1].pos = D3DXVECTOR3(HP_X_Right2 - hp[1].posX, HP_Y_Left2, 0.0f);
//		//pVtx[2].pos = D3DXVECTOR3(HP_X_Left2, HP_Y_Right2, 0.0f);
//		//pVtx[3].pos = D3DXVECTOR3(HP_X_Right2 - hp[1].posX, HP_Y_Right2, 0.0f);
//
//
//		//pVtx[0].rhw = 1.0f;												//���W�ϊ��p�W��
//		//pVtx[1].rhw = 1.0f;
//		//pVtx[2].rhw = 1.0f;
//		//pVtx[3].rhw = 1.0f;
//
//		//pVtx[0].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);				//���_�J���[�i�q�C�f�C�a�C�`�j
//		//pVtx[1].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		//pVtx[2].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		//pVtx[3].col = D3DCOLOR_RGBA(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//
//		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);							//�e�N�X�`���̂t�u���W�i�t�C�u�j
//		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		//m_VertexBuffer->Unlock();              //���b�N�̉���
//
//	}
//
//		m_pHPbar->UpdateAll();
//
//}
//
//
///******************************************************************************
//**	�֐���: �`�揈�� Draw
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: void
//**	����  :
//******************************************************************************/
//void HPbar::Draw()
//{
//
//	cntID2++;
//	if (cntID2 == 1)
//	{
//		m_ID = ID_0;
//	}
//	else
//	{
//		cntID2 = 0;
//		m_ID = ID_1;
//	}
//
//
//	/* �}�g���b�N�X���� */
//	// �v���W�F�N�V����
//	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
//	glLoadIdentity();
//	glOrtho(0.0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, 0.0, 1.0);
//
//	// ���f���r���[
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glLoadIdentity();
//
//
//	/* �l�p�`�`�� */
//	//// �e�N�X�`��
//	//glEnable(GL_TEXTURE_2D);
//	//glBindTexture(GL_TEXTURE_2D, m_Texture);
//
//	// �A���t�@�u�����h�ݒ�
//	glEnable(GL_BLEND);
//	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDisable(GL_DEPTH_TEST);
//
//	// ���C�g�̖�����
//	glDisable(GL_LIGHTING);
//
//
//	glBegin(GL_TRIANGLE_STRIP);
//
//	if (m_ID == 0)
//	{
//		glColor4f(hp[0].colR, hp[0].colG, hp[0].colB, 255);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2d(HP_X_Left + hp[0].posX, HP_Y_Left);
//
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2d(HP_X_Right, HP_Y_Left);
//
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2d(HP_X_Left + hp[0].posX, HP_Y_Right);
//
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2d(HP_X_Right, HP_Y_Right);
//	}
//	else if (m_ID == 1)
//	{
//	/*	glColor4f(hp[1].colR, hp[1].colG, hp[1].colB, 255);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2d(HP_X_Left2, HP_Y_Left2);
//
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2d(HP_X_Right2 - hp[1].posX, HP_Y_Left2);
//
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2d(HP_X_Left2, HP_Y_Right2);
//
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2d(HP_X_Right2 - hp[1].posX, HP_Y_Right2);*/
//	}
//
//	glEnd();
//
//	/*glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);*/
//	glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
//
//	/* �}�g���b�N�X�����ɖ߂� */
//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();
//
//	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();
//
//	m_pHPbar->DrawAll();
//
//}
//
///******************************************************************************
//**	�֐���: Create
//**		�֐��̊T�v
//**	����  : void
//**	�߂�l: HPbarFrame *
//**	����  : ���������� Scene2D�|�C���^�A���s�� NULL
//******************************************************************************/
//HPbar *HPbar::Create()
//{
//	HPbar *p;
//	p = new HPbar;
//	p->Init();
//	return p;
//}
//
//

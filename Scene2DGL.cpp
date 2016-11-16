/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Scene2DL.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/2/22
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Scene2DGL.h"
#include "main.h"
#include "ImageTGA.h"


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
Scene2DGL::Scene2DGL( int Priority ) : SceneGL( Priority )
{
}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Scene2DGL::~Scene2DGL()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  : void
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT Scene2DGL::Init()
{

	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int Scene2DGL::Uninit()
{

	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Scene2DGL::Update()
{
}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Scene2DGL::Draw()
{
	// �G���[���
	if( m_Texture == EOF )
	{
		return;

	}

	/* �}�g���b�N�X���� */
	// �v���W�F�N�V����
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0.0, ( GLdouble )SCREEN_WIDTH, ( GLdouble )SCREEN_HEIGHT, 0.0, 0.0, 1.0 );

	// ���f���r���[
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();


	/* �l�p�`�`�� */
	// �e�N�X�`��
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Texture );

	// �A���t�@�u�����h�ݒ�
	glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_DST_ALPHA );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_DEPTH_TEST );

	// ���C�g�̖�����
	glDisable( GL_LIGHTING );


	glBegin( GL_TRIANGLE_STRIP );

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d( m_Obj3d.pos.x - m_Obj3d.width * 0.5f, m_Obj3d.pos.y + m_Obj3d.height * 0.5f );
	
	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( m_Obj3d.pos.x + m_Obj3d.width * 0.5f, m_Obj3d.pos.y + m_Obj3d.height * 0.5f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d( m_Obj3d.pos.x - m_Obj3d.width * 0.5f, m_Obj3d.pos.y - m_Obj3d.height * 0.5f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( m_Obj3d.pos.x + m_Obj3d.width * 0.5f, m_Obj3d.pos.y - m_Obj3d.height * 0.5f );

	glEnd();

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );

	/* �}�g���b�N�X�����ɖ߂� */
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

}


/******************************************************************************
**	�֐���: Create
**		�֐��̊T�v
**	����  : void
**	�߂�l: Scene2DGL *
**	����  : ���������� Scene2D�|�C���^�A���s�� NULL
******************************************************************************/
Scene2DGL *Scene2DGL::Create()
{
	Scene2DGL *p;
	p = new Scene2DGL;

	if FAILED( p->Init() )
	{
		delete p;
		return NULL;

	}

	else return p;

}



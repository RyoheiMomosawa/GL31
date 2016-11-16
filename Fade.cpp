/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����:  Fade.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/19
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Fade.h"

// �V�X�e��
#include "Mode.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "main.h"
#include "Manager.h"

// �I�u�W�F�N�g
#include "Color.h"


/******************************************************************************
**	�}�N����`
******************************************************************************/


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
unsigned int Fade::m_Texture;
Color Fade::m_color;
FADE Fade::m_fade;
Mode *Fade::m_pModeNext;
int Fade::m_FadeTimeCount;
float Fade::m_Width;
float Fade::m_Height;


/******************************************************************************
**	�֐���: Fade
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
Fade::Fade()
{
}


/******************************************************************************
**	�֐���: ~Fade
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Fade::~Fade()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT Fade::Init()
{
	// �t�F�[�h�F�E�t�F�[�h�E���[�h�ݒ�
	m_color = Color( FADE_R, FADE_G, FADE_B, FADE_A );
	m_fade = FADE_IN;

	// �e��p�����[�^�ݒ�
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;


	// �J�E���g
	m_FadeTimeCount = 0;


	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int Fade::Uninit()
{
	// �摜�폜
	glDeleteTextures( GL_TEXTURE_2D, &m_Texture );
	
	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Fade::Update()
{
	/* �t�F�[�h�C�� */
	if( m_fade == FADE_IN )
	{
		if( m_FadeTimeCount > 30 )
		{
			/* ���l���Z */
			m_color.a -= 0.05f;

			// ���l��0.0f�ȉ��Ńt�F�[�h�m�[���ɐ؂�ւ�
			if( m_color.a <= 0.0f )
			{
				m_fade = FADE_NONE;

				// ���l�̐ݒ�
				m_color.a = 0.0f;

			}

		}
		else
		{
			m_FadeTimeCount++;

		}

	}
	// �t�F�[�h�A�E�g
	else if( m_fade == FADE_OUT )
	{
		// ���l���Z
		m_color.a += 0.02f;

		// ���l��1.0f�ȏ�ɂȂ������ʐ؂�ւ�
		if( m_color.a >= 1.0f )
		{
			// ���l��߂�
			m_color.a = 1.0f;

			// �t�F�[�h�C��
			m_fade = FADE_IN;

			// ��ʑJ�ڐ؂�ւ�
			Manager::SetMode( m_pModeNext );

		}

	}

}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Fade::Draw()
{
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

	glColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d( 0.0f, 0.0f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( m_Width, 0.0f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d( 0.0f, m_Height );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( m_Width, m_Height );

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
**	�֐���: Set
**	�֐��̊T�v
**	����  : Mode *next
**	�߂�l: void
**	����  :
******************************************************************************/
void Fade::Set( Mode *next )
{
	/* �t�F�[�h�E���[�h�̐؂�ւ� */
	m_fade = FADE_OUT;
	m_pModeNext = next;
	m_FadeTimeCount = 0;

}


/******************************************************************************
**	�֐���: Get
**	�֐��̊T�v
**	����  : void
**	�߂�l: FADE
**	����  :
******************************************************************************/
FADE Fade::Get()
{
	return m_fade;

}

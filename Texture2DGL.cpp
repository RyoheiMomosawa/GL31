/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: .cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016//
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/

// ���g�w�b�_
#include "Texture2DGL.h"


// �I�u�W�F�N�g


// �V�X�e��
#include "Color.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���: Texture2DGL
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
Texture2DGL::Texture2DGL()
{
}


/******************************************************************************
**	�֐���: ~Texture2DGL
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
Texture2DGL::~Texture2DGL()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT Texture2DGL::Init()
{
	return E_NOTIMPL;
}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int Texture2DGL::Uninit()
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
void Texture2DGL::Update()
{
}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::Draw()
{
	// �e�N�X�`��
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Texture );
	
	// �`��
	glBegin( GL_TRIANGLE_STRIP );

	glColor4f( m_Color.r, m_Color.g, m_Color.b, m_Color.a );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2d( m_Pos.x - m_Width * 0.5f, m_Pos.y + m_Height * 0.5f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2d( m_Pos.x + m_Width * 0.5f, m_Pos.y + m_Height * 0.5f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2d( m_Pos.x - m_Width * 0.5f, m_Pos.y - m_Height * 0.5f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2d( m_Pos.x + m_Width * 0.5f, m_Pos.y - m_Height * 0.5f );

	glEnd();

	// �e�N�X�`���폜
	glDisable( GL_TEXTURE_2D );

}


/******************************************************************************
**	�֐���: SetTexture
**	�֐��̊T�v
**	����  : int TextureNo
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetTexture( int TextureNo )
{
	m_Texture = TextureNo;

}


/******************************************************************************
**	�֐���: SetSize
**	�֐��̊T�v
**	����  : float width, float height
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetSize( float width, float height )
{
	m_Width = width;
	m_Height = height;

}


/******************************************************************************
**	�֐���: SetPos
**	�֐��̊T�v
**	����  : Vector3 * pos
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetPos( Vector3 * pos )
{
	m_Pos = *pos;

}


/******************************************************************************
**	�֐���: SetPos
**	�֐��̊T�v
**	����  : float x, float y
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetPos( float x, float y )
{
	m_Pos = Vector3( x, y, 0.0f );

}


/******************************************************************************
**	�֐���: SetRot
**	�֐��̊T�v
**	����  : float z
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetRot( float z )
{
	m_Rot = Vector3( 0.0f, 0.0f, z );

}


/******************************************************************************
**	�֐���: SetColor
**	�֐��̊T�v
**	����  : float r, float g, float b, float a
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetColor( float r, float g, float b, float a )
{
	m_Color = Color( r, g, b, a );

}


/******************************************************************************
**	�֐���: SetColor
**	�֐��̊T�v
**	����  : Color col
**	�߂�l: void
**	����  :
******************************************************************************/
void Texture2DGL::SetColor( Color col )
{
	m_Color = col;

}

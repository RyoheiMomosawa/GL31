/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Renderer.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/4/22
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "RendererGL.h"


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
HDC RendererGL::m_hDC;
HGLRC RendererGL::m_hGLRC;
Color RendererGL::m_BgCol;


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
RendererGL::RendererGL()
{
}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
RendererGL::~RendererGL()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT RendererGL::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// �f�o�C�X�R���e�L�X�g�̎擾
	m_hDC = GetDC( hWnd );

	// �s�N�Z���t�H�[�}�b�g(OpenGL�̏����f�[�^)
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof PIXELFORMATDESCRIPTOR , // pfd�̃T�C�Y
		1 , // �o�[�W����
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER , // �`��ݒ�
		PFD_TYPE_RGBA , // �`����@�̐F�w��
		32 , // �F�̃o�b�t�@�T�C�Y
		0 ,0 ,0 ,0 ,0, 0 ,0, 0, // RGBA�̃o�b�t�@�T�C�Y�ƃV�t�g(?)
		0, 0, 0, 0, 0, // RGBA AccumBits
		24, // ���s���o�b�t�@
		8, // �X�e���V���o�b�t�@
		0, // �I�[�f�B�I�o�b�t�@
		PFD_MAIN_PLANE, // ���C���[�^�C�v
		0, // Reserved
		0, 0, 0 // ���C���[�A�r�W�u���A�_���[�W �}�X�N

	};

	/* OpenGL Init */
	// �s�N�Z���A�J�����g�R���e�N�X�g�̐ݒ�
	m_nFormat = ChoosePixelFormat( m_hDC, &pfd );
	if( m_nFormat == NULL )
	{
		// 0���A���Ă�����G���[��Ԃ�
		return E_FAIL;

	}
	if( !SetPixelFormat( m_hDC, m_nFormat, &pfd ) )
	{
		// �Z�b�g���s���ɃG���[��Ԃ�
		return E_FAIL;

	}
	m_hGLRC = wglCreateContext( m_hDC );
	wglMakeCurrent( m_hDC, m_hGLRC );


	/* ���s�`�攻�菈�� */
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	

	/* �F */
	m_BgCol = Color( BGCOLOR_R, BGCOLOR_G, BGCOLOR_B, BGCOLOR_A );


	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
int RendererGL::Uninit()
{
	// �J�����g�R���e�L�X�g�̖�����
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hGLRC );

	// DC���폜
	DeleteDC( m_hDC );


	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::Update()
{
}


/******************************************************************************
**	�֐���: BeginDraw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
bool RendererGL::BeginDraw()
{
	/* ��ʂ̃N���A */
	glClearColor( m_BgCol.r, m_BgCol.g, m_BgCol.b, m_BgCol.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	wglMakeCurrent( m_hDC, m_hGLRC );

	return true;

}


/******************************************************************************
**	�֐���: EndDraw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::EndDraw()
{
	// �`�揈��
	glFlush();
	SwapBuffers( m_hDC );

}


/******************************************************************************
**	�֐���: GetHDC
**	�֐��̊T�v
**	����  : void
**	�߂�l: HDC
**	����  : �f�o�C�X�R���e�L�X�g�̎擾
******************************************************************************/
HDC RendererGL::GetHDC()
{
	return m_hDC;
}


/******************************************************************************
**	�֐���: GetHGLRC
**	�֐��̊T�v
**	����  : void
**	�߂�l: HGLRC
**	����  : OpenGL�̃f�o�C�X���擾
******************************************************************************/
HGLRC RendererGL::GetHGLRC()
{
	return m_hGLRC;
}


/******************************************************************************
**	�֐���: SetRenderMode
**	�֐��̊T�v
**	����  : GLRENDERSTATE glrs, DWORD value
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::SetRenderMode( GLRENDERSTATE glrs, DWORD value )
{
	DWORD set;

	switch( glrs )
	{
		case GLRS_FILLMODE:
			switch( value )
			{
				case GLFILL_POINT:
					set = GL_POINT;

					break;


				case GLFILL_WIREFRAME:
					set = GL_LINE;

					break;


				case GLFILL_SOLID:
					set = GL_FILL;

					break;


				default:
					
					break;


			}
			glPolygonMode( GL_FRONT_AND_BACK, set );

			break;


		default:
			
			break;


	}

}


/******************************************************************************
**	�֐���: SetRenderMode
**	�֐��̊T�v
**	����  : DWORD glrs, GLboolean value
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::SetRenderMode( DWORD glrs, GLboolean value )
{
}


/******************************************************************************
**	�֐���: SetBgColor
**	�֐��̊T�v
**	����  : float r, float g, float b, float a
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::SetBgColor( float r, float g, float b, float a )
{
	m_BgCol = Color( r, g, b, a );

}


/******************************************************************************
**	�֐���: SetBgColor
**	�֐��̊T�v
**	����  : Color *col
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::SetBgColor( Color *col )
{
	m_BgCol = *col;

}


/******************************************************************************
**	�֐���: SetBgColor
**	�֐��̊T�v
**	����  : unsigned long col
**	�߂�l: void
**	����  :
******************************************************************************/
void RendererGL::SetBgColor( unsigned long col )
{
	m_BgCol = col;

}


/******************************************************************************
**	�֐���: GetBgColor
**	�֐��̊T�v
**	����  : void
**	�߂�l: Color
**	����  :
******************************************************************************/
Color RendererGL::GetBgColor()
{
	return m_BgCol;

}





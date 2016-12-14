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
#include "SceneGL.h"

// �I�u�W�F�N�g


// �V�X�e��
#include "ImageTGA.h"
#include "main.h"
#include <Windows.h>


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
DWORD SceneGL::m_dwCreateCnt = 0;
SceneGL *SceneGL::m_Top[ PRIORITY_MAX ] = {};
SceneGL *SceneGL::m_Last[ PRIORITY_MAX ] = {};


/******************************************************************************
**	�֐���:�@SceneGL
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
SceneGL::SceneGL( int Priority )
{
	// ������
	ZeroMemory( &m_Obj3d, sizeof OBJECT3D );
	m_Obj3d.pos = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.accPos = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.rot = Vector3( 0.0f, 0.0f, 0.0f );
	m_Obj3d.scl = Vector3( 1.0f, 1.0f, 1.0f );
	m_Obj3d.normal = Vector3( 0.0f, 1.0f, 0.0f );
	m_Obj3d.col = Color( 1.0f, 1.0f, 1.0f, 1.0f );
	m_Obj3d.width = 0.0f;
	m_Obj3d.height = 0.0f;
	m_Obj3d.depth = 0.0f;
	m_Obj3d.length2D = m_Obj3d.length3D = 0.0f;
	m_Obj3d.bUse = m_Obj3d.bUpdate = m_Obj3d.bDraw = false;
	m_Obj3d.anim.fPattern_X = m_Obj3d.anim.fPattern_Y = 1.0f;
	m_Obj3d.anim.fAnimWidth = m_Obj3d.anim.fAnimHeight = 1.0f;
	m_Obj3d.anim.nChangeTimming = 1;

	m_Obj3d.movestate = MOVESTATE_NONE;
	m_bCreate = false;
	m_pTexPath = NULL;
	m_Texture = EOF;

	// ���X�g�o�^
	if( m_Top[ Priority ] == NULL )
	{
		// �����ݒ�
		m_Top[ Priority ] = m_Last[ Priority ] = this;
		m_Prev = m_Next = NULL;

	}
	else
	{
		m_Prev = m_Last[ Priority ]; // �����̑O�|�C���^�ɍŌ�̃|�C���^����
		m_Last[ Priority ] = m_Last[ Priority ]->m_Next = this; // ����|�C���^�ƑO�f�[�^->�|�C���^�Ɏ����̃|�C���^����
		m_Next = NULL;

	}

	// ����������J�E���g
	m_dwCreateCnt++;

}


/******************************************************************************
**	�֐���: ~SceneGL
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
SceneGL::~SceneGL()
{
	if( this != NULL )
	{
		m_dwCreateCnt--;
		this->DeleteTexture();

	}
	else
	{
		// NULL���폜���悤�Ƃ�����I������
		MessageBox( GetHWND(), "�Q�Ƃ��ꂽ�l��NULL�ł���", "����!", MB_OK | MB_ICONERROR );
		PostQuitMessage( 0 );

	}

}


/******************************************************************************
**	�֐���: InitAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: HRESULT
**	����  :
******************************************************************************/
HRESULT SceneGL::InitAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];

		while( scene != NULL )
		{
			scene->Init();
			scene = scene->m_Next;

		}

	}

	return S_OK;

}


/******************************************************************************
**	�֐���: UninitAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int SceneGL::UninitAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];
		SceneGL *next;

		while( scene != NULL )
		{
			next = scene->m_Next;
			scene->Uninit();
			scene->DeleteTexture();
			delete scene;
			scene = next;

		}

		scene = NULL;
		m_Top[ i ] = NULL;
		m_Last[ i ] = NULL;

	}


	return 0;

}


/******************************************************************************
**	�֐���: UpdateAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::UpdateAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];
		SceneGL *next;

		while( scene != NULL )
		{
			next = scene->m_Next;
			scene->GetObject3D()->bUse && scene->GetObject3D()->bUpdate ? scene->Update() : false;
			scene = next;

		}

	}


}


/******************************************************************************
**	�֐���: DrawAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::DrawAll()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		auto *scene = m_Top[ i ];

		while( scene != NULL )
		{
			scene->GetObject3D()->bUse && scene->GetObject3D()->bUpdate ? scene->Draw() : false;
			scene = scene->m_Next;

		}

	}

}


/******************************************************************************
**	�֐���: Release
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::Release()
{
	for( int i = 0; i < PRIORITY_MAX; i++ )
	{
		if( this == m_Top[ i ] )
		{
			m_Top[ i ] = m_Next;
			m_Next->m_Prev = NULL;

		}
		else if( this == m_Last[ i ] )
		{
			m_Last[ i ] = m_Prev;
			m_Prev->m_Next = NULL;

		}
		else
		{
			m_Prev->m_Next = m_Next;
			m_Next->m_Prev = m_Prev;

		}

	}

	delete this;

}


/******************************************************************************
**	�֐���: GetObject3D
**	�֐��̊T�v
**	����  : void
**	�߂�l: OBJECT3D
**	����  :
******************************************************************************/
OBJECT3D* SceneGL::GetObject3D()
{
	return &this->m_Obj3d;

}


/******************************************************************************
**	�֐���: SetObject3D
**	�֐��̊T�v
**	����  : OBJECT3D
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::SetObject3D( OBJECT3D obj3d )
{
	this->m_Obj3d = obj3d;

}


/******************************************************************************
**	�֐���: SetTexture
**		�֐��̊T�v
**	����  : const char *
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SceneGL::SetTexture( const char *pFilePath )
{
	// �e�N�X�`���ݒ�
	if( m_Texture == EOF )
	{
		ImageTGA cTexture;
		m_Texture = cTexture.CreateTexture( pFilePath );

	}
	// �f�[�^�������Ă���ꍇ�͍폜���Ă���ǂݍ���
	else
	{
		DeleteTexture();
		ImageTGA cTexture;
		m_Texture = cTexture.CreateTexture( pFilePath );

	}

	// �t�@�C�������邩�ǂ������ׂ�
	if( m_Texture != NULL )
	{
		m_pTexPath = ( char * )pFilePath;
		return true;

	}
	else
	{
		// �����ꍇ��false��Ԃ�
		m_pTexPath = NULL;
		m_Texture = EOF;
		return false;

	}

}


/******************************************************************************
**	�֐���: SetParam
**	�֐��̊T�v
**	����  : float *x, float *y, float *z, SCENEPARAM ParamName
**	�߂�l: void
**	����  : SIZE�̏ꍇ�Ax = width, y = height, z = depth �ƂȂ�
******************************************************************************/
void SceneGL::SetParam( float *x, float *y, float *z, SCENEPARAM ParamName )
{
	switch( ParamName )
	{
		// vec��NULL���ɂ͏��������Ȃ�
		case SCENEPARAM_POS:
			m_Obj3d.pos.x = x == NULL ? m_Obj3d.pos.x : *x;
			m_Obj3d.pos.y = y == NULL ? m_Obj3d.pos.y : *y;
			m_Obj3d.pos.z = z == NULL ? m_Obj3d.pos.z : *z;

			break;

		case SCENEPARAM_ROT:
			m_Obj3d.rot.x = x == NULL ? m_Obj3d.rot.x : *x;
			m_Obj3d.rot.y = y == NULL ? m_Obj3d.rot.y : *y;
			m_Obj3d.rot.z = z == NULL ? m_Obj3d.rot.z : *z;

			break;

		case SCENEPARAM_SCL:
			m_Obj3d.scl.x = x == NULL ? m_Obj3d.scl.x : *x;
			m_Obj3d.scl.y = y == NULL ? m_Obj3d.scl.y : *y;
			m_Obj3d.scl.z = z == NULL ? m_Obj3d.scl.z : *z;

			break;

		case SCENEPARAM_SIZE:
			m_Obj3d.width = x == NULL ? m_Obj3d.width : *x;
			m_Obj3d.height = y == NULL ? m_Obj3d.height : *y;
			m_Obj3d.depth = z == NULL ? m_Obj3d.depth : *z;

			break;

		default:

			break;

	}

}


/******************************************************************************
**	�֐���: SetParam
**	�֐��̊T�v
**	����  : D3DXVECTOR3 *, SCENEPARAM ParamName
**	�߂�l: void
**	����  : SIZE�̏ꍇ�Ax = width, y = height, z = depth �ƂȂ�
******************************************************************************/
void SceneGL::SetParam( Vector3 *vec, SCENEPARAM ParamName )
{
	// vec��NULL���ɂ͏��������Ȃ�
	if( vec == NULL ) return;

	switch( ParamName )
	{
		case SCENEPARAM_POS:
			m_Obj3d.pos = *vec;

			break;

		case SCENEPARAM_ROT:
			m_Obj3d.rot = *vec;

			break;

		case SCENEPARAM_SCL:
			m_Obj3d.scl = *vec;

			break;

		case SCENEPARAM_SIZE:
			m_Obj3d.width = vec->x;
			m_Obj3d.height = vec->y;
			m_Obj3d.depth = vec->z;

			break;

		default:

			break;

	}

}


/******************************************************************************
**	�֐���: SetColor
**	�֐��̊T�v
**	����  :  float *r, float *g, float *b, float *a
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::SetColor( float *r, float *g, float *b, float *a )
{
	m_Obj3d.col = Color(
		r == nullptr ? m_Obj3d.col.r : *r,
		g == nullptr ? m_Obj3d.col.g : *g,
		b == nullptr ? m_Obj3d.col.b : *b,
		a == nullptr ? m_Obj3d.col.a : *a );

}


/******************************************************************************
**	�֐���: SetColor
**	�֐��̊T�v
**	����  :  float *r, float *g, float *b, float *a
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::SetColor( Color *col )
{
	if( col == nullptr ) return;
	m_Obj3d.col = *col;

}


/******************************************************************************
**	�֐���: SetAnimation
**	�֐��̊T�v
**	����  : int ChangeTim, float PatternX, float PatternY
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::SetAnimation( int ChangeTim, float PatternX, float PatternY )
{
	m_Obj3d.anim.nChangeTimming = ChangeTim;
	m_Obj3d.anim.fPattern_X = PatternX;
	m_Obj3d.anim.fPattern_Y = PatternY;
	m_Obj3d.anim.fAnimWidth = 1.0f / ( m_Obj3d.anim.fPattern_X / m_Obj3d.anim.fPattern_Y );
	m_Obj3d.anim.fAnimHeight = 1.0f / m_Obj3d.anim.fPattern_Y;

}


/******************************************************************************
**	�֐���: DeleteTexture
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGL::DeleteTexture()
{
	glDeleteTextures( GL_TEXTURE_2D, ( unsigned int * )&m_Texture );
	m_Texture = EOF;

}

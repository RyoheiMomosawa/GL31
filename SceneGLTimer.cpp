/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: SceneTimer.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/6/22
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "SceneGLTimer.h"
#include "Manager.h"


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
SceneGLTimer::SceneGLTimer( int Priority ) : SceneGL( Priority )
{
	m_pNumber = NULL;
	m_Time = 0;
	m_nDigit = 0;
	
}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
SceneGLTimer::~SceneGLTimer()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  :
**	�߂�l: HRESULT
**	����  : ����������
******************************************************************************/
HRESULT SceneGLTimer::Init()
{
	// �����ς݂Ȃ珈�����Ȃ�
	if( m_bCreate ) return S_OK;

	int time = m_Time;
	int digit;


	// ���𑜓x�^�C�}�[�̏�����
	if( FAILED( m_QPCntr.Init() ) )
	{
		// �������Ɏ��s
		return E_FAIL;

	}
	m_QPCntr.SetTimmerMs( 60, CHECKMETHOD_REPETITION );



	// �����ς�
	m_bCreate = true;


	return S_OK;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int SceneGLTimer::Uninit()
{
	for( int i = 0; i < m_nDigit; i++ )
	{
		m_pNumber[ i ].Uninit();

	}
	delete[] m_pNumber;

	m_QPCntr.ResetTimmer();
	m_Time = 0;

	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGLTimer::Update()
{
	int time = m_Time;
	int s;

	// �^�C�}�[�I��
	if( m_QPCntr.c_bRanTimmer == false )
	{
		m_QPCntr.StartTimmer();

	}

	// �^�C�}�[���u0�v�ɂȂ�����X�g�b�v
	if( m_Time <= 0 )
	{
		m_QPCntr.StopTimmer();

	}

#ifdef _DEBUG
	if( Manager::GetKeyboard()->GetRepeat( DIK_0 ) )
	{
		m_Time++;

	}
	else if( Manager::GetKeyboard()->GetRepeat( DIK_9 ) )
	{
		m_Time--;

	}

#endif // _DEBUG

	// �^�C�}�[�̌��Z
	if( m_QPCntr.CheckTimmer() )
	{
		m_Time--;

	}

	// ���l�̃Z�b�g
	for( int i = 0; i < m_nDigit; i++ )
	{
		// ���l�̃Z�b�g
		s = powl( 10, ( m_nDigit - i - 1 ) );
		m_pNumber[ i ].SetNumber( time / s );
		time = time % s;
		m_pNumber[ i ].Update();

	}


}


/******************************************************************************
**	�֐���: �`�揈�� Draw
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGLTimer::Draw()
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

	// ���l�̕`��
	for( int i = 0; i < m_nDigit; i++ )
	{
		m_pNumber[ i ].Draw();

	}

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
**	�֐��̊T�v
**	����  : void 
**	�߂�l: SceneGLTimer *
**	����  :
******************************************************************************/
SceneGLTimer *SceneGLTimer::Create()
{
	SceneGLTimer *p;
	p = new SceneGLTimer;

	if FAILED( p->Init() )
	{
		delete p;
		return NULL;

	}

	else return p;

}


/******************************************************************************
**	�֐���: GetTimer
**	�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int SceneGLTimer::GetTimer()
{
	return m_Time;

}


/******************************************************************************
**	�֐���: SetTimer
**	�֐��̊T�v
**	����  : int time
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGLTimer::SetTimer( int time )
{
	m_Time = time;

}



/******************************************************************************
**	�֐���: SetDigit
**	�֐��̊T�v
**	����  : int num
**	�߂�l: void
**	����  :
******************************************************************************/
void SceneGLTimer::SetDigit( int num )
{
	m_nDigit = num;

}


/******************************************************************************
**	�֐���: Reset
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
HRESULT SceneGLTimer::Reset()
{
	// �^�C�}�[���������Ȃ琶������
	if( m_pNumber == NULL )
	{
		m_pNumber = new Number[ m_nDigit ];
		for( int i = 0; i < m_nDigit; i++ )
		{
			if( FAILED( m_pNumber[ i ].Init() ) )
			{
				return E_FAIL;

			}

		}

	}
	// �폜���Ă��琶��
	else
	{
		for( int i = 0; i < m_nDigit; i++ )
		{
			m_pNumber[ i ].Uninit();

		}
		delete[] m_pNumber;

		// �Đ���
		m_pNumber = new Number[ m_nDigit ];
		for( int i = 0; i < m_nDigit; i++ )
		{
			if( FAILED( m_pNumber[ i ].Init() ) )
			{
				return E_FAIL;

			}

		}

	}


	// �p�����[�^����
	int time = m_Time;
	int digit;
	float width = m_Obj3d.width * 0.5f;
	Vector3 pos;
	pos = m_Obj3d.pos;
	pos.x = m_Obj3d.pos.x - width * ( m_nDigit - 1 );
	for( int i = 0; i < m_nDigit; i++ )
	{
		// �e��p�����[�^�ݒ�
		// �ʒu
		m_pNumber[ i ].SetPos( &pos );
		// ��
		m_pNumber[ i ].SetSize( m_Obj3d.width, m_Obj3d.height );
		// �F
		m_pNumber[ i ].SetColor( &m_Obj3d.col );
		// ��
		digit = powl( 10, ( m_nDigit - i - 1 ) );
		m_pNumber[ i ].SetNumber( time / digit );
		time = time % digit;

		// �����̈ʒu�X�V
		pos.x += width * 2.0f;

	}


	return S_OK;

}

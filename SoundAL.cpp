/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: SoundAL.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/6/20
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "SoundAL.h"
#include <string.h>


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
SOUND_SOURCE *SoundAL::m_pSource; // �X�s�[�J�[
SOUND_BUFFERDATA *SoundAL::m_pSoundBuffData; // ���f�[�^
int SoundAL::m_CreateSource; // �\�[�X�̐�����
int SoundAL::m_CreateBuffer; // �o�b�t�@�̐�����
bool SoundAL::m_bInit; // ���������Ă��邩


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
SoundAL::SoundAL()
{
	m_pSource = NULL;
	m_pSoundBuffData = NULL;
	m_CreateBuffer = m_CreateSource = 0;
	m_bInit = false;

}


/******************************************************************************
**	�֐���:
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
SoundAL::~SoundAL()
{
}


/******************************************************************************
**	�֐���: ���������� Init
**		�֐��̊T�v
**	����  : void
**	�߂�l: bool
**	����  : ����������
******************************************************************************/
bool SoundAL::Init()
{
	if( !m_bInit )
	{
		alutInit( NULL, NULL );
		m_bInit = true;

	}
	m_pSource = NULL;
	m_pSoundBuffData = NULL;
	m_CreateBuffer = m_CreateSource = 0;

	return true;

}


/******************************************************************************
**	�֐���: �I������ Uninit
**		�֐��̊T�v
**	����  : void
**	�߂�l: int
**	����  :
******************************************************************************/
int SoundAL::Uninit()
{
	// �\�[�X
	if( m_pSource != NULL )
	{
		delete[] m_pSource;
		m_pSource = NULL;
		m_CreateSource = 0;

	}
	else
	{
		return 1;

	}

	// �\�[�X
	if( m_pSoundBuffData != NULL )
	{
		// �t�@�C�����폜
		for( int i = 0; i < m_CreateBuffer; i++ )
		{
			delete[] m_pSoundBuffData[ i ].pFileName;
			m_pSoundBuffData[ i ].pFileName = NULL;

		}

		delete[] m_pSoundBuffData;
		m_pSoundBuffData = NULL;
		m_CreateBuffer = 0;

	}
	else
	{
		return 1;

	}

	if( m_bInit )
	{
		alutExit();
		m_bInit = false;

	}

	return 0;

}


/******************************************************************************
**	�֐���: �X�V���� Update
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::Update()
{
	int value = 0;
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alGetSourcei( m_pSource[ i ].source, AL_SOURCE_STATE, &value );
			if( value == AL_STOPPED )
			{
				printf( "�Đ��I��" );
				alSourcei( m_pSource[ i ].source, AL_INITIAL, NULL );
				m_pSource[ i ].bUse = false;
				m_pSource[ i ].bPlay = false;

			}
			else if( value == AL_PAUSED )
			{
				m_pSource[ i ].bPlay = false;

			}

		}

	}

}


/******************************************************************************
**	�֐���: CreateSource
**	�֐��̊T�v
**	����  : ALuint value
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::CreateSource( ALuint value )
{
	// �������̊m�F
	if( m_pSource == NULL )
	{
		m_CreateSource = value;
		m_pSource = new SOUND_SOURCE[ m_CreateSource ];
		alGenSources( m_CreateSource, &m_pSource[ 0 ].source );
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			m_pSource[ i ].bUse = false;
			m_pSource[ i ].bPlay = false;

		}
		return true;

	}

	// �����Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: CreateBuffer
**	�֐��̊T�v
**	����  : ALuint value
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::CreateBuffer( ALuint value )
{
	// �������̊m�F
	if( m_pSoundBuffData == NULL )
	{
		m_CreateBuffer = value;
		m_pSoundBuffData = new SOUND_BUFFERDATA[ m_CreateBuffer ];
		for( ALuint i = 0; i < m_CreateBuffer; i++ )
		{
			m_pSoundBuffData[ i ].buffer = 0;
			m_pSoundBuffData[ i ].id = 0;
			m_pSoundBuffData[ i ].pFileName = 0;

		}
		return true;
	}

	// �����Ɏ��s
	return false;
}


/******************************************************************************
**	�֐���: CreateBufferData
**	�֐��̊T�v
**	����  : const char *pFileName, ALuint *out_ID, ALboolean Loop = AL_FALSE
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::CreateBufferData( const char *pFileName, ALuint *out_ID, ALboolean Loop = AL_FALSE )
{
	// �t�@�C���I�[�v��
	ALuint buffer;
	buffer = alutCreateBufferFromFile( pFileName );

	// �f�[�^�����ɐ���
	if( buffer != 0 )
	{
		for( ALuint i = 0; i < m_CreateBuffer; i++ )
		{
			if( m_pSoundBuffData[ i ].buffer == NULL )
			{
				int nFileNameLen = strnlen_s( pFileName, 256 );
				m_pSoundBuffData[ i ].buffer = buffer;
				m_pSoundBuffData[ i ].id = i;
				m_pSoundBuffData[ i ].pFileName = new char[ nFileNameLen + 1 ];
				strcpy_s( m_pSoundBuffData[ i ].pFileName, nFileNameLen + 1, pFileName );
				m_pSoundBuffData[ i ].bLoop = Loop;

				// ID�̕ԋp
				*out_ID = i;

				return true;

			}

		}

	}

	// �����Ɏ��s
	*out_ID = -1;
	return false;

}


/******************************************************************************
**	�֐���: DeleteSource
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::DeleteSource( ALuint id )
{
}


/******************************************************************************
**	�֐���: DeleteBuffer
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::DeleteBuffer( ALuint id )
{
}


/******************************************************************************
**	�֐���: DeleteSourceAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::DeleteSourceAll()
{
	delete[] m_pSource;
	m_pSource = NULL;

}


/******************************************************************************
**	�֐���: DeleteBufferAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::DeleteBufferAll()
{
	// �t�@�C�����폜
	for( int i = 0; i < m_CreateBuffer; i++ )
	{
		delete[] m_pSoundBuffData[ i ].pFileName;
		m_pSoundBuffData[ i ].pFileName = NULL;

	}

	delete[] m_pSoundBuffData;
	m_pSoundBuffData = NULL;

}


/******************************************************************************
**	�֐���: SetBuffer
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::SetBuffer( ALuint id )
{
	// �w�肳�ꂽID�͈͓̔��`�F�b�N
	if( id < m_CreateBuffer )
	{
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			// ���g�p�`�F�b�N
			if( !m_pSource[ i ].bUse )
			{
				alSourcei( m_pSource[ i ].source, AL_BUFFER, m_pSoundBuffData[ id ].buffer );
				alSourcei( m_pSource[ i ].source, AL_LOOPING, m_pSoundBuffData[ id ].bLoop );
				m_pSource[ i ].bUse = true;
				return true;

			}

		}

	}

	// �Z�b�g�Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: SetBuffer
**	�֐��̊T�v
**	����  : ALuint id, ALboolean Loop
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::SetBuffer( ALuint id, ALboolean Loop )
{
	// �w�肳�ꂽID�͈͓̔��`�F�b�N
	if( id < m_CreateBuffer )
	{
		for( ALuint i = 0; i < m_CreateSource; i++ )
		{
			// ���g�p�`�F�b�N
			if( !m_pSource[ i ].bUse )
			{
				alSourcei( m_pSource[ i ].source, AL_BUFFER, m_pSoundBuffData[ id ].buffer );
				alSourcei( m_pSource[ i ].source, AL_LOOPING, Loop );
				m_pSource[ i ].bUse = true;
				return true;

			}

		}

	}

	// �Z�b�g�Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: SetLoop
**	�֐��̊T�v
**	����  : ALuint BufferID, int Loop
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::SetLoop( ALuint BufferID, int Loop )
{
	// �w�肳�ꂽID�͈͓̔��`�F�b�N
	if( BufferID < m_CreateBuffer )
	{
		m_pSoundBuffData[ BufferID ].bLoop = Loop;
		alSourcei( m_pSource[ BufferID ].source, AL_LOOPING, Loop );

	}

}


/******************************************************************************
**	�֐���: PlaySound
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::PlaySoundAL( ALuint id )
{
	// �w�肳�ꂽID�͈͓̔��`�F�b�N
	if( id < m_CreateSource )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ id ].bUse && !m_pSource[ id ].bPlay )
		{
			alSourcePlay( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = true;
			return true;

		}

	}

	// �Z�b�g�Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: PlaySoundAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::PlaySoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ i ].bUse && !m_pSource[ i ].bPlay )
		{
			alSourcePlay( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = true;

		}

	}	

}


/******************************************************************************
**	�֐���: StopSound
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::StopSound( ALuint id )
{
	if( id < m_CreateSource )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ id ].bUse && m_pSource[ id ].bPlay )
		{
			alSourceStop( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = false;
			m_pSource[ id ].bUse = false;
			return true;

		}

	}

	// �Z�b�g�Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: StopSoundAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::StopSoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alSourceStop( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = false;
			m_pSource[ i ].bUse = false;

		}

	}

}


/******************************************************************************
**	�֐���: PauseSound
**	�֐��̊T�v
**	����  : ALuint id
**	�߂�l: bool
**	����  :
******************************************************************************/
bool SoundAL::PauseSound( ALuint id )
{
	if( id < m_CreateSource )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ id ].bUse && m_pSource[ id ].bPlay )
		{
			alSourcePause( m_pSource[ id ].source );
			m_pSource[ id ].bPlay = false;
			return true;

		}

	}

	// �Z�b�g�Ɏ��s
	return false;

}


/******************************************************************************
**	�֐���: PauseSoundAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void SoundAL::PauseSoundAll()
{
	for( ALuint i = 0; i < m_CreateSource; i++ )
	{
		// �g�p�`�F�b�N
		if( m_pSource[ i ].bUse && m_pSource[ i ].bPlay )
		{
			alSourcePause( m_pSource[ i ].source );
			m_pSource[ i ].bPlay = false;

		}

	}

}



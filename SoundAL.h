#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: SoundAL.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/6/20
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**	2016/6/24
**		�X�g�b�v�A�|�[�Y�@�\�ǉ��A�ׂ��ȃo�O�C��
**		���[�v�ݒ莞�ɑ����f�ł���悤�C��
**
**
******************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include <alut.h>
#include <stdio.h>


/******************************************************************************
**	���C�u���������N
******************************************************************************/
#pragma comment( lib, "OpenAL32.lib" )
#pragma comment( lib, "alut.lib" )


/******************************************************************************
**	�}�N����`
******************************************************************************/

/* �\�[�X */
typedef struct
{
	ALuint source;
	bool bUse; // �g�p���̗L��
	bool bPlay; // �Đ���

}SOUND_SOURCE;

/* �f�[�^�� */
typedef struct
{
	ALuint buffer; // �f�[�^��
	char *pFileName; // �t�@�C���l�[��
	ALuint id; // ���̃f�[�^��ID,0�`65535
	ALboolean bLoop;

}SOUND_BUFFERDATA;


/******************************************************************************
**	�N���X��`
******************************************************************************/
class SoundAL
{
public:
	SoundAL();
	virtual ~SoundAL();

	// ���\�b�h
	static bool Init();
	static int Uninit();
	static void Update();


	// Create
	static bool CreateSource( ALuint value );
	static bool CreateBuffer( ALuint value );
	static bool CreateBufferData( const char *pFileName, ALuint *out_id, ALboolean Loop );


	// Delete
	static void DeleteSource( ALuint id );
	static void DeleteBuffer( ALuint id );
	static void DeleteSourceAll();
	static void DeleteBufferAll();


	// Set
	static bool SetBuffer( ALuint id );
	static bool SetBuffer( ALuint id, ALboolean Loop );
	static void SetLoop( ALuint BufferID, int Loop );


	// Get


	// Play,Stop,Pause
	static bool PlaySoundAL( ALuint id );
	static void PlaySoundAll();
	static bool StopSound( ALuint id );
	static void StopSoundAll();
	static bool PauseSound( ALuint id );
	static void PauseSoundAll();


protected:
	// �����o�ϐ�
	static SOUND_SOURCE *m_pSource; // �X�s�[�J�[
	static SOUND_BUFFERDATA *m_pSoundBuffData; // ���f�[�^
	static int m_CreateSource; // �\�[�X�̐�����
	static int m_CreateBuffer; // �o�b�t�@�̐�����
	static bool m_bInit; // ���������Ă��邩

};


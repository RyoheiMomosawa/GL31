/******************************************************************************
	�^�C�g��  : ���𑜓x�^�C�}�[FPS
	�t�@�C����: QPCounter.h
	�쐬��    : AT-12A-244 �o�Ȕԍ� 16 �ؑ� �ˋM
	�쐬��    : 2015/7/20
	�o�[�W����: 1.0.1
******************************************************************************/

/******************************************************************************
	�X�V���e

	2015/7/28	ver1.0.0
				���𑜓x�^�C�}�[�d�l��FPS���T�|�[�g
				��L���g�p�o���Ȃ��ꍇ�͒�𑜓x���T�|�[�g����

	2015/7/29	ver1.0.1
				���𑜓x�^�C�}�[�̃T�|�[�g��C�ӂŕύX�ł���悤��
				�ύX�̍ۂ�"bool c_bPerformance"���ĂсA�l��������

	2015/9/22	ver.1.2.0
				�L�b�`���^�C�}�[����
				�w�肳�ꂽ���Ԃ�m�点��悤��
				���m�Ɏ��Ԏw��œ������������̂ɍœK

******************************************************************************/

/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#ifndef _QPCCOUNTER_H_
#define _QPCCOUNTER_H_


/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"

/******************************************************************************
	���C�u���������N
******************************************************************************/


/******************************************************************************
	�}�N����`
******************************************************************************/

/**** �}�W�b�N�i���o�[ ****/

/* FPS�l�Z�o�X�V�x */
#define FPSCOUNT ( 500 )

/* FPS�X�V�p�x */
#define FPS ( 60 )

/* �𑜓x�� */
#define PERFOEMANCE_FPS ( 1000 )


/**** �\���̐錾 ****/
typedef enum
{
	CHECKMETHOD_ONLY_ONCE = 0, // ���̂�
	CHECKMETHOD_REPETITION , // �J��Ԃ�
	CHECKMETHOD_REGINTVL , // ���Ԋu
	CHECKMETHOD_MAX

}CHECKMETHOD; // �^�C�}�[�̃`�F�b�N���@


/**** �N���X��` ****/
class QPCounter
{
	public :
		QPCounter();
		~QPCounter();

		/* �v���g�^�C�v�錾 */
		// FPS�A���𑜓x�^�C�}�[�̐ݒ�
		HRESULT Init( void );
		void SetFPS( int _nFPS = FPS );
		void SetPerfoemance( int nPerformance = PERFOEMANCE_FPS );
		void CountFPS( void );
		bool CallFPS( void ); // �X�V����^�C�~���O���ǂ���
		void EndFPS( void ); // �X�V�����Ō�̃^�C�~���O
		//int Ran( void );
		void DrawFPS();

		// �L�b�`���^�C�}�[
		bool SetTimmerMs( int ms , CHECKMETHOD cm ); // ms�P�ʂŎ��Ԍo�߂��v�鎞�Ԃ̃Z�b�g
		bool StartTimmer( void ); // �v���X�^�[�g
		bool CheckTimmer( void ); // �w�肳�ꂽ���Ԃ��o�߂������ǂ���
		bool StopTimmer( void ); // ���Ԃ��X�g�b�v
		bool RestartTimmer( void ); // ���Ԍo�߂����Z�b�g
		bool ResetTimmer( void ); // �w�肳�ꂽ���Ԃ����Z�b�g

		/* �ϐ��錾 */
		bool c_bPerformance; // ���𑜓x�^�C�}�[���d�l�ł��邩
		bool c_bRanTimmer; // �^�C�}�[�������Ă��邩


	private:
		DWORD c_nCntFPS; // ���݂�FPS�l
		DWORD c_nPerformance; // �𑜓x
		DWORD c_nFPS; //	�X�V����^�C�~���O
		DWORD c_llFrameCount; // �X�V�E�`�悵����
		//LONGLONG c_llCurrentTime; // ���݂̎���
		LONGLONG c_llExecLastTime; // �X�V�E�`�悵����
		LONGLONG c_llFPSLastTime; // FPS�̐��l���擾�����Ō�̎���
		LONGLONG c_llSysFreq; // �V�X�e���̎��g��

		// �L�b�`���^�C�}�[
		int c_nMs; // �Z�b�g����鎞��(ms)
		int c_PerformanceTime; // ���ԉ𑜓x
		CHECKMETHOD c_cm; // ���Ԍo�߂̃`�F�b�N����
		LONGLONG c_llStartTime; // �J�n����
 		LONGLONG c_llLastTime; // �Ō�̎���
		LONGLONG c_llContinueTime; // �����̎���
		LONGLONG c_llStopTime; // �~�߂�����

};


/******************************************************************************
	�v���g�^�C�v�錾
******************************************************************************/
double CreateRandomNumber( int nRange_Min , int nRange_Max , int seed );


/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#endif


/******************************************************************************
**	�^�C�g��  : ���𑜓x�^�C�}�[FPS QueryPerformanceCounter
**	�t�@�C����: QPCounter.cpp
**	�쐬��    : AT-12A-244 �o�Ȕԍ� 16 �ؑ� �ˋM
**	�쐬��    : 2015/7/20
******************************************************************************/

/******************************************************************************
**	���e
**
**	���Ԃ�J�E���g�Ɋւ�����̂��X�ɍׂ����l������֐�
**	timeGetTime()�����ׂ������l����邱�Ƃ��ł��鍂�𑜓x�^�C�}�[
**	�����APC��n�[�h�ɂ���Ă͑Ή����Ă��Ȃ��̂Œ���
**	FPS�Ȃǂ̒l����萸���ɑ���邱�Ƃ��ł���
**	�܂��A���Q�[��G�t�F�N�g�̃^�C�~���O�ȂǁA�Y���Ă͂Ȃ�Ȃ����̂ɑ΂���
**	���ɗL��
**
******************************************************************************/

/******************************************************************************
**	�X�V���e
**
******************************************************************************/


/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "QPCounter.h"
//#include "debugProc.h"


/******************************************************************************
**	�}�N����`
******************************************************************************/

/**** �}�W�b�N�i���o�[ ****/

/*** FPS�֘A ***/

/* ���𑜓x��FALSE���Ɏg�p������g���̒l */
#define FALSE_FREQ ( 1000 )

/* FPS�Z�o�Ԋu���� */
#define FPS_COUNT ( 500 )

/* FPS�\�������� */
#define STR_FPS ( 10 )

/* �\�������J���[ */
#define TEXTCOLOR_FPS_R ( 255 )
#define TEXTCOLOR_FPS_G ( 255 )
#define TEXTCOLOR_FPS_B ( 0 )
#define TEXTCOLOR_FPS_A ( 60 )

/* �\���ʒu */
#define POS_FPS_X ( 0 )
#define POS_FPS_Y ( 0 )

/* ���ԉ𑜓x */
#define PERFORMANCETIME_MS ( 60 )


/******************************************************************************
**	�v���g�^�C�v�錾
******************************************************************************/


/******************************************************************************
**	�O���[�o���ϐ�
******************************************************************************/


/******************************************************************************
**	�֐���: cQPCounter::cQPCounter
**		�֐��̊T�v
**	����  : void
**	����  : cQPCounter�̃R���X�g���N�^
********************************************************************************/
QPCounter::QPCounter( void )
{
	/**** �ϐ��錾 ****/
	LARGE_INTEGER ltQPFreq; // ���𑜓x���g���l


	/**** ���𑜓x���g�p�\���̗L�� ****/
	// �Ή����Ă��鎞�͍��𑜓x���[�h���I��
	// �X��PC�̃V�X�e�����g����ۑ�
	if( QueryPerformanceFrequency( &ltQPFreq ) ) // �V�X�e���̎��g�����擾
	{
		c_bPerformance = true;
		c_llSysFreq = ltQPFreq.QuadPart;


	}
	// �g���˂��`���̓I�t
	// ������timeGetTime()�ő�p����(���g����FALSE_FREQ�Ɉˑ�����)
	else
	{
		c_bPerformance = false;
		c_llSysFreq = ( LONGLONG )FALSE_FREQ;

		/* ����\ */
		timeBeginPeriod( 1 );

	}

	/* ���𑜓x�J�E���^�[�̃N���X�������� */
	if( FAILED( QPCounter::Init() ) )
	{
		// ���s������AtimeGetTime()�Ŏ擾
		c_bPerformance = false;
		Init();

	}


	/**** �L�b�`���^�C�}�[�̏����� ****/
	c_bRanTimmer = false; // �^�C�}�[��~���
	c_nMs = 0;
	c_cm = CHECKMETHOD_MAX;
	c_llStartTime = c_llStopTime = c_llContinueTime = c_llLastTime = 0;

}


/******************************************************************************
**	�֐���: cQPCounter::~cQPCounter
**		�֐��̊T�v
**	����  : void
**	����  : cQPCounter�̃f�X�g���N�^
********************************************************************************/
QPCounter::~QPCounter( void )
{
	/* ����\��߂� */
	if( !c_bPerformance )
	{
		timeEndPeriod( 1 );

	}

}


/******************************************************************************
**	�֐���: InitQPCounter
**		�֐��̊T�v
**	����  : void
**	�߂�l: HRESULT
**	����  : ������
******************************************************************************/
HRESULT QPCounter::Init( void )
{
	// �^�C�}�[���Z�b�g����
	if( c_bPerformance )
	{
		/**** �ϐ��錾 ****/
		LARGE_INTEGER ltQPCnter; // ���𑜓x�^�C�}�[


		// ���𑜓x���g�p��
		if( !QueryPerformanceCounter( &ltQPCnter ) ) // ���Ԃ̎擾
		{
			return E_FAIL;

		}

		// �^�C�}�[�̃Z�b�g
		c_llFPSLastTime = c_llExecLastTime = ltQPCnter.QuadPart;

	}
	else
	{
		// ���𑜓x���g�p�s��
		c_llFPSLastTime = c_llExecLastTime = ( LONGLONG )timeGetTime();

	}

	/* ���̑��AFPS�J�E���^�[�AFPS�l�̏����� */
	c_llFrameCount = 0;
	c_nCntFPS = 0;
	SetFPS( FPS ); // �f�t�H���g��60�������������ő������Ă���

	return S_OK;

}


/******************************************************************************
**	�֐���: SetFPS
**		�֐��̊T�v
**	����  : FPS�l int _nFPS
**	�߂�l: void
**	����  : FPS�l���Z�b�g
******************************************************************************/
void QPCounter::SetFPS( int _nFPS )
{
	c_nFPS = _nFPS;

}


/******************************************************************************
**	�֐���: SetPerformance
**	�֐��̊T�v
**	����  : �𑜓x nPerformance
**	�߂�l: void
**	����  : �𑜓x�̐ݒ�
******************************************************************************/
void QPCounter::SetPerfoemance( int nPeformance )
{
	c_nPerformance = c_nPerformance;

}


/******************************************************************************
**	�֐���: CountFPS
**		�֐��̊T�v
**	����  : void
**	�߂�l: bool
**	����  : FPS�J�E���g
******************************************************************************/
void QPCounter::CountFPS( void )
{
	/**** �ϐ��錾 ****/
	LONGLONG llCurrentTime; // ���Ԃ��擾


	/* ���𑜓x�^�C�}�[���g�p�\�L�� */
	if( c_bPerformance )
	{
		// ���𑜓x���[�h

		// ���Ԃ̎擾
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// ��𑜓x���[�h

		// ���Ԃ̎擾( timeGetTime() )
		llCurrentTime = ( LONGLONG )timeGetTime();

	}

	// FPS�Z�o
	if( ( ( llCurrentTime - c_llFPSLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) >= FPS_COUNT )
	{
		c_nCntFPS = ( ( c_llFrameCount * PERFOEMANCE_FPS ) / ( ( llCurrentTime - c_llFPSLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) );

		/* ���݂̎��Ԃ��Ō�̎��ԂƂ��đ���A�t���[���J�E���g���N���A */
		c_llFPSLastTime = llCurrentTime;
		c_llFrameCount = 0;

	}

}


/******************************************************************************
**	�֐���: cQPCounter::CallFPS
**		�֐��̊T�v
**	����  : void
**	�߂�l: bool
**	����  : FPS����
******************************************************************************/
bool QPCounter::CallFPS( void )
{
	/**** �ϐ��錾 ****/
	LONGLONG llCurrentTime; // ���Ԃ��擾


	/* ���𑜓x�^�C�}�[���g�p�\�L�� */
	if( c_bPerformance )
	{
		// ���𑜓x���[�h

		// ���Ԃ̎擾
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// ��𑜓x���[�h

		// ���Ԃ̎擾( timeGetTime() )
		llCurrentTime = ( LONGLONG ) timeGetTime();

	}


	/**** FPS���� ****/

	// FPS���̏���( �f�t�H���g��1/60�񖈂ɍX�V )
	if( ( ( llCurrentTime - c_llExecLastTime ) * PERFOEMANCE_FPS / c_llSysFreq ) >= ( 1000 / c_nFPS ) )
	{
		// �X�V�ł���^�C�~���O��true��Ԃ�
		return true;

	}
	else
	{
		// �X�V�ł��Ȃ��^�C�~���O��false��Ԃ�
		return false;

	}

}


/******************************************************************************
**	�֐���: EndFPS
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �Ō�̏���
******************************************************************************/
void QPCounter::EndFPS( void )
{
	/**** �ϐ��錾 ****/
	LONGLONG llCurrentTime; // ���Ԃ��擾


	/* ���𑜓x�^�C�}�[���g�p�\�L�� */
	if ( c_bPerformance )
	{
		// ���𑜓x���[�h

		// ���Ԃ̎擾
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		llCurrentTime = ltQPCnter.QuadPart;

	}
	else
	{
		// ��𑜓x���[�h

		// ���Ԃ̎擾( timeGetTime() )
		llCurrentTime = ( LONGLONG )timeGetTime();

	}

	// ���݂̎��Ԃ��Ō�̎��ԂƂ��đ���A�X�V���ƂɃt���[���J�E���g���v���X
	c_llExecLastTime = llCurrentTime;
	c_llFrameCount++;

}


/******************************************************************************
**	�֐���: DrawFPS
**		�֐��̊T�v
**	����  : �t�H���g�f�o�C�X pFont
**	�߂�l: void
**	����  : FPS�l��\��
******************************************************************************/
void QPCounter::DrawFPS()
{
	//PrintDebugProc( "FPS:%d\n", c_nCntFPS );

}


/******************************************************************************
**	�֐���: SetTimmerMs
**	�֐��̊T�v
**	����  : �Z�b�g���鎞�� int ms , �`�F�b�N���� CHECKMETHOD cm
**	�߂�l: ���� bool
**	����  : �`�F�b�N���鎞�Ԃ��`�F�b�N�����ɂ��������ă`�F�b�N���Ă���
******************************************************************************/
bool QPCounter::SetTimmerMs( int ms , CHECKMETHOD cm )
{
	c_nMs = ms;
	c_cm = cm;
	c_PerformanceTime = PERFORMANCETIME_MS;
	c_bRanTimmer = false;

	return true;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l: ���� bool
**	����  :
******************************************************************************/
bool QPCounter::StartTimmer( void )
{
	// ���𑜓x�^�C�}�[�ɑΉ����Ă��邩
	if( c_bPerformance )
	{
		// ���𑜓x���[�h

		// ���Ԃ̎擾
		LARGE_INTEGER ltQPCnter;
		QueryPerformanceCounter( &ltQPCnter );
		c_llStartTime = ltQPCnter.QuadPart;

	}
	else
	{
		// ��𑜓x���[�h

		// ���Ԃ̎擾( timeGetTime() )
		c_llStartTime = ( LONGLONG )timeGetTime();

	}

	// �^�C�}�[�N����ON
	c_bRanTimmer = true;

	return true;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l: ���� bool
**	����  :
******************************************************************************/
bool QPCounter::CheckTimmer( void )
{
	// �^�C�}�[��ON�ɂȂĂ����珈��������
	if( c_bRanTimmer == true )
	{
		/* �ϐ��錾 */
		LONGLONG llCurrentTime; // ���Ԃ��擾

		// ���𑜓x�^�C�}�[�ɑΉ����Ă��邩
		if( c_bPerformance )
		{
			// ���𑜓x���[�h

			// ���Ԃ̎擾
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// ��𑜓x���[�h

			// ���Ԃ̎擾( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// ���Ԍo�߂̊m�F
		/****************************************
		 * 
		 * (���݂̎��� - �ĊJ��������) + (��~�������� - �J�n��������)
		 * ������~���Ȃ������ꍇ�ł��J�n�������Ԃ��}�C�i�X�l�ɂȂ�
		 * 
		 ***************************************/
		if( ( ( ( llCurrentTime - c_llContinueTime ) + ( c_llStopTime - c_llStartTime ) ) * c_PerformanceTime / c_llSysFreq ) >= c_nMs )
		{
			// �J��Ԃ��w��
			switch( c_cm )
			{
				case CHECKMETHOD_ONLY_ONCE: // 1��݂̂̓^�C�}�[��OFF�ɂ���
					c_bRanTimmer = false;

					break;

				case CHECKMETHOD_REPETITION: // �J��Ԃ��͎擾�������Ԃ�StartTime�Ƀ��Z�b�g����
					c_llStartTime = llCurrentTime;
					c_llContinueTime = c_llStopTime = 0;

					break;

				case CHECKMETHOD_REGINTVL: // ���Ԋu�́E�E�E
					/***** �o�[�W�����A�b�v�ɂĎ��� **/
					break;

				default: // �G���[����̂��߁A������false�ɂ���
					c_bRanTimmer = false;

					break;

			}

			// �w�肳�ꂽ���Ԃ�������true��Ԃ�
			return true;

		}
		else
		{
			// �w�肳�ꂽ���ԊO��������false��Ԃ�
			return false;

		}
		
	}
	else
	{
		// OFF(false)�������ꍇ��false��Ԃ�
		return false;

	}

	return false;

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l: ���� bool
**	����  :
******************************************************************************/
bool QPCounter::StopTimmer( void )
{
	/* �ŏ��Ɏ��Ԃ��󂯎��^�C�}�[���~�߂� */
	// �^�C�}�[��ON�������珈��������
	if( c_bRanTimmer )
	{
		/* �ϐ��錾 */
		LONGLONG llCurrentTime; // ���Ԃ��擾

		// ���𑜓x�^�C�}�[�ɑΉ����Ă��邩
		if( c_bPerformance )
		{
			// ���𑜓x���[�h

			// ���Ԃ̎擾
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// ��𑜓x���[�h

			// ���Ԃ̎擾( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// ���Ԃ̎󂯓n���A�^�C�}�[�̒�~
		c_llStopTime = llCurrentTime;
		c_bRanTimmer = false;

		return true;

	}
	else
	{
		// ����OFF�������ꍇ��false��Ԃ�
		return false;

	}

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l: ���� bool
**	����  :
******************************************************************************/
bool QPCounter::RestartTimmer( void )
{
	/* �ŏ��Ƀ^�C�}�[��ON�ɂ��Ă��玞�Ԃ��󂯎�� */
	// �^�C�}�[��OFF�������珈��������
	if( c_bRanTimmer == false )
	{
		/* �ϐ��錾 */
		LONGLONG llCurrentTime; // ���Ԃ��擾

		// ���𑜓x�^�C�}�[�ɑΉ����Ă��邩
		if( c_bPerformance )
		{
			// ���𑜓x���[�h

			// ���Ԃ̎擾
			LARGE_INTEGER ltQPCnter;
			QueryPerformanceCounter( &ltQPCnter );
			llCurrentTime = ltQPCnter.QuadPart;

		}
		else
		{
			// ��𑜓x���[�h

			// ���Ԃ̎擾( timeGetTime() )
			llCurrentTime = ( LONGLONG )timeGetTime();

		}

		// ���Ԃ̎󂯓n���A�^�C�}�[�̍Đ�
		c_llContinueTime = llCurrentTime;
		c_bRanTimmer = true;

		return true;

	}
	else
	{
		// ����OFF�������ꍇ��false��Ԃ�
		return false;

	}

}


/******************************************************************************
**	�֐���:
**	�֐��̊T�v
**	����  :
**	�߂�l: ���� bool
**	����  :
******************************************************************************/
bool QPCounter::ResetTimmer( void )
{
	c_bRanTimmer = false;
	c_nMs = 0;
	c_cm = CHECKMETHOD_MAX;
	c_llStartTime = c_llStopTime = c_llContinueTime = c_llLastTime = 0;

	return true;

}


/******************************************************************************
**	�֐���: CreateRandomNumber
**	�֐��̊T�v
**	����  : ���l�͈̔� int Min , int Max , �����̎� seed(�f�t�H���g��1�����)
**	�߂�l: ���� double�^
**	����  : �����쐬
******************************************************************************/
double CreateRandomNumber( int nRange_Min , int nRange_Max , int seed )
{
	/**** �ϐ��錾 ****/
	LARGE_INTEGER QPFreq; // ���g��
	LARGE_INTEGER QPCntr; // ���݂̎���
	static long seed2; // ���������p


	/* ���𑜓x�^�C�}�[���g�p�\�L�� */
	if( QueryPerformanceFrequency( &QPFreq ) )
	{
		// ���𑜓x���[�h

		// ���Ԃ̎擾
		QueryPerformanceCounter( &QPCntr );

	}
	else
	{
		// ��𑜓x���[�h

		// ���Ԃ̎擾( timeGetTime() )
		QPCntr.QuadPart = ( LONGLONG )timeGetTime();

	}

	// �����쐬
	seed2 = rand();
	srand( seed * seed2 );
	double RandNum = ( int )( QPCntr.QuadPart / QPFreq.QuadPart * rand() ) % nRange_Max;

	// �͈̓`�F�b�N 
	/********************************************
	 * 
	 * �͈͈ȉ��̎��͈ȉ��̌v�Z������
	 * �͈͍ŏ��l�Ɛ������ꂽ����(�ȉ�����)�̍����𗐐��ɑ���
	 * �͈͂̍����l��rand()�Ő������ꂽ�����̗]��𑫂� = �͈͓��ŗ��������������
	 * 
	********************************************/
	if( RandNum < nRange_Min )
	{
		RandNum += nRange_Min - RandNum + ( rand() % ( nRange_Max - nRange_Min ) );

	}

	return RandNum;

}


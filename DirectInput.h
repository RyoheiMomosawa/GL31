#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: DirectInput.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/10
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�X�V���e
**
**
**
******************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Input.h"

/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/


/******************************************************************************
**	�N���X��`
******************************************************************************/
namespace input
{
	class DirectInput
	{
	public:
		DirectInput();
		virtual ~DirectInput();

		// �������A�I���A�X�V����
		virtual HRESULT Init( HWND ) = 0;
		virtual int Uninit() = 0;
		virtual HRESULT Update() = 0;

		// �擾���@
		virtual bool GetPress( int ); // ������
		virtual bool GetTrigger( int ); // �g���K�[
		virtual bool GetRelease( int ); // �����[�X
		virtual bool GetRepeat( int ); // ���s�[�g

		// ���s�[�g�̑��x�ύX
		virtual void SetRepeatSpeed( unsigned int );

		// ���X�g�\��
		static DWORD m_dwCreateCnt; // ������
		static DirectInput *m_Top; // �擪�A�h���X
		static DirectInput *m_Last; // ����A�h���X
		DirectInput *m_Prev; // �O�|�C���^
		DirectInput *m_Next; // ���|�C���^


	protected:
		// ���̓f�o�C�X�ւ̃|�C���^
		LPDIRECTINPUTDEVICE8 lpdid;

		// ���̓��[�N
		BYTE *m_State;
		BYTE *m_StateTrigger;
		BYTE *m_StateRelese;
		BYTE *m_StateRepeat;
		unsigned int *m_StateRepeatCount;
		unsigned int m_RepeatSpeed;

	};

}


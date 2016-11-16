/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Dialog.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/7/15
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Dialog.h"


/******************************************************************************
**	�O���[�o���ϐ�
******************************************************************************/


/******************************************************************************
** 	�֐���: CALLBACK PosDlgProc
** 	�֐��̊T�v
** 	����  : �_�C�A���O�̃f�[�^�A���b�Z�[�W�A�p�����[�^2��
** 	�߂�l: bool
** 	����  : �_�C�A���O�̊e���菈��
******************************************************************************/
BOOL CALLBACK PosDlgProc( HWND Dialog, UINT Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
	{
		case WM_INITDIALOG:

			return TRUE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( Dialog, 0 );

					break;

				default:

					break;

			}

			return TRUE;

		default:

			break;

	}

	return FALSE;

}


/******************************************************************************
** 	�֐���: CALLBACK AboutDlgProc
** 	�֐��̊T�v
** 	����  : �_�C�A���O�̃f�[�^�A���b�Z�[�W�A�p�����[�^2��
** 	�߂�l: bool
** 	����  : �_�C�A���O�̊e���菈��
******************************************************************************/
BOOL CALLBACK CameraDlgProc( HWND Dialog, UINT Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
	{
		case WM_INITDIALOG:

			return TRUE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( Dialog, 0 );

					break;

				default:

					break;

			}

			return TRUE;

		default:

			break;

	}

	return FALSE;

}


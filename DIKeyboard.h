#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: DIKeyboard.h
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
#include "DirectInput.h"


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
	class DIKeyboard : public DirectInput
	{
		public:
		DIKeyboard();
		virtual ~DIKeyboard();

		HRESULT Init( HWND hWnd );
		int Uninit();
		HRESULT Update();

	};

}

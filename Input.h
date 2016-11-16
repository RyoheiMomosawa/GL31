#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Input.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/5/9
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
#include <windows.h>
#include <string.h>

// DirectX
#include "d3dx9.h"
#define DIRECTINPUT_VERSION ( 0x0800 ) // �G���[�I�Ȃ��̂̉��
#include "dinput.h" // ���͂ɕK�v
#include "xaudio2.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/

/* �`�揈���ɕK�v */
#pragma comment ( lib , "d3d9.lib" )

/* DirectX9�̊g�����C�u���� */
#pragma comment ( lib , "d3dx9.lib" )

/* DirectX�R���|�[�l���g�ɕK�v */
#pragma comment ( lib , "dxguid.lib" )

/* ���̍Đ��ɕK�v�ȃR���|�[�l���g(FPS�Ȃǂɂ��g�p) */
#pragma comment ( lib , "winmm.lib" )

/* �{�^���A�L�[�{�[�h�̓��� */
#pragma comment ( lib , "dinput8.lib" )


/******************************************************************************
**	�}�N����`
******************************************************************************/

/**** �}�W�b�N�i���o�[ ****/

/* ���s�[�g�J�n���� */
#define REPEAT_TIME ( 30 )

/* �}�E�X����ݒ� */
//#define COOPERRATIONLEBEL_MOUSE ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) // �A�N�Z�X���� �t�H�A�O���E���h�̃X�N���[�����͂������Ȃ�
#define COOPERRATIONLEBEL_MOUSE ( DISCL_EXCLUSIVE | DISCL_BACKGROUND ) // �A�N�Z�X���� �t�H�A�O���E���h�̃X�N���[�����͂������Ȃ�

/* �R���g���[������ݒ� */
#define COOPERRATIONLEBEL_JOYPAD ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) // �A�N�Z�X���� �t�H�A�O���E���h�̃X�N���[�����͂������Ȃ�


// Z���͈�
#define PROPRANGE_MIN ( -1000 )
#define PROPRANGE_MAM ( 1000 )

/* �\���L�[�e���� */
#define POVSTATE_UP ( 0 )
#define POVSTATE_UPRIGHT ( 4500 )
#define POVSTATE_RIGHT ( 9000 )
#define POVSTATE_DOWNRIGHT ( 13500 )
#define POVSTATE_DOWN ( 18000 )
#define POVSTATE_DOWNLEFT ( 22500 )
#define POVSTATE_LEFT ( 27000 )
#define POVSTATE_UPLEFT ( 31500 )

/* �}�E�X���� */
enum MOUSEBUTTON
{
	MOUSEBUTTON_LEFT = 0,
	MOUSEBUTTON_RIGHT,
	MOUSEBUTTON_CENTER,
	MOUSEBUTTON_3,
#ifdef _SET_DIMOUSESTATE2_
	MOUSEBUTTON_4,
	MOUSEBUTTON_5,
	MOUSEBUTTON_6,
	MOUSEBUTTON_7,

#endif // _SET_DIMOUSESTATE2_

	MOUSEBUTTON_MAX

};

/* �}�E�X�X�e�[�g */
#ifdef _SET_DIMOUSESTATE2_
typedef DIMOUSESTATE2 MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 8 )

#elif _SET_DIMOUSESTATE_
typedef DIMOUSESTATE MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 4 )

#else
typedef DIMOUSESTATE MOUSE_STATE;
#define MOUSE_USE_BOTTON_MAX ( 4 )

#endif // SET MOUSESTATE

/* �W���C�p�b�h�X�e�[�g */
#ifdef _SET_DIJOYSTATE2_
typedef DIJOYSTATE2 JOYPAD_STATE;

#elif _SET_DIJOYSTATE_
typedef DIJOYSTATE JOYPAD_STATE;

#else
typedef DIJOYSTATE JOYPAD_STATE;

#endif // SET JOYSTATE


/******************************************************************************
**	���O��Ԓ�`
******************************************************************************/
namespace input
{
	class Input
	{
		public:
		Input();
		~Input();

		// DirectInput�I�u�W�F�N�g�̏������A�폜����
		static HRESULT Init( HINSTANCE hInstance, HWND hWnd );
		static int Release();

		// DirectInput�I�u�W�F�N�g
		static LPDIRECTINPUT8 lpDirectInput;

		protected:

	};

}

/******************************************************************************
	�^�C�g��  : 
	�t�@�C����: 
	�쐬��    : AT-12A-244 �o�Ȕԍ� 16 �ؑ� �ˋM
	�쐬��    : //
******************************************************************************/

/******************************************************************************
	�X�V���e

******************************************************************************/

/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_


/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include < windows.h >
#include <string.h>
#include <time.h>



/******************************************************************************
	���C�u���������N
******************************************************************************/

/* ���̍Đ��ɕK�v�ȃR���|�[�l���g(FPS�Ȃǂɂ��g�p) */
#pragma comment ( lib , "winmm.lib" )


/******************************************************************************
	�}�N����`
******************************************************************************/

/**** �}�W�b�N�i���o�[ ****/

/* �E�B���h�E�̑傫�� */
#define SCREEN_WIDTH ( 1280 )
#define SCREEN_HEIGHT ( 720 )

/* �E�B���h�E�N���X�� */
#define WNDCLS_NAME ( "OpenGL temp" )
#define WNDMAINCLS_NAME ( "OpenGL temp" )

/* �E�B���h�E�̖��O */
#define WND_NAME ( "Motion Viewer for ObjectFile" )
#define WNDMAIN_NAME ( "Motion Viewer for ObjectFile" )


/**** �\���̐錾 ****/


/******************************************************************************
	�v���g�^�C�v�錾
******************************************************************************/
HINSTANCE GetInstance( void );
HWND GetHWND( void );


/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#endif
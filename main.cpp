/******************************************************************************
** 	�^�C�g��  :
** 	�t�@�C����:
** 	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
** 	�쐬��    : //
******************************************************************************/

/******************************************************************************
**	�X�V���e
**
**
**
******************************************************************************/


/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "wndproc.h"
#include "Manager.h"
#include "resource.h"

#include <time.h>
#include <tchar.h>
#include <stdio.h>
#include <crtdbg.h>
/******************************************************************************
**	�}�N����`
******************************************************************************/

/**** �w�i�F ****/
#define BGCOLOR_R ( 0 )
#define BGCOLOR_G ( 0 )
#define BGCOLOR_B ( 0 )
#define BGCOLOR_A ( 100 )


/**** FPS�֘A ****/

/* FPS�l */
#define FPS ( 60 )

/* FPS�\�������� */
#define STR_FPS ( 256 )

/* �\�������J���[ */
#define TEXTCOLOR_FPS_R ( 255 )
#define TEXTCOLOR_FPS_G ( 255 )
#define TEXTCOLOR_FPS_B ( 255 )
#define TEXTCOLOR_FPS_A ( 255 )

/* �\���ʒu */
#define POS_FPS_X ( 0 )
#define POS_FPS_Y ( 0 )


/******************************************************************************
**	�v���g�^�C�v�錾
******************************************************************************/

/* �������A�I������ */
HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
int Uninit();

/* �X�V�A�`�揈�� */
void Update( void );
void Draw( void );

/* FPS�\�� */
void DrawFPS( void );



/******************************************************************************
**	�O���[�o���ϐ�
******************************************************************************/

/* FPS�J�E���^ */
int g_nCountFPS;

/* �C���X�^���X */
HINSTANCE g_hInstance;

/* �E�B���h�E */
HWND g_hWnd;

/* RendererGL */
Manager *g_pManager;


/******************************************************************************
** 	�֐���: WinMain
** 		�֐��̊T�v
** 	����  :
** 	�߂�l:
** 	����  :
******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPerInstance, LPSTR lpCmdLine, int nCmdShow )
{
	/**** ���������[�N���o ****/
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 85 );

	/**** �C���X�^���X���R�s�[ ****/
	g_hInstance = hInstance;


	/**** �ϐ��錾 ****/

	/* �E�B���h�E���� */
	// �e�E�B���h�E
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ), // �������T�C�Y�̎w��
		CS_CLASSDC, // �E�B���h�E�̃X�^�C�����w��
		WndProc, // �E�B���h�E�v���V�[�V���̃A�h���X(�֐���)���w��
		0, // �g�p���Ȃ�
		0, // �g�p���Ȃ�
		hInstance, // �C���X�^���X�̃n���h����ݒ�
		NULL, // �g�p����A�C�R�����w��
		LoadCursor( NULL , IDC_ARROW ), // �}�E�X�J�[�\�����w��
		( HBRUSH )( COLOR_WINDOW + 1 ), // �N���C�A���g�̈�̔w�i�F��ݒ�
		MAKEINTRESOURCE( IDR_MENU1 ) , // ���j���[��ǉ����������ɐݒ�
		WNDCLS_NAME, // �E�B���h�E�N���X�̖��O��ݒ�
		NULL, // �������A�C�R���̏���ݒ�

	};

	/* �E�B���h�E�n���h�� */
	HWND hWnd;

	/* ���b�Z�[�W */
	MSG msg;

	/* �E�B���h�E�̕�(�N���C�A���g�̈�) */
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };


	/* FPS�ɕK�v�ȕϐ� */
	DWORD dwFrameCount; // �X�V�E�`�悵����
	DWORD dwCurrentTime; // ���݂̎���
	DWORD dwExecLastTime; // �X�V�E�`�揈���������Ō�̎���
	DWORD dwFPSLastTime; // FPS�̐��l���擾�����Ō�̎���


	/**** �E�B���h�E���� ****/

	// �e�E�B���h�E�̐���
	// �N���C�A���g�̈�̊m��
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false ); // false�̕����́A���j���[������ꍇ�ɂ�true�ɂ���

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx( &wcex );
	hWnd = CreateWindowEx( 0,
		WNDCLS_NAME, // �E�B���h�E �N���X�̖��O
		WND_NAME, // �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, // �E�B���h�E�̎��
		CW_USEDEFAULT, // �E�B���h�E�\���ʒu X���W
		CW_USEDEFAULT, //         �V         Y
		rect.right - rect.left, // ��
		rect.bottom - rect.top, // ����
		NULL, // �e�E�B���h�E�̃n���h��
		NULL, // ���j���[�n���h�� �܂��� �q�E�B���h�EID
		hInstance,
		NULL ); // �E�B���h�E�쐬�f�[�^


	/**** DirectX���������� ****/
	if( FAILED( Init( hInstance, hWnd, TRUE ) ) )
	{
		return -1;

	}


	/**** �E�B���h�E�̕\�� ****/
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );


	/**** FPS�J�n�ʒu ****/

	/* ����\ */
	timeBeginPeriod( 1 );

	/* FPS�ϐ��̏�����*/
	dwFrameCount =
		dwCurrentTime = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();


	/**** �Q�[������ ****/
	while( 1 )
	{
		/*** �Q�[���I������ ***/
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			/* ���b�Z�[�W���I���Ȃ�v���O�����I�� */
			if( msg.message == WM_QUIT )
			{
				break;

			}
			else
			{
				/* ���b�Z�[�W�̖|��Ƒ��o */
				TranslateMessage( &msg );
				DispatchMessage( &msg );

			}

		}
		/* DirectX(�Q�[��)���� */
		else
		{
			/*** FPS���� ***/
			dwCurrentTime = timeGetTime(); // ���݂̎��Ԃ��擾

										   /* FPS�Z�o **** 500ms����FPS�̒l���X�V */
			if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;

			}

			/* 1/60���̍X�V�E�`�揈�� */
			if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / FPS ) )
			{
				/* �X�V�E�`�揈�����������Ԃ��Ō�̎��ԂƂ��ĕۊ� */
				dwExecLastTime = dwCurrentTime;

				/* �X�V�E�`�揈�� */
				Update();
				Draw();

				/* ���񐔓��ɍX�V�E�`�揈�������񐔂��J�E���g */
				dwFrameCount++;

			}

		}

	}


	/**** �E�B���h�E�폜 ****/
	UnregisterClass( WNDCLS_NAME, wcex.hInstance ); // ( �E�B���h�E�N���X�� )


	/**** �I������ ****/
	Uninit();


	/**** ����\ ****/
	timeEndPeriod( 1 );

	return ( int )msg.wParam;

}


/******************************************************************************
** 	�֐���: ���������� Init
** 		�֐��̊T�v
** 	����  : �n���h���C���X�^���X�A�n���h���E�B���h�E�As������ʂ̑傫��(bool)
** 	�߂�l: HRESULT
** 	����  : ����������
******************************************************************************/
HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	/* �����_���̐��� */
	g_pManager = new Manager;

	// �����_���̏�����
	g_pManager->Init( hInstance, hWnd, bWindow );

	return S_OK;

}


/******************************************************************************
** 	�֐���: �I������ Uninit
** 		�֐��̊T�v
** 	����  : void
** 	�߂�l: void
** 	����  :
******************************************************************************/
int Uninit()
{
	// �����_���̍폜
	g_pManager->Uninit();
	delete g_pManager;
	g_pManager = nullptr;


	/**** �I�������������A0��Ԃ� ****/
	return 0;

}


/******************************************************************************
** 	�֐���: �X�V���� Update
** 		�֐��̊T�v
** 	����  : void
** 	�߂�l: void
** 	����  :
******************************************************************************/
void Update( void )
{
	// �����_��
	g_pManager->Update();

}


/******************************************************************************
** 	�֐���: �`�揈�� Draw
** 		�֐��̊T�v
** 	����  : void
** 	�߂�l: void
** 	����  :
******************************************************************************/
void Draw( void )
{
	// �����_��
	g_pManager->Draw();

}


/******************************************************************************
** �֐���: �C���X�^���X�̏����擾 GetInstance
** �֐��̊T�v
** ����  : void
** �߂�l: �f�o�C�X�|�C���^ LPDIRECT3DDEVICE9
** ����  :
******************************************************************************/
HINSTANCE GetInstance( void )
{
	return g_hInstance;

}


/******************************************************************************
** 	�֐���: FPS�\�� void DrawFPS( void )
** 		�֐��̊T�v
** 	����  : void
** 	�߂�l: void
** 	����  :
******************************************************************************/
void DrawFPS( void )
{

}



/******************************************************************************
** �֐���: �E�B���h�E�̃n���h�����擾 GetHWND
** �֐��̊T�v
** ����  : void
** �߂�l: HWND
** ����  :
******************************************************************************/
HWND GetHWND( void )
{
	return g_hWnd;

}


/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: wndproc.cpp
**	�쐬��    : AT-12A-244 �o�Ȕԍ� 16 �ؑ� �ˋM
**	�쐬��    : 2015/5/10
**�@�C�����@�@: 2016/2/9
******************************************************************************/

/******************************************************************************
**	�X�V���e
**
******************************************************************************/


/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "wndproc.h"
#include "resource.h"
#include "Manager.h"
#include "RendererGL.h"
#include "Color.h"
#include "Dialog.h"


/******************************************************************************
**	�}�N����`
******************************************************************************/


/******************************************************************************
**	�v���g�^�C�v�錾
******************************************************************************/


/******************************************************************************
**	�O���[�o���ϐ�
******************************************************************************/

/* �|�W�V�����\���_�C�A���O */
HWND g_PosDialog;

/* �J�����\���_�C�A���O */
HWND g_CameraDialog;


/* �X�e�[�^�X�o�[ */
HWND g_hStatusBar;
BOOL g_bStatusBar = FALSE;


/******************************************************************************
** 	�֐���: LRESULT CALLBACK WndProc
** 		�֐��̊T�v
** 	����  : �e�n���h���A���b�Z�[�W�A
** 	�߂�l: �����Ɠ���
** 	����  : ���b�Z�[�W�̊e���菈��
******************************************************************************/
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	/**** �ϐ��錾 ****/
	int nID; // ���b�Z�[�W�{�b�N�X�߂�l
	static HWND hWndButton; // �{�^��
	static HWND hWndChild; // �q�E�B���h�E�̃|�C���^
	static RECT rectChild; // �q�E�B���h�E�̑傫��
	PAINTSTRUCT ps; // �N���C�A���g�̈��`�悷��ۂɕK�v
	HINSTANCE hInstance = GetInstance();

	/* �I�u�W�F�N�g�̈ړ��� */
	static int nPosX = 380;
	static int nPosY = 300;

	/* �N���C�A���g�̈� */
	const RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };

	/* �e�E�B���h�E�̑傫�����擾 */
	RECT PrntWndRect;


	/* �`�F�b�N�{�b�N�X */
	static DWORD dwCheckMenu = 0;

	/* �J���[�_�C�A���O */
	static CHOOSECOLOR cc;
	static COLORREF CustColors[ 16 ];


	/**** ���b�Z�[�W���菈�� ****/
	switch( uMsg )
	{
		case WM_DESTROY: // �~�{�^���������ꂽ��
			PostQuitMessage( 0 );

			break;

		case WM_PAINT: // �`��E�ĕ`�悷��

			break;

		case WM_KEYDOWN: // �L�[�����͂��ꂽ��
			switch( wParam )
			{
				case VK_ESCAPE: // �G�X�P�[�v
					/* �I���m�F�{�b�N�X */
					nID = MessageBox( hWnd, "�Q�[�����I�����܂����H", "�I���m�F", MB_YESNO + MB_ICONQUESTION );
					if( nID == IDYES )
					{
						DestroyWindow( hWnd );

					}

					break;

			}

			break;

		case WM_CREATE: // �E�B���h�E���������ꂽ��
		{
			// ���[�h���X�_�C�A���O����
			g_PosDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_DIALOG1 ), hWnd, PosDlgProc );
			g_CameraDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_DIALOG2 ), hWnd, CameraDlgProc );


			// �J���[�_�C�A���O����
			Color col = RendererGL::GetBgColor();
			COLORREF cr = RGB( ( int )( col.r * 255.0f ), ( int )( col.g * 255.0f ), ( int )( col.b * 255.0f ) );
			ZeroMemory( &cc, sizeof CHOOSECOLOR );
			cc.lStructSize = sizeof CHOOSECOLOR;
			cc.hwndOwner = hWnd;
			cc.rgbResult = cr;
			cc.lpCustColors = CustColors;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;


			// �X�e�[�^�X�o�[�̐���
			InitCommonControls();
			g_hStatusBar = CreateWindowEx(
				0, // �g���X�^�C��
				STATUSCLASSNAME, // �E�B���h�E�N���X
				NULL, // �^�C�g��
				WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM, // �E�B���h�E�ݒ�
				0, 0, 0, 0, // ���W�A�傫��
				hWnd, // �e�E�B���h�E
				( HMENU )ID_STATUSBAR, // �X�e�[�^�X�o�[ID
				hInstance, // �C���X�^���X�n���h��
				NULL );
			SetWindowPos( g_hStatusBar, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

		}


		break;

		case WM_MOVE:

			break;

		case WM_COMMAND: // ���������{�^���������ꂽ��
			switch( LOWORD( wParam ) )
			{
				// **********************************************************************************************************
				// **		�t�@�C��
				// **********************************************************************************************************
				case ID_CLOSE:
					DestroyWindow( hWnd );

					break;


				// **********************************************************************************************************
				// **		�\��
				// **********************************************************************************************************


			// ------------------------------------------------

				case ID_WIRERFRAME:
				{
					HMENU hMenu = GetMenu( hWnd );

					// �`�F�b�N�̗L��
					// �`�F�b�N�ς�
					if( GetMenuState( hMenu, ID_WIRERFRAME, MF_BYCOMMAND ) & ( MF_BYCOMMAND | MFS_CHECKED ) )
					{
						// �`�F�b�N���O���A���C���[�t���[��������
						dwCheckMenu = MF_BYCOMMAND | MFS_UNCHECKED;
						RendererGL::SetRenderMode( GLRS_FILLMODE, GLFILL_SOLID );

					}
					// �`�F�b�N����
					else
					{
						// �`�F�b�N��t���A���C���[�t���[���K�p
						dwCheckMenu = MF_BYCOMMAND | MFS_CHECKED;
						RendererGL::SetRenderMode( GLRS_FILLMODE, GLFILL_WIREFRAME );

					}

					// �`�F�b�N�̔��f
					CheckMenuItem( hMenu, ID_WIRERFRAME, dwCheckMenu );


					break;

				}


				case ID_STATUSBAR:
				{
					HMENU hMenu = GetMenu( hWnd );

					// �`�F�b�N�̗L��
					// �`�F�b�N�ς�
					if( GetMenuState( hMenu, ID_STATUSBAR, MF_BYCOMMAND ) & ( MF_BYCOMMAND | MFS_CHECKED ) )
					{
						// �`�F�b�N���O���A�X�e�[�^�X�o�[���\��
						dwCheckMenu = MF_BYCOMMAND | MFS_UNCHECKED;
						ShowWindow( g_hStatusBar, SW_HIDE );
						g_bStatusBar = FALSE;

					}
					// �`�F�b�N����
					else
					{
						// �`�F�b�N��t���A�X�e�[�^�X�o�[��\��
						dwCheckMenu = MF_BYCOMMAND | MFS_CHECKED;
						ShowWindow( g_hStatusBar, SW_SHOW );
						SendMessage( g_hStatusBar, SB_SIMPLE, TRUE, 0L );
						g_bStatusBar = TRUE;

					}

					// �`�F�b�N�̔��f
					CheckMenuItem( hMenu, ID_STATUSBAR, dwCheckMenu );

				}

					break;


				// **********************************************************************************************************
				// **		�ݒ�
				// **********************************************************************************************************

				case ID_BGCOLOR:
					if( ChooseColor( &cc ) )
					{
						RendererGL::SetBgColor( cc.rgbResult );

					}

					break;


				// **********************************************************************************************************
				// **		�w���v
				// **********************************************************************************************************

				case ID_HELP:

					break;


				case ID_VERSION:
					MessageBoxA( hWnd, "template ver 0.1", "�o�[�W�������", MB_OK );

					break;


				default:

					break;

			}

			break;

	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );

}


/******************************************************************************
** 	�֐���: GetPosDialog
** 	�֐��̊T�v
** 	����  : void
** 	�߂�l: HWND
** 	����  :
******************************************************************************/
HWND GetPosDialog()
{
	return g_PosDialog;

}


/******************************************************************************
** 	�֐���: GetCameraDialog
** 	�֐��̊T�v
** 	����  : void
** 	�߂�l: HWND
** 	����  :
******************************************************************************/
HWND GetCameraDialog()
{
	return g_CameraDialog;

}


/******************************************************************************
** 	�֐���: UpdateStatusBar
** 	�֐��̊T�v
** 	����  : void
** 	�߂�l: void
** 	����  :
******************************************************************************/
void UpdateStatusBar()
{
	if( g_bStatusBar )
	{
		SendMessage( g_hStatusBar, SB_SETTEXT, 255 | 0, ( LPARAM )"" );

	}

}


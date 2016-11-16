/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: WndProcDbgManager.cpp
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/6/28
**	�C����	�@: //
********************************************************************************/

/******************************************************************************
**	�C���N���[�h�t�@�C��
******************************************************************************/
#include "WndProcDbgManager.h"
#include <string.h>
#include <stdio.h>


/******************************************************************************
**	�ÓI�����o�ϐ�
******************************************************************************/
VALUEDEBUG *WndProcDbgManager::m_pValueDebug;
void *WndProcDbgManager::m_pTop, *WndProcDbgManager::m_pLast;
int WndProcDbgManager::m_CreateNum;
HWND WndProcDbgManager::m_hWnd;
HDC WndProcDbgManager::m_hdc;
int WndProcDbgManager::m_width, WndProcDbgManager::m_height;


/******************************************************************************
**	�֐���: WndProcDbgManager
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �R���X�g���N�^
******************************************************************************/
WndProcDbgManager::WndProcDbgManager()
{
	m_CreateNum = 0;
	m_width = 200;
	m_height = 30;

}


/******************************************************************************
**	�֐���: ~WndProcDbgManager
**		�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  : �f�X�g���N�^
******************************************************************************/
WndProcDbgManager::~WndProcDbgManager()
{
	m_pValueDebug = NULL;

}


/******************************************************************************
**	�֐���: SetDebugInfo
**	�֐��̊T�v
**	����  : const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize
**	�߂�l: int ID(�������̔ԍ��A0�`35565)
**	����  :
******************************************************************************/
int WndProcDbgManager::SetDebugInfo( const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize )
{
	int len = 0;
	HWND hWndEdit;
	VALUEDEBUG *p;
	p = new VALUEDEBUG;


	// �f�[�^�̑��
	len = strlen( pValueName );
	p->pValueName = new char[ len + 1 ];
	strncpy_s( p->pValueName, len + 1, pValueName, len );
	p->nValueNameLen = len;
	p->pValuePointer = ( INTEGRA_DECIMAL * )pValuePointer;
	p->nValueSize = nValueSize;
	p->typevalue = ValType;
	p->sign = sign;
	p->id = ( HMENU )( m_CreateNum + 1 );


	// �G�f�B�b�g�{�b�N�X�̐���
	hWndEdit = CreateWindow(
		TEXT( "EDIT" ), TEXT( "0" ),
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		0, m_height * ( m_CreateNum + 1 )  + m_height * m_CreateNum, m_width, m_height,
		hWnd,
		( HMENU )( m_CreateNum + 1 ),
		hInstance,
		NULL );
	p->hWndEditBox = hWndEdit;


	// ���X�g�\���|�C���^���
	if( m_CreateNum == 0 )
	{
		p->pPrev = NULL;
		p->pNext = NULL;
		m_pTop = p;
		m_pLast = NULL;

	}
	else
	{
		m_pValueDebug->pNext = p;
		m_pLast = p;
		p->pPrev = m_pValueDebug;
		p->pNext = NULL;

	}

	// ���������f�[�^�̃|�C���^���ڍs
	m_pValueDebug = p;
	p = NULL;


	// �����������Ԃ�Ԃ�(�J�n�ԍ� 0�`)
	m_CreateNum++;
	return m_CreateNum - 1;

}


/******************************************************************************
**	�֐���: Delete
**	�֐��̊T�v
**	����  : int id(0�`35565)
**	�߂�l: void
**	����  :
******************************************************************************/
bool WndProcDbgManager::Delete( int id )
{
	bool res = false;
	VALUEDEBUG *now = ( VALUEDEBUG * )m_pTop;
	VALUEDEBUG *next;
	int i = 0;

	while( now != NULL )
	{
		next = now->pNext;
		if( i == id )
		{
			// ���X�g�\������؂藣��
			if( now == m_pTop )
			{
				m_pTop = now->pNext;
				now->pNext->pPrev = NULL;

			}
			else if( now == m_pLast )
			{
				m_pLast = now->pPrev;
				now->pPrev->pNext = NULL;

			}
			else
			{
				now->pNext->pPrev = now->pPrev;
				now->pPrev->pNext = now->pNext;

			}

			// �폜
			delete[] now->pValueName;
			delete now;
			res = true;
			break;

		}

		// ���̃|�C���^�Ɉړ�
		now = next;
		i++;

	}


	return res;

}


/******************************************************************************
**	�֐���: DeleteAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void WndProcDbgManager::DeleteAll()
{
	VALUEDEBUG *now = ( VALUEDEBUG * )m_pTop;
	VALUEDEBUG *next;

	while( now != NULL )
	{
		next = now->pNext;
		delete[] now->pValueName;
		delete now;
		now = next;

	}

}


/******************************************************************************
**	�֐���: SetValueNameTextSize
**	�֐��̊T�v
**	����  : int width, int height
**	�߂�l: void
**	����  :
******************************************************************************/
void WndProcDbgManager::SetValueNameTextSize( int width, int height )
{
	m_width = width;
	m_height = height;

}


/******************************************************************************
**	�֐���: UpdateWindowTextAll
**	�֐��̊T�v
**	����  : HWND hWnd
**	�߂�l: void
**	����  :
******************************************************************************/
void WndProcDbgManager::UpdateWindowTextAll( HWND hWnd )
{
	HWND wnd = GetActiveWindow();
	if( wnd == hWnd )
	{
		return;

	}
	m_hWnd = hWnd;
	m_hdc = GetDC( hWnd );
	SendMessage( m_hWnd, WM_COMMAND, EN_UPDATE, 1 );
	//InvalidateRect( hWnd, NULL, TRUE );

}


/******************************************************************************
**	�֐���: DrawWindowTextAll
**	�֐��̊T�v
**	����  : void
**	�߂�l: void
**	����  :
******************************************************************************/
void WndProcDbgManager::DrawWindowTextAll()
{
	VALUEDEBUG *now = ( VALUEDEBUG * )m_pTop;
	VALUEDEBUG *next;
	int cnt = 0;
	INTEGRA_DECIMAL value;
	char ValueName[ 256 ];
	char text[ 256 ];

	while( now != NULL )
	{
		next = now->pNext;
		value = *now->pValuePointer;

		// �^�C�v
		switch( now->typevalue )
		{
			case TYPEVALUE_CHAR:
				strcpy_s( text, 256, value.c );

				break;


			case TYPEVALUE_SHORT:
				now->sign == TYPESIGN_SIGNED ?
					sprintf_s( text, 256, "%o", now->pValuePointer->s ) :
					sprintf_s( text, 256, "%o", now->pValuePointer->us );

				break;


			case TYPEVALUE_INT:
				now->sign == TYPESIGN_SIGNED ?
					sprintf_s( text, 256, "%d", now->pValuePointer->i ) :
					sprintf_s( text, 256, "%u", now->pValuePointer->ui );

				break;


			case TYPEVALUE_LONG:
				now->sign == TYPESIGN_SIGNED ?
					sprintf_s( text, 256, "%ld", now->pValuePointer->l ) :
					sprintf_s( text, 256, "%lu", now->pValuePointer->ul );

				break;


			case TYPEVALUE_LONGLONG:
				now->sign == TYPESIGN_SIGNED ?
					sprintf_s( text, 256, "%ld", now->pValuePointer->ll ) :
					sprintf_s( text, 256, "%lu", now->pValuePointer->ull );

				break;


			case TYPEVALUE_FLOAT:
				sprintf_s( text, 256, "%f", now->pValuePointer->f );

				break;


			case TYPEVALUE_DOUBLE:
				sprintf_s( text, 256, "%lf", now->pValuePointer->f );

				break;


			case TYPEVALUE_LONGDOUBLE:
				sprintf_s( text, 256, "%lf", now->pValuePointer->ld );

				break;


			default:

				break;


		}


		// �ϐ����̃R�s�[
		strcpy_s( ValueName, 256, now->pValueName );

		// �e�L�X�g�̕\��
		RECT r = { 0, m_height * cnt * 2, m_width, m_height + m_height * cnt * 2 };
		DrawText( m_hdc, now->pValueName, now->nValueNameLen, &r, DT_LEFT | DT_WORDBREAK );
		SetWindowText( now->hWndEditBox, text );

		// ���̃��X�g�ֈڍs
		cnt++;
		now = next;

	}

}


/******************************************************************************
**	�֐���: GetValueData
**	�֐��̊T�v
**	����  : HMENU id
**	�߂�l: void
**	����  : char�^(������)�͕s����A�񐄏�
******************************************************************************/
void WndProcDbgManager::GetValueData( HMENU id )
{
	VALUEDEBUG *now = ( VALUEDEBUG * )m_pTop;
	VALUEDEBUG *next;
	char text[ 256 ];

	while( now != NULL )
	{
		next = now->pNext;
		
		// id�̌���
		if( now->id == id )
		{
			GetWindowText( now->hWndEditBox, text, 256 );

			// �^�C�v
			switch( now->typevalue )
			{
				case TYPEVALUE_CHAR:
					strcpy_s( now->pValuePointer->c, now->nValueSize, text );

					break;


				case TYPEVALUE_SHORT:
					now->pValuePointer->s = atoi( text );

					break;


				case TYPEVALUE_INT:
					now->pValuePointer->i = atoi( text );

					break;


				case TYPEVALUE_LONG:
					now->pValuePointer->l = atol( text );

					break;


				case TYPEVALUE_LONGLONG:
					now->pValuePointer->ll = atoll( text );

					break;


				case TYPEVALUE_FLOAT:
					now->pValuePointer->f = ( float )atof( text );

					break;


				case TYPEVALUE_DOUBLE:
					now->pValuePointer->d = atof( text );

					break;


				case TYPEVALUE_LONGDOUBLE:
					now->pValuePointer->d = atof( text );

					break;


				default:

					break;


			}

			// ���[�v���甲����
			return;

		}

		// ���̃|�C���^��
		now = next;

	}

}

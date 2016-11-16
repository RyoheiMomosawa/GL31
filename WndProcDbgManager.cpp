/******************************************************************************
**	タイトル  :
**	ファイル名: WndProcDbgManager.cpp
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/28
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include "WndProcDbgManager.h"
#include <string.h>
#include <stdio.h>


/******************************************************************************
**	静的メンバ変数
******************************************************************************/
VALUEDEBUG *WndProcDbgManager::m_pValueDebug;
void *WndProcDbgManager::m_pTop, *WndProcDbgManager::m_pLast;
int WndProcDbgManager::m_CreateNum;
HWND WndProcDbgManager::m_hWnd;
HDC WndProcDbgManager::m_hdc;
int WndProcDbgManager::m_width, WndProcDbgManager::m_height;


/******************************************************************************
**	関数名: WndProcDbgManager
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : コンストラクタ
******************************************************************************/
WndProcDbgManager::WndProcDbgManager()
{
	m_CreateNum = 0;
	m_width = 200;
	m_height = 30;

}


/******************************************************************************
**	関数名: ~WndProcDbgManager
**		関数の概要
**	引数  : void
**	戻り値: void
**	説明  : デストラクタ
******************************************************************************/
WndProcDbgManager::~WndProcDbgManager()
{
	m_pValueDebug = NULL;

}


/******************************************************************************
**	関数名: SetDebugInfo
**	関数の概要
**	引数  : const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize
**	戻り値: int ID(生成順の番号、0～35565)
**	説明  :
******************************************************************************/
int WndProcDbgManager::SetDebugInfo( const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize )
{
	int len = 0;
	HWND hWndEdit;
	VALUEDEBUG *p;
	p = new VALUEDEBUG;


	// データの代入
	len = strlen( pValueName );
	p->pValueName = new char[ len + 1 ];
	strncpy_s( p->pValueName, len + 1, pValueName, len );
	p->nValueNameLen = len;
	p->pValuePointer = ( INTEGRA_DECIMAL * )pValuePointer;
	p->nValueSize = nValueSize;
	p->typevalue = ValType;
	p->sign = sign;
	p->id = ( HMENU )( m_CreateNum + 1 );


	// エディットボックスの生成
	hWndEdit = CreateWindow(
		TEXT( "EDIT" ), TEXT( "0" ),
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		0, m_height * ( m_CreateNum + 1 )  + m_height * m_CreateNum, m_width, m_height,
		hWnd,
		( HMENU )( m_CreateNum + 1 ),
		hInstance,
		NULL );
	p->hWndEditBox = hWndEdit;


	// リスト構造ポインタ代入
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

	// 生成したデータのポインタを移行
	m_pValueDebug = p;
	p = NULL;


	// 生成した順番を返す(開始番号 0～)
	m_CreateNum++;
	return m_CreateNum - 1;

}


/******************************************************************************
**	関数名: Delete
**	関数の概要
**	引数  : int id(0～35565)
**	戻り値: void
**	説明  :
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
			// リスト構造から切り離す
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

			// 削除
			delete[] now->pValueName;
			delete now;
			res = true;
			break;

		}

		// 次のポインタに移動
		now = next;
		i++;

	}


	return res;

}


/******************************************************************************
**	関数名: DeleteAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
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
**	関数名: SetValueNameTextSize
**	関数の概要
**	引数  : int width, int height
**	戻り値: void
**	説明  :
******************************************************************************/
void WndProcDbgManager::SetValueNameTextSize( int width, int height )
{
	m_width = width;
	m_height = height;

}


/******************************************************************************
**	関数名: UpdateWindowTextAll
**	関数の概要
**	引数  : HWND hWnd
**	戻り値: void
**	説明  :
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
**	関数名: DrawWindowTextAll
**	関数の概要
**	引数  : void
**	戻り値: void
**	説明  :
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

		// タイプ
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


		// 変数名のコピー
		strcpy_s( ValueName, 256, now->pValueName );

		// テキストの表示
		RECT r = { 0, m_height * cnt * 2, m_width, m_height + m_height * cnt * 2 };
		DrawText( m_hdc, now->pValueName, now->nValueNameLen, &r, DT_LEFT | DT_WORDBREAK );
		SetWindowText( now->hWndEditBox, text );

		// 次のリストへ移行
		cnt++;
		now = next;

	}

}


/******************************************************************************
**	関数名: GetValueData
**	関数の概要
**	引数  : HMENU id
**	戻り値: void
**	説明  : char型(文字列)は不安定、非推奨
******************************************************************************/
void WndProcDbgManager::GetValueData( HMENU id )
{
	VALUEDEBUG *now = ( VALUEDEBUG * )m_pTop;
	VALUEDEBUG *next;
	char text[ 256 ];

	while( now != NULL )
	{
		next = now->pNext;
		
		// idの検索
		if( now->id == id )
		{
			GetWindowText( now->hWndEditBox, text, 256 );

			// タイプ
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

			// ループから抜ける
			return;

		}

		// 次のポインタへ
		now = next;

	}

}

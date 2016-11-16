#pragma once
/******************************************************************************
**	タイトル  :
**	ファイル名: WndProcDbgManager.h
**	作成者    : AT-13B-284 出席番号 14 木村 祥貴
**	作成日    : 2016/6/28
**	修正日	　: //
********************************************************************************/

/******************************************************************************
**	更新内容
**
**
**
******************************************************************************/

/******************************************************************************
**	インクルードファイル
******************************************************************************/
#include <Windows.h>


/******************************************************************************
**	ライブラリリンク
******************************************************************************/


/******************************************************************************
**	マクロ定義
******************************************************************************/

/* 型 */
typedef enum
{
	TYPEVALUE_CHAR = 0,
	TYPEVALUE_SHORT,
	TYPEVALUE_INT,
	TYPEVALUE_LONG,
	TYPEVALUE_LONGLONG,
	TYPEVALUE_FLOAT,
	TYPEVALUE_DOUBLE,
	TYPEVALUE_LONGDOUBLE

}TYPEVALUE;

/* 符号修飾子 */
typedef enum
{
	TYPESIGN_SIGNED = 0, // 符号あり
	TYPESIGN_UNSIGNED // 符号なし

}TYPESIGN;

/* 整数、小数の共用体 */
typedef union
{
	// Integra
	long long ll;
	unsigned long long ull;
	long l;
	unsigned long ul;
	int i;
	unsigned int ui;
	short s;
	unsigned short us;
	char *c; // 文字ポインタ、符号比較無し
	unsigned char uc; // 非推奨、符号比較無し

	// Decimal
	long double ld; // 符号比較無し
	double d; // 符号比較無し
	float f; // 符号比較無し

}INTEGRA_DECIMAL, *LPINTEGRA_DECIMAL;

/* 変数値デバッグ構造体 */
typedef struct tagVALUEDEBUG
{
	char *pValueName; // 変数名
	int nValueNameLen; // 変数名の長さ
	INTEGRA_DECIMAL *pValuePointer; // 指定先ポインタ
	int nValueSize; // 指定先ポインタの大きさ(主に文字列に使用)
	TYPEVALUE typevalue; // 型の種類
	TYPESIGN sign; // 型の符号有無
	HWND hWndEditBox; // エディットボックスのハンドル
	HMENU id;

	tagVALUEDEBUG *pPrev; // 前ポインタ
	tagVALUEDEBUG *pNext; // 次ポインタ

}VALUEDEBUG;


/******************************************************************************
**	クラス定義
******************************************************************************/
class WndProcDbgManager
{
public:
	WndProcDbgManager();
	virtual ~WndProcDbgManager();


	// メソッド
	static int SetDebugInfo( const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize = 1 );
	static bool Delete( int id );
	static void DeleteAll();

	static void SetValueNameTextSize( int width, int height );
	static void UpdateWindowTextAll( HWND hWnd );
	static void DrawWindowTextAll();

	static void GetValueData( HMENU id );

	// メンバ変数
private:
	static VALUEDEBUG *m_pValueDebug;
	static void *m_pTop, *m_pLast;
	static int m_CreateNum;
	static HWND m_hWnd;
	static HDC m_hdc;
	static int m_width, m_height;

};


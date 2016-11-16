#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: WndProcDbgManager.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/6/28
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
#include <Windows.h>


/******************************************************************************
**	���C�u���������N
******************************************************************************/


/******************************************************************************
**	�}�N����`
******************************************************************************/

/* �^ */
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

/* �����C���q */
typedef enum
{
	TYPESIGN_SIGNED = 0, // ��������
	TYPESIGN_UNSIGNED // �����Ȃ�

}TYPESIGN;

/* �����A�����̋��p�� */
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
	char *c; // �����|�C���^�A������r����
	unsigned char uc; // �񐄏��A������r����

	// Decimal
	long double ld; // ������r����
	double d; // ������r����
	float f; // ������r����

}INTEGRA_DECIMAL, *LPINTEGRA_DECIMAL;

/* �ϐ��l�f�o�b�O�\���� */
typedef struct tagVALUEDEBUG
{
	char *pValueName; // �ϐ���
	int nValueNameLen; // �ϐ����̒���
	INTEGRA_DECIMAL *pValuePointer; // �w���|�C���^
	int nValueSize; // �w���|�C���^�̑傫��(��ɕ�����Ɏg�p)
	TYPEVALUE typevalue; // �^�̎��
	TYPESIGN sign; // �^�̕����L��
	HWND hWndEditBox; // �G�f�B�b�g�{�b�N�X�̃n���h��
	HMENU id;

	tagVALUEDEBUG *pPrev; // �O�|�C���^
	tagVALUEDEBUG *pNext; // ���|�C���^

}VALUEDEBUG;


/******************************************************************************
**	�N���X��`
******************************************************************************/
class WndProcDbgManager
{
public:
	WndProcDbgManager();
	virtual ~WndProcDbgManager();


	// ���\�b�h
	static int SetDebugInfo( const char *pValueName, void *pValuePointer, TYPEVALUE ValType, TYPESIGN sign, HWND hWnd, HINSTANCE hInstance, int nValueSize = 1 );
	static bool Delete( int id );
	static void DeleteAll();

	static void SetValueNameTextSize( int width, int height );
	static void UpdateWindowTextAll( HWND hWnd );
	static void DrawWindowTextAll();

	static void GetValueData( HMENU id );

	// �����o�ϐ�
private:
	static VALUEDEBUG *m_pValueDebug;
	static void *m_pTop, *m_pLast;
	static int m_CreateNum;
	static HWND m_hWnd;
	static HDC m_hdc;
	static int m_width, m_height;

};


#pragma once
/******************************************************************************
**	�^�C�g��  :
**	�t�@�C����: Renderer.h
**	�쐬��    : AT-13B-284 �o�Ȕԍ� 14 �ؑ� �ˋM
**	�쐬��    : 2016/4/22
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
#include < windows.h >
#include <string.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Color.h"
#include "Vector3.h"


/******************************************************************************
**	���C�u���������N
******************************************************************************/

/* OpenGL Library */
#pragma comment ( lib , "opengl32.lib" )
#pragma comment ( lib , "glu32.lib" )


/* ���̍Đ��ɕK�v�ȃR���|�[�l���g(FPS�Ȃǂɂ��g�p) */
#pragma comment ( lib , "winmm.lib" )


/******************************************************************************
**	�}�N����`
******************************************************************************/

// �~����
#define GL_PI ( 3.141592654f )

// �d��
#define GL_GRAVITY ( 9.8f )

// �w�i�F
#define BGCOLOR_R ( 0.0f )
#define BGCOLOR_G ( 0.0f )
#define BGCOLOR_B ( 0.0f )
#define BGCOLOR_A ( 1.0f )


/* �����_�[�X�e�[�g */
typedef enum
{
	GLRS_FILLMODE = 0,
	GLRS_CULLMODE,
	GLRS_LIGHTING,
	GLRS_TEXTURE,
	GLRS_MAX

}GLRENDERSTATE;

/* �t�B�����[�h */
enum GLFILLMODE
{
	GLFILL_POINT = 0,
	GLFILL_WIREFRAME,
	GLFILL_SOLID,
	GLFILL_MAX

};

/* �J�����O���[�h */
enum GLCULL
{
	GLCULL_CU = 0,
	GLCULL_CUU,
	GLCULL_MAX

};


/* ����X�e�[�g */
typedef enum
{
	MOVESTATE_NONE = 0, // �ҋ@��
	MOVESTATE_MOVE, // �ړ���
	MOVESTATE_STOP, // ��~��
	MOVESTATE_MAX

}MOVESTATE;


/* �A�j���[�V���� */
typedef struct tagANIMETION
{
	int nCounterAnim; // 1�t���[�����؊����J�E���g
	int nChangeTimming; // �A�j���[�V�����؊��^�C�~���O
	int nPosPatternAnim_X; // �摜�̈ʒuX���W
	int nPosPatternAnim_Y; // �摜�̈ʒuY���W
	float fPattern_X; // X���W�ɑ΂��ẴA�j���[�V�����Ԋu
	float fPattern_Y; // Y���W�ɑ΂��ẴA�j���[�V�����Ԋu
	float fAnimWidth; // �A�j���[�V�����؊��Ԋu ��
	float fAnimHeight; // �A�j���[�V�����؊��Ԋu ����

}ANIMETION, *LPANIMETION;


/* �|�W�V���� */
typedef struct tagOBJECT3D
{
	// �ʒu�A�傫��
	Vector3 pos; // �|�W�V����
	Vector3 accPos; // �ړ���(���x��)
	Vector3 posSet; // �ړI�ʒu
	Vector3 rot; // ��]
	Vector3 rotMove; // ��]��
	Vector3 rotSetMove; // �ړI�p�x
	Vector3 scl; // �傫��
	Vector3 normal; // �@��
	//D3DXMATRIX mtxWorld; // ���[���h�}�g���b�N�X
	Color col; // �F
	float velocity; // �W�����v�����x
	float fall; // �������x
	float velocityJumpVec; // �W�����v������
	float accJumpVec; // �W�����v���x��
	float moveVec; // �i�ދ����̒���
	float length2D; // ���`�Ίp��
	float length3D; // �����̑Ίp��
	float angleXZ; // �Εӊp
	float angleYX; // �Εӊp
	float width; // ��
	float height; // ����
	float depth; // ���s��
	int nLife; // �����AHP
	int JumpCnt; // �W�����v���̃J�E���g
	bool bUse; // �g�p���̗L��
	bool bUpdate; // �A�b�v�f�[�g�L��
	bool bDraw; // �`��L��
	bool bHit; // �Փ˔���

	// �A�j���[�V�����֘A
	ANIMETION anim;

	// �e��X�e�[�g
	MOVESTATE movestate;

}OBJECT3D, *LPOBJECT3D;


/******************************************************************************
**	�N���X��`
******************************************************************************/

/* �����_��GL�N���X */
class RendererGL
{
public:
	RendererGL();
	virtual ~RendererGL();

	// ���\�b�h
	HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	int Uninit();
	void Update();

	bool BeginDraw();
	void EndDraw();

	// �f�o�C�X�֘A�̎󂯓n��
	static HDC GetHDC();
	static HGLRC GetHGLRC();


	// Set,Get
	static void SetRenderMode( GLRENDERSTATE glrs, DWORD value );
	static void SetRenderMode( DWORD glrs, GLboolean value );
	static void SetBgColor( float r, float g, float b, float a );
	static void SetBgColor( Color *col );
	static void SetBgColor( unsigned long col );
	static Color GetBgColor();


private:
	// �����o�ϐ�
	int m_nFormat; // �`��̃t�H�[�}�b�g�ԍ�

	// �f�o�C�X�֘A
	static HDC m_hDC; // �f�o�C�X�R���e�L�X�g
	static HGLRC m_hGLRC; // OpenGL�̃f�o�C�X

	// �F
	static Color m_BgCol;

};

